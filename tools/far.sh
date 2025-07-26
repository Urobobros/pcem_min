#!/usr/bin/env bash
# Quick helper commands for BIOS modification walkthrough

set -euo pipefail

BIOS=${1:-ami_8088_bios_31jan89.bin}

# Example disassembly with radare2
r2 -a x86 -b 16 -m 0xf0000 "$BIOS" <<'RAD'
aaa
/ out
/ in
q
RAD

# Example assembly rebuild (modify exported.asm as needed)
# nasm -f bin modified.asm -o modified.bin

# Example patching of the original BIOS
# dd if=modified.bin of="$BIOS" bs=1 seek=0x1234 conv=notrunc
