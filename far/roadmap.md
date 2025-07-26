# Roadmap

| Krok | Úkol | Příkaz / nástroj | Deadline | Stav |
| --- | --- | --- | --- | --- |
| 1 | Instalace nástrojů | `sudo apt install radare2 nasm hexedit` | Dnes | 🔲 |
| 2 | Umístit BIOS do složky `bios/` | `cp ami_8088_bios_31jan89.bin bios/` | Dnes | 🔲 |
| 3 | Rychlý náhled v radare2 | `r2 -a x86 -b 16 -m 0xf0000 bios/ami_8088_bios_31jan89.bin` | Dnes | 🔲 |
| 4 | Vyhledat porty pomocí skriptu | `python3 tools/bios_port_search.py bios/ami_8088_bios_31jan89.bin -p 03B8 0213` | Dnes | 🔲 |
| 5 | Otevřít BIOS v Ghidře a nastavit base 0xF0000 | GUI | Zítra | 🔲 |
| 6 | Exportovat kód do NASM | Ghidra → *Export Program* | Zítra | 🔲 |
| 7 | Vyčistit ASM a přeložit | `nasm -f bin exported.asm -o new.bin` | Zítra | 🔲 |
| 8 | Patchnout originální BIOS | `dd if=new.bin of=bios/ami_8088_bios_31jan89.bin bs=1 seek=OFFSET conv=notrunc` | Zítra | 🔲 |
| 9 | Test v emulátoru | `qemu-system-i386 -bios bios/ami_8088_bios_31jan89.bin` | Později | 🔲 |
