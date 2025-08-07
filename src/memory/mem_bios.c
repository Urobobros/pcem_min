#include <stdlib.h>
#include "ibm.h"
#include "mem.h"
#include "mem_bios.h"
#include "rom.h"
#include "video.h"


static void romfread(uint8_t *buf, size_t size, size_t count, FILE *fp) {
        int result = fread(buf, size, count, fp);
        if (result < count) {
                pclog("ROM read failed: Expected %d, read %d\n", count, result);
        }
}

static int mem_load_basic(char *path) {
        char s[256];
        FILE *f;

        sprintf(s, "%s/ibm-basic-1.10.rom", path);
        f = romfopen(s, "rb");
        if (!f) {
                sprintf(s, "%s/basicc11.f6", path);
                f = romfopen(s, "rb");
                if (!f)
                        return 1; /*I don't really care if BASIC is there or not*/
                romfread(rom + 0x6000, 8192, 1, f);
                fclose(f);
                sprintf(s, "%s/basicc11.f8", path);
                f = romfopen(s, "rb");
                if (!f)
                        return 0; /*But if some of it is there, then all of it must be*/
                romfread(rom + 0x8000, 8192, 1, f);
                fclose(f);
                sprintf(s, "%s/basicc11.fa", path);
                f = romfopen(s, "rb");
                if (!f)
                        return 0;
                romfread(rom + 0xA000, 8192, 1, f);
                fclose(f);
                sprintf(s, "%s/basicc11.fc", path);
                f = romfopen(s, "rb");
                if (!f)
                        return 0;
                romfread(rom + 0xC000, 8192, 1, f);
                fclose(f);
        } else {
                romfread(rom + 0x6000, 32768, 1, f);
                fclose(f);
        }

        return 1;
}

int loadbios() {
        FILE *f = NULL, *ff = NULL;
        int c;

        loadfont("mda.rom", FONT_MDA);

        biosmask = 0xffff;

        if (!rom)
                rom = malloc(0x40000);
        memset(romext, 0x63, 0x4000);
        memset(rom, 0xff, 0x20000);

       // pclog("Starting with romset %i\n", romset);

        switch (romset) {
                case ROM_AMIXT:
                        f = romfopen("amixt/ami_8088_bios_31jan89.bin", "rb");
                        if (!f)
                                break;
                        romfread(rom + 0xE000, 8192, 1, f);
                        fclose(f);
                        return 1;
        }
   //     printf("Failed to load ROM!\n");
        if (f)
                fclose(f);
        if (ff)
                fclose(ff);
        return 0;
}
