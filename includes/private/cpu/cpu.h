#ifndef _CPU_H_
#define _CPU_H_

#include <pcem/devices.h>

extern int cpu, cpu_manufacturer;
extern int fpu_type;

/*808x class CPUs*/
#define CPU_8088 0

#define MANU_INTEL 0
#define MANU_AMD 1
#define MANU_CYRIX 2
#define MANU_IDT 3
#define MANU_VIA 4

extern int timing_rr;
extern int timing_mr, timing_mrl;
extern int timing_rm, timing_rml;
extern int timing_mm, timing_mml;
extern int timing_bt, timing_bnt;

extern int timing_int, timing_int_rm, timing_int_v86, timing_int_pm, timing_int_pm_outer;
extern int timing_iret_rm, timing_iret_v86, timing_iret_pm, timing_iret_pm_outer;
extern int timing_call_rm, timing_call_pm, timing_call_pm_gate, timing_call_pm_gate_inner;
extern int timing_retf_rm, timing_retf_pm, timing_retf_pm_outer;
extern int timing_jmp_rm, timing_jmp_pm, timing_jmp_pm_gate;

extern int timing_misaligned;

enum { FPU_NONE, FPU_8087, FPU_287, FPU_287XL, FPU_387, FPU_BUILTIN };

extern CPU *cpu_s;

extern CPU cpus_8088[];

extern int cpu_iscyrix;
extern int cpu_16bitbus;
extern int cpu_busspeed;
extern int cpu_multi;
/*Cyrix 5x86/6x86 only has data misalignment penalties when crossing 8-byte boundaries*/
extern int cpu_cyrix_alignment;

#define CPU_FEATURE_RDTSC (1 << 0)
#define CPU_FEATURE_MSR (1 << 1)
#define CPU_FEATURE_MMX (1 << 2)
#define CPU_FEATURE_CR4 (1 << 3)
#define CPU_FEATURE_VME (1 << 4)
#define CPU_FEATURE_CX8 (1 << 5)
#define CPU_FEATURE_3DNOW (1 << 6)
#define CPU_FEATURE_SYSCALL (1 << 7)

extern uint32_t cpu_features;
static inline int cpu_has_feature(int feature) { return cpu_features & feature; }

#define CR4_TSD (1 << 2)
#define CR4_DE (1 << 3)
#define CR4_MCE (1 << 6)
#define CR4_PCE (1 << 8)

extern uint64_t cpu_CR4_mask;

#define CPU_SUPPORTS_DYNAREC 1
#define CPU_REQUIRES_DYNAREC 2

extern int cpu_cycles_read, cpu_cycles_read_l, cpu_cycles_write, cpu_cycles_write_l;
extern int cpu_prefetch_cycles, cpu_prefetch_width, cpu_mem_prefetch_cycles, cpu_rom_prefetch_cycles;
extern int cpu_waitstates;
extern int cpu_cache_int_enabled, cpu_cache_ext_enabled;

extern uint64_t tsc;

void cyrix_write(uint16_t addr, uint8_t val, void *priv);
uint8_t cyrix_read(uint16_t addr, void *priv);

extern int is486;
extern int CPUID;

void cpu_CPUID();
void cpu_RDMSR();
void cpu_WRMSR();

extern int cpu_use_dynarec;

extern uint64_t xt_cpu_multi;

extern int isa_cycles;
#define ISA_CYCLES(x) (x * isa_cycles)

#define CPU_CLOCK_DIVIDER_MAX 16384
void cpu_update_waitstates();
void cpu_set();
void cpu_set_edx();
void cpu_set_turbo(int turbo);
int cpu_get_turbo();
void cpu_set_nonturbo_divider(int divider);
int cpu_get_speed();

extern int has_vlb;

int fpu_get_type(int model, int manu, int cpu, const char *internal_name);
const char *fpu_get_internal_name(int model, int manu, int cpu, int type);
const char *fpu_get_name_from_index(int model, int manu, int cpu, int c);
int fpu_get_type_from_index(int model, int manu, int cpu, int c);

#endif /* _CPU_H_ */
