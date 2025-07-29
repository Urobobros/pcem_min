#include <stdint.h>
#include "ibm.h"
#include "models/pit.h"

/* CPU and ISA */
int isa_cycles = 1; 
struct cpu_state_t { int _cycles; } cpu_state;

/* Disc/FDD stubs */
void disc_set_rate(int drive, int drvden, int rate) {}
void disc_set_drivesel(int drive) {}
void disc_set_motor_enable(int m) {}
void disc_readsector(int drive, int sector, int track, int side, int density, int sector_size) {}
void disc_writesector(int drive, int sector, int track, int side, int density, int sector_size) {}
void disc_readaddress(int drive, int track, int side, int density) {}
void disc_format(int drive, int track, int side, int density, uint8_t fill) {}
void disc_sector_stop() {}
int disc_drivesel = 0;
int disc_changed[2] = {0};
int drive_empty[2] = {0};
int writeprot[2] = {0};

int fdd_swap = 0;
void fdd_set_densel(int densel) {}
uint64_t fdd_seek(int drive, int track_diff) { return 0; }
int fdd_is_525(int drive) { return 0; }
int fdd_is_ed(int drive) { return 0; }
int fdd_get_type(int drive) { return 0; }
int fdd_track0(int drive) { return 0; }

/* DMA */
void dma_channel_write(int chan, uint8_t dat) {}
uint8_t dma_channel_read(int chan) { return 0; }

/* PIC/Interrupt stubs */
void picintlevel(int level) {}

/* Speaker/Timer/Video stubs */
int was_speaker_enable = 0;
int speaker_gated = 0;
int speaker_enable = 0;
void speaker_update() {}
PIT pit; 
void pit_set_gate(PIT *pit, int channel, int gate) {}
void timer_process() {}
void cpu_set_turbo(int turbo) {}
int video_is_ega_vga() { return 0; }
int video_is_mda() { return 0; }
int hasfpu = 0;

/* Keyboard globals */
int keyboard_scan = 1;
void (*keyboard_send)(uint8_t val) = 0;
void (*keyboard_poll)() = 0;

int readflash = 0;
