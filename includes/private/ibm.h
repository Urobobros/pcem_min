#ifndef _IBM_H_
#define _IBM_H_
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "timer.h"

#include <pcem/defines.h>
#include <pcem/logging.h>

#ifdef ABS
#undef ABS
#endif

#define ABS(x) ((x) > 0 ? (x) : -(x))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define READFLASH_FDC 0
#define READFLASH_HDC 4
#define readflash_set(offset, drive) readflash |= 1 << ((offset) + (drive))
#define readflash_clear(offset, drive) readflash &= ~(1 << ((offset) + (drive)))
#define readflash_get(offset, drive) ((readflash & (1 << ((offset) + (drive)))) != 0)

/*Memory*/
extern uint8_t *ram;

extern uint32_t rammask;

extern int readlookup[256], readlookupp[256];
extern uintptr_t *readlookup2;
extern int readlnext;
extern int writelookup[256], writelookupp[256];
extern uintptr_t *writelookup2;
extern int writelnext;

extern int mmu_perm;

uint8_t readmembl(uint32_t addr);
void writemembl(uint32_t addr, uint8_t val);
uint16_t readmemwl(uint32_t addr);
void writememwl(uint32_t addr, uint16_t val);
uint32_t readmemll(uint32_t addr);
void writememll(uint32_t addr, uint32_t val);
uint64_t readmemql(uint32_t addr);
void writememql(uint32_t addr, uint64_t val);

uint8_t *getpccache(uint32_t a);

uint32_t mmutranslatereal(uint32_t addr, int rw);

void addreadlookup(uint32_t virt, uint32_t phys);
void addwritelookup(uint32_t virt, uint32_t phys);

/*IO*/
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t val);
uint32_t inl(uint16_t port);
void outl(uint16_t port, uint32_t val);

FILE *romfopen(char *fn, char *mode);
extern int mem_size;
extern int readlnum, writelnum;

/*Processor*/
extern int ins, output, timetolive;

extern int cycles_lost;

/*Timer*/
typedef struct PIT_nr {
        int nr;
        struct PIT *pit;
} PIT_nr;

typedef struct PIT {
        uint32_t l[3];
        pc_timer_t timer[3];
        uint8_t m[3];
        uint8_t ctrl, ctrls[3];
        int wp, rm[3], wm[3];
        uint16_t rl[3];
        int thit[3];
        int delay[3];
        int rereadlatch[3];
        int gate[3];
        int out[3];
        int running[3];
        int enabled[3];
        int newcount[3];
        int count[3];
        int using_timer[3];
        int initial[3];
        int latched[3];
        int disabled[3];

        uint8_t read_status[3];
        int do_read_status[3];

        PIT_nr pit_nr[3];

        void (*set_out_funcs[3])(int new_out, int old_out);
} PIT;

extern PIT pit;
void setpitclock(float clock);

float pit_timer0_freq();

#define cpu_rm cpu_state.rm_data.rm_mod_reg.rm
#define cpu_mod cpu_state.rm_data.rm_mod_reg.mod
#define cpu_reg cpu_state.rm_data.rm_mod_reg.reg

/*DMA*/
typedef struct dma_t {
        uint32_t ab, ac;
        uint16_t cb;
        int cc;
        int wp;
        uint8_t m, mode;
        uint8_t page;
        uint8_t stat, stat_rq;
        uint8_t command;
        int size;

        uint8_t ps2_mode;
        uint8_t arb_level;
        uint16_t io_addr;
} dma_t;

extern dma_t dma[8];

/*PPI*/
typedef struct PPI {
        int s2;
        uint8_t pa, pb;
} PPI;

extern PPI ppi;

/*PIC*/
typedef struct PIC {
        uint8_t icw1, icw4, mask, ins, pend, mask2;
        int icw;
        uint8_t vector;
        int read;
        uint8_t level_sensitive;
} PIC;

extern PIC pic, pic2;
extern int pic_intpending;

extern char discfns[2][256];
extern int driveempty[2];

#define PCJR (romset == ROM_IBMPCJR)

extern int GAMEBLASTER, GUS, SSI2001;
extern int is386, PCI, MCA;

enum {
        ROM_AMIXT, /*XT Clone with AMI BIOS*/
};

extern int romspresent[ROM_MAX];

extern int hasfpu;
extern int romset;

enum {
        GFX_BUILTIN = -1,
        GFX_CGA = 0,
        GFX_MDA
};

extern int gfx_present[GFX_MAX];

extern int gfxcard;

extern int cpuspeed;

/*Video*/
extern int readflash;
extern int egareads, egawrites;
extern int vid_resize;
extern int vid_api;
extern int winsizex, winsizey;

extern int changeframecount;

/*Sound*/
extern int ppispeakon;
extern uint64_t CGACONST;
extern uint64_t MDACONST;
extern uint64_t RTCCONST;
extern int gated, speakval, speakon;

/*Hard disc*/
typedef struct {
        FILE *f;
        int spt, hpc; /*Sectors per track, heads per cylinder*/
        int tracks;
} PcemHDC;

extern PcemHDC hdc[7];

/*Keyboard*/
extern int keybsenddelay;

/*CD-ROM*/
extern int cdrom_drive;
extern int old_cdrom_drive;
extern int idecallback[2];

#define CD_STATUS_EMPTY 0
#define CD_STATUS_DATA_ONLY 1
#define CD_STATUS_PLAYING 2
#define CD_STATUS_PAUSED 3
#define CD_STATUS_STOPPED 4

extern uint32_t atapi_get_cd_volume(int channel);

extern int nmi;
extern int nmi_auto_clear;

extern float isa_timing, bus_timing;

uint64_t timer_read();
extern uint64_t timer_freq;

void loadconfig(char *fn);
extern int config_override;

extern int infocus;

void onesec();

void resetpc_cad();

extern int start_in_fullscreen;
extern int window_w, window_h, window_x, window_y, window_remember;

void startblit();
void endblit();

void set_window_title(const char *s);

void updatewindowsize(int x, int y);

void initpc(int argc, char *argv[]);
void runpc();
void closepc();
void resetpc();
void resetpchard();
void speedchanged();

void saveconfig(char *fn);
void saveconfig_global_only();

#define UNUSED(x) (void)x

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void ide_padstr(char *str, const char *src, int len);

void stop_emulation_now(void);

#endif /* _IBM_H_ */
