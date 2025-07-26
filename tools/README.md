# Tools

## BIOS Port Search

Use `bios_port_search.py` to scan a BIOS binary for `IN` or `OUT` instructions targeting specific I/O ports. This can help determine if a ROM accesses particular hardware.

```bash
python3 bios_port_search.py NAZEV_VASEHO_BIOSU.bin -p 03B8 0213
```

The script requires `objdump` to be installed and available in your PATH. The BIOS file is provided as the first argument, while ports are specified in hexadecimal without the `0x` prefix. If you omit `-p`, the tool searches the default ports `0xA0` and `0x3D8`.

## Disassembling a BIOS

`ndisasm` (part of the NASM toolchain) can be used to inspect BIOS images:

```bash
ndisasm -b 16 ami_8088_bios_31jan89.bin | less
```

If you want to edit the code and assemble it again, be aware that the output of
`ndisasm` is **not** directly valid NASM input. The listing contains offsets and
hex bytes that must be removed and it lacks an `org` directive telling NASM
where the code should reside. One approach is:

```bash
# Start a new assembly file with the ROM load address
echo 'org 0xf0000' > ami_8088_bios_31jan89.asm
# Strip the address and hex columns from the disassembly
ndisasm -b 16 ami_8088_bios_31jan89.bin | cut -c21- >> ami_8088_bios_31jan89.asm
```

This still requires manual cleanup (labels, data sections, jump targets) before
running NASM:

```bash
nasm -f bin ami_8088_bios_31jan89.asm -o ami_8088_bios_31jan89_rebuilt.bin
```

Recreating the original binary exactly is difficult, but the process can help
when experimenting with small modifications.
