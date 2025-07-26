# Tools

This directory contains small helper scripts. Currently available:

## `bios_port_search.py`

Search a BIOS binary for IN/OUT port instructions. Requires `objdump` from binutils.

```
python3 bios_port_search.py [-p PORT ...] PATH_TO_BIOS
```

If no ports are provided, the script looks for `0xA0` and `0x3D8`.

Example:

```
python3 bios_port_search.py ./bios/ami_8088_bios_31jan89.bin
```

Specify additional ports in hexadecimal:

```
python3 bios_port_search.py -p A0 3D0 3D8 ./bios/ami_8088_bios_31jan89.bin
```
