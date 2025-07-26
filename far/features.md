# BIOS Modification Project Features

| Cíl | Popis | Stav |
| --- | ----- | ---- |
| Načíst BIOS do disassembleru | Analyzovat BIOS pomocí Ghidry nebo radare2 | ✅ Hotovo |
| Najít I/O porty | Vyhledat in/out instrukce na porty (např. 03B8, A0, 3D8) | 🔄 Probíhá |
| Exportovat NASM kompatibilní kód | Export z Ghidry a ruční čištění k překladu NASMem | 🔲 Plánováno |
| Přeložit .asm do .bin | Použít `nasm -f bin` | 🔲 Plánováno |
| Patchnout originální BIOS | Pomocí `dd` nebo `hexedit` nahradit část kódu | 🔲 Plánováno |
| Otestovat upravený BIOS | V emulátoru (86Box, QEMU, Bochs) | 🔲 Později |
