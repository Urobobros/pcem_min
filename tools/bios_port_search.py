import argparse
import subprocess
import re
from pathlib import Path


def disassemble(bios_path: Path) -> list[str]:
    """Disassemble binary BIOS file using objdump."""
    cmd = [
        "objdump",
        "-D",
        "-b",
        "binary",
        "-m",
        "i8086",
        str(bios_path),
    ]
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
    return result.stdout.splitlines()


def search_ports(asm_lines: list[str], ports: list[int]) -> list[str]:
    """Search assembly lines for in/out instructions to given ports."""
    hits = []
    pattern = re.compile(r"\b(in|out)\b[^$]*\$0x([0-9a-fA-F]+)")
    for line in asm_lines:
        match = pattern.search(line)
        if match:
            port = int(match.group(2), 16)
            if port in ports:
                hits.append(line)
    return hits


def main() -> None:
    parser = argparse.ArgumentParser(description="Search BIOS for IN/OUT port instructions")
    parser.add_argument("bios", type=Path, help="Path to BIOS binary")
    parser.add_argument(
        "-p",
        "--ports",
        nargs="+",
        default=["A0", "3D8"],
        help="Ports to search for in hex (defaults to A0 3D8)",
    )
    args = parser.parse_args()

    ports = [int(p, 16) for p in args.ports]
    asm_lines = disassemble(args.bios)
    hits = search_ports(asm_lines, ports)

    if hits:
        print("Found instructions:")
        for line in hits:
            print(line)
    else:
        print("No matching instructions found")

    print(f"Total matches: {len(hits)}")


if __name__ == "__main__":
    main()
