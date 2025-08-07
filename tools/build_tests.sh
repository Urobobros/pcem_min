#!/usr/bin/env bash
set -e
CC=${CC:-gcc}
COMMON="-Iincludes -Iincludes/private -Iincludes/private/bus -Iincludes/private/ide -Iincludes/private/floppy -Iincludes/private/memory -Iincludes/private/video -Iincludes/private/cpu -Iincludes/private/models -Iincludes/private/plugin-api -Iincludes/private/scsi -Iincludes/private/sound -Iincludes/private/disc -Iincludes/private/mouse -Iincludes/private/keyboard -Iincludes/public -Isrc"
$CC $COMMON tests/test_init.c src/io.c src/models/dma.c src/models/pit.c -o tests/test_init
$CC $COMMON tests/test_dma_init.c src/io.c src/models/dma.c -o tests/test_dma_init
$CC $COMMON tests/test_pic_init.c src/io.c src/models/pic.c -o tests/test_pic_init
$CC $COMMON tests/test_pit_init.c src/io.c src/models/pit.c src/models/dma.c -o tests/test_pit_init
$CC $COMMON tests/test_fdc_init.c tests/test_stubs.c src/io.c src/floppy/fdc.c -o tests/test_fdc_init
$CC $COMMON tests/test_keyboard_init.c tests/test_stubs.c src/io.c src/keyboard/keyboard_xt.c -o tests/test_keyboard_init
$CC $COMMON tests/test_serial_init.c src/io.c src/models/serial.c -o tests/test_serial_init
$CC $COMMON tests/test_device_init.c tests/test_stubs.c src/io.c src/floppy/fdc.c src/models/serial.c src/keyboard/keyboard_xt.c src/models/nmi.c -o tests/test_device_init
$CC $COMMON tests/test_cga_init.c tests/test_stubs.c src/io.c -o tests/test_cga_init
