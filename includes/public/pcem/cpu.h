#ifndef _PCEM_CPU_H_
#define _PCEM_CPU_H_

#include <stdint.h>

typedef struct FPU {
        const char *name;
        const char *internal_name;
        const int type;
} FPU;

typedef struct CPU {
        char name[32];
        int cpu_type;
        const FPU *fpus;
        int speed;
        int rspeed;
        int multi;
        int pci_speed;
        uint32_t edx_reset;
        uint32_t cpuid_model;
        uint16_t cyrix_id;
        int cpu_flags;
        int mem_read_cycles, mem_write_cycles;
        int cache_read_cycles, cache_write_cycles;
        int atclk_div;
} CPU;

extern FPU fpus_none[];
extern FPU fpus_8088[];
extern FPU fpus_80286[];
extern FPU fpus_80386[];
extern FPU fpus_builtin[];
extern CPU cpus_8088[];

#endif /* _PCEM_CPU_H_ */
