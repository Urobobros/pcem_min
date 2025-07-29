# Building Unit Tests on Windows

To build the small unit tests included in this repository using a Windows environment, install a GCC-based toolchain such as [MinGW-w64](http://mingw-w64.org/). Once `gcc` is available in your `PATH`, run the batch script:

```cmd
cd %~dp0\..
tools\build_tests.bat
```

The script compiles `tests\test_init.exe`, `tests\test_dma_init.exe`, `tests\test_pic_init.exe`, `tests\test_pit_init.exe`, `tests\test_fdc_init.exe`, `tests\test_keyboard_init.exe`, `tests\test_serial_init.exe`, `tests\test_device_init.exe` and `tests\test_cga_init.exe`. After building you can execute each program from a command prompt:

```cmd
tests\test_init.exe
```

Each test prints a confirmation message when it passes.
