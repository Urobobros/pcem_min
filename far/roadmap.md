# Roadmap

| Krok | Úkol | Příkaz / nástroj | Deadline | Stav |
| --- | --- | --- | --- | --- |
| 1 | Spustit radare2 pro rychlý náhled | `r2 -a x86 -b 16 -m 0xf0000 ami_8088_bios_31jan89.bin` | Dnes | ✅ Hotovo |
| 2 | Spustit aaa a hledat přístup na porty | `aaa; / out; / in` | Dnes | 🔄 Probíhá |
| 3 | Otevřít Ghidru a nastavit 0xF0000 jako image base | GUI | Zítra | 🔲 Plán |
| 4 | Exportovat kód z Ghidry jako NASM | GUI (File → Export Program) | Zítra | 🔲 Plán |
| 5 | Vyčistit .asm a přeložit | `nasm -f bin export.asm -o new.bin` | Zítra | 🔲 Plán |
| 6 | Patchnout originální BIOS | `dd if=new.bin of=orig.bin bs=1 seek=OFFSET conv=notrunc` | Zítra | 🔲 Plán |
| 7 | Spustit v emulátoru (86Box nebo QEMU) | `qemu-system-i386 -bios orig.bin` | Později | 🔲 Plán |
