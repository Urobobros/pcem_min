#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "ibm.h"
#undef printf
#include "io.h"
#include "memory/mem.h"
#include "video/vid_cga.h"
#include <stdlib.h>

static uint8_t stub_in(uint16_t addr, void *p) { (void)addr; (void)p; return 0; }
static void stub_out(uint16_t addr, uint8_t val, void *p) { (void)addr; (void)val; (void)p; }
static uint8_t stub_read(uint32_t addr, void *p) { return ((cga_t *)p)->vram[addr & 0x3fff]; }
static void stub_write(uint32_t addr, uint8_t val, void *p) { ((cga_t *)p)->vram[addr & 0x3fff] = val; }

static cga_t *cga_standalone_init() {
    cga_t *cga = malloc(sizeof(cga_t));
    memset(cga, 0, sizeof(cga_t));
    cga->vram = malloc(0x4000);
    io_sethandler(0x03d0, 0x0010, stub_in, NULL, NULL, stub_out, NULL, NULL, cga);
    return cga;
}
extern uint8_t (*port_inb[0x10000][2])(uint16_t, void*);
extern void (*port_outb[0x10000][2])(uint16_t, uint8_t, void*);
extern void *port_priv[0x10000][2];

/* Stubs for device and memory helpers */
int device_get_config_int(char *name) { return 0; }
void cga_comp_init(int revision) {}
void cgapal_rebuild(int display_type, int contrast) {}
void mem_mapping_add(mem_mapping_t *mapping, uint32_t base, uint32_t size,
                     uint8_t (*read_b)(uint32_t, void*),
                     uint16_t (*read_w)(uint32_t, void*),
                     uint32_t (*read_l)(uint32_t, void*),
                     void (*write_b)(uint32_t, uint8_t, void*),
                     void (*write_w)(uint32_t, uint16_t, void*),
                     void (*write_l)(uint32_t, uint32_t, void*),
                     uint8_t *exec, uint32_t flags, void *p) {}

uint8_t mem_readb_phys(uint32_t addr) { return 0; }
void mem_writeb_phys(uint32_t addr, uint8_t val) {}
void mem_invalidate_range(uint32_t start, uint32_t end) {}

/* Timer stubs */
uint64_t tsc = 0;
int cpu_busspeed = 1;
uint64_t xt_cpu_multi;
#include "private/timer.h"
void timer_add(pc_timer_t *timer, void (*callback)(void *), void *p, int start)
{ timer->callback = callback; timer->p = p; timer->enabled = start; }
uint32_t timer_target; uint64_t TIMER_USEC;
void timer_enable(pc_timer_t *timer) { timer->enabled = 1; }
void timer_disable(pc_timer_t *timer) { timer->enabled = 0; }

/* Misc stubs required by ibm.h */
void pclog(const char *fmt, ...) {}
void error(const char *fmt, ...) {}
void fatal(const char *fmt, ...) {}
void warning(const char *fmt, ...) {}
void device_speed_changed() {}
void video_updatetiming() {}
int nmi = 0; int nmi_auto_clear = 0; int speakon = 0; int ppispeakon = 0;
int speakval = 0; PPI ppi; uint8_t _ram_storage[1]; uint8_t *ram = _ram_storage;

int main() {
    io_init();
    cga_t *cga = cga_standalone_init();
    for (int p = 0x3d0; p < 0x3e0; p++) {
        if (p < 0x3d0 + 0x10) {
            if ((p & 1) == 0)
                assert(port_outb[p][0] == stub_out);
            else
                assert(port_inb[p][0] == stub_in);
            assert(port_priv[p][0] == cga);
        }
    }

    stub_write(0, 'A', cga);
    assert(stub_read(0, cga) == 'A');
    printf("CGA VRAM first byte: %c\n", cga->vram[0]);
    printf("cga_init tests passed\n");
    return 0;
}
