# BIOS Modification Project Features

| Cíl | Popis | Stav |
| --- | ----- | ---- |
| Načíst BIOS do disassembleru | Analyzovat BIOS pomocí Ghidry nebo radare2 | ✅ Hotovo |
| Najít I/O porty | Vyhledat in/out instrukce na porty (např. 03B8, A0, 3D8) | 🔄 Probíhá |
| Exportovat NASM kompatibilní kód | Export z Ghidry a ruční čištění k překladu NASMem | 🔲 Plánováno |
| Přeložit .asm do .bin | Použít `nasm -f bin` | 🔲 Plánováno |
| Patchnout originální BIOS | Pomocí `dd` nebo `hexedit` nahradit část kódu | 🔲 Plánováno |
| Otestovat upravený BIOS | V emulátoru (86Box, QEMU, Bochs) | 🔲 Později |
| Unit testy inicializace | Testy pro pit_init, dma_init, pic_init, fdc_add, serial1/2_init, keyboard_xt_init, nmi_init, CGA a io_sethandler (včetně samostatných testů pro klávesnici, sériové porty a FDC) | ✅ Hotovo |
| Build skripty pro Windows | Batch soubor `tools/build_tests.bat` kompiluje unit testy | ✅ Hotovo |
