#include "ibm.h"
#include "cpu.h"
#include "model.h"
#include "io.h"
#include "x86_ops.h"
#include "mem.h"
#include "pci.h"
#include "codegen.h"
#include "x87_timings.h"

int fpu_type;
uint32_t cpu_features;

static int cpu_turbo_speed, cpu_nonturbo_speed;
static int cpu_turbo = 1;

int isa_cycles;
int has_vlb;
static uint8_t ccr0, ccr1, ccr2, ccr3, ccr4, ccr5, ccr6;
int hasfpu;
int cpuspeed;

OpFn *x86_dynarec_opcodes;
OpFn *x86_dynarec_opcodes_0f;
OpFn *x86_dynarec_opcodes_d8_a16;
OpFn *x86_dynarec_opcodes_d8_a32;
OpFn *x86_dynarec_opcodes_d9_a16;
OpFn *x86_dynarec_opcodes_d9_a32;
OpFn *x86_dynarec_opcodes_da_a16;
OpFn *x86_dynarec_opcodes_da_a32;
OpFn *x86_dynarec_opcodes_db_a16;
OpFn *x86_dynarec_opcodes_db_a32;
OpFn *x86_dynarec_opcodes_dc_a16;
OpFn *x86_dynarec_opcodes_dc_a32;
OpFn *x86_dynarec_opcodes_dd_a16;
OpFn *x86_dynarec_opcodes_dd_a32;
OpFn *x86_dynarec_opcodes_de_a16;
OpFn *x86_dynarec_opcodes_de_a32;
OpFn *x86_dynarec_opcodes_df_a16;
OpFn *x86_dynarec_opcodes_df_a32;
OpFn *x86_dynarec_opcodes_REPE;
OpFn *x86_dynarec_opcodes_REPNE;
OpFn *x86_dynarec_opcodes_3DNOW;

OpFn *x86_opcodes;
OpFn *x86_opcodes_0f;
OpFn *x86_opcodes_d8_a16;
OpFn *x86_opcodes_d8_a32;
OpFn *x86_opcodes_d9_a16;
OpFn *x86_opcodes_d9_a32;
OpFn *x86_opcodes_da_a16;
OpFn *x86_opcodes_da_a32;
OpFn *x86_opcodes_db_a16;
OpFn *x86_opcodes_db_a32;
OpFn *x86_opcodes_dc_a16;
OpFn *x86_opcodes_dc_a32;
OpFn *x86_opcodes_dd_a16;
OpFn *x86_opcodes_dd_a32;
OpFn *x86_opcodes_de_a16;
OpFn *x86_opcodes_de_a32;
OpFn *x86_opcodes_df_a16;
OpFn *x86_opcodes_df_a32;
OpFn *x86_opcodes_REPE;
OpFn *x86_opcodes_REPNE;
OpFn *x86_opcodes_3DNOW;

enum {
        CPUID_FPU = (1 << 0),
        CPUID_VME = (1 << 1),
        CPUID_PSE = (1 << 3),
        CPUID_TSC = (1 << 4),
        CPUID_MSR = (1 << 5),
        CPUID_CMPXCHG8B = (1 << 8),
        CPUID_SEP = (1 << 11),
        CPUID_CMOV = (1 << 15),
        CPUID_MMX = (1 << 23)
};

/*Addition flags returned by CPUID function 0x80000001*/
enum { CPUID_3DNOW = (1 << 31) };

int cpu = 3, cpu_manufacturer = 0;
CPU *cpu_s;
int cpu_multi;
int cpu_iscyrix;
int cpu_16bitbus;
int cpu_busspeed;
int cpu_use_dynarec;
int cpu_cyrix_alignment;

uint64_t cpu_CR4_mask;

int cpu_cycles_read, cpu_cycles_read_l, cpu_cycles_write, cpu_cycles_write_l;
int cpu_prefetch_cycles, cpu_prefetch_width, cpu_mem_prefetch_cycles, cpu_rom_prefetch_cycles;
int cpu_waitstates;
int cpu_cache_int_enabled, cpu_cache_ext_enabled;

int is386;
int is486;
int CPUID;

uint64_t tsc = 0;

int timing_rr;
int timing_mr, timing_mrl;
int timing_rm, timing_rml;
int timing_mm, timing_mml;
int timing_bt, timing_bnt;
int timing_int, timing_int_rm, timing_int_v86, timing_int_pm, timing_int_pm_outer;
int timing_iret_rm, timing_iret_v86, timing_iret_pm, timing_iret_pm_outer;
int timing_call_rm, timing_call_pm, timing_call_pm_gate, timing_call_pm_gate_inner;
int timing_retf_rm, timing_retf_pm, timing_retf_pm_outer;
int timing_jmp_rm, timing_jmp_pm, timing_jmp_pm_gate;
int timing_misaligned;

static struct {
        uint32_t tr1, tr12;
        uint32_t cesr;
        uint32_t fcr;
        uint64_t fcr2, fcr3;
} msr;

void cpu_set_edx() { EDX = models[model]->cpu[cpu_manufacturer].cpus[cpu].edx_reset; }

int fpu_get_type(int model, int manu, int cpu, const char *internal_name) {
        CPU *cpu_s = &models[model]->cpu[manu].cpus[cpu];
        const FPU *fpus = cpu_s->fpus;
        int fpu_type = fpus[0].type;
        int c = 0;

        while (fpus[c].internal_name) {
                if (!strcmp(internal_name, fpus[c].internal_name))
                        fpu_type = fpus[c].type;
                c++;
        }

        return fpu_type;
}

const char *fpu_get_internal_name(int model, int manu, int cpu, int type) {
        CPU *cpu_s = &models[model]->cpu[manu].cpus[cpu];
        const FPU *fpus = cpu_s->fpus;
        int c = 0;

        while (fpus[c].internal_name) {
                if (fpus[c].type == type)
                        return fpus[c].internal_name;
                c++;
        }

        return fpus[0].internal_name;
}

const char *fpu_get_name_from_index(int model, int manu, int cpu, int c) {
        CPU *cpu_s = &models[model]->cpu[manu].cpus[cpu];
        const FPU *fpus = cpu_s->fpus;

        return fpus[c].name;
}

int fpu_get_type_from_index(int model, int manu, int cpu, int c) {
        CPU *cpu_s = &models[model]->cpu[manu].cpus[cpu];
        const FPU *fpus = cpu_s->fpus;

        return fpus[c].type;
}

CPU *cpu_s;

void cpu_set() {
        if (!models[model]->cpu[cpu_manufacturer].cpus) {
                /*CPU is invalid, set to default*/
                cpu_manufacturer = 0;
                cpu = 0;
        }

        cpu_s = &models[model]->cpu[cpu_manufacturer].cpus[cpu];

        CPUID = cpu_s->cpuid_model;
        cpuspeed = cpu_s->speed;
        hasfpu = (fpu_type != FPU_NONE);

        if (cpu_s->multi)
                cpu_busspeed = cpu_s->rspeed / cpu_s->multi;
        cpu_multi = cpu_s->multi;
        ccr0 = ccr1 = ccr2 = ccr3 = ccr4 = ccr5 = ccr6 = 0;

        cpu_turbo_speed = cpu_s->rspeed;

        cpu_nonturbo_speed = 4772728;
        cpu_turbo = 1;

        cpu_update_waitstates();

        isa_cycles = cpu_s->atclk_div;

        if (cpu_s->rspeed <= 8000000)
                cpu_rom_prefetch_cycles = cpu_mem_prefetch_cycles;
        else
                cpu_rom_prefetch_cycles = cpu_s->rspeed / 1000000;

        if (cpu_s->pci_speed) {
                pci_nonburst_time = 4 * cpu_s->rspeed / cpu_s->pci_speed;
                pci_burst_time = cpu_s->rspeed / cpu_s->pci_speed;
        } else {
                pci_nonburst_time = 4;
                pci_burst_time = 1;
        }
        pclog("PCI burst=%i nonburst=%i\n", pci_burst_time, pci_nonburst_time);

        pclog("hasfpu - %i\n", hasfpu);
        pclog("is486 - %i  %i\n", is486, cpu_s->cpu_type);

        x86_setopcodes(ops_386, ops_386_0f, dynarec_ops_386, dynarec_ops_386_0f);
        x86_opcodes_REPE = ops_REPE;
        x86_opcodes_REPNE = ops_REPNE;
        x86_opcodes_3DNOW = ops_3DNOW;
        x86_dynarec_opcodes_REPE = dynarec_ops_REPE;
        x86_dynarec_opcodes_REPNE = dynarec_ops_REPNE;
        x86_dynarec_opcodes_3DNOW = dynarec_ops_3DNOW;

        if (hasfpu) {
                x86_dynarec_opcodes_d8_a16 = dynarec_ops_fpu_d8_a16;
                x86_dynarec_opcodes_d8_a32 = dynarec_ops_fpu_d8_a32;
                x86_dynarec_opcodes_d9_a16 = dynarec_ops_fpu_d9_a16;
                x86_dynarec_opcodes_d9_a32 = dynarec_ops_fpu_d9_a32;
                x86_dynarec_opcodes_da_a16 = dynarec_ops_fpu_da_a16;
                x86_dynarec_opcodes_da_a32 = dynarec_ops_fpu_da_a32;
                x86_dynarec_opcodes_db_a16 = dynarec_ops_fpu_db_a16;
                x86_dynarec_opcodes_db_a32 = dynarec_ops_fpu_db_a32;
                x86_dynarec_opcodes_dc_a16 = dynarec_ops_fpu_dc_a16;
                x86_dynarec_opcodes_dc_a32 = dynarec_ops_fpu_dc_a32;
                x86_dynarec_opcodes_dd_a16 = dynarec_ops_fpu_dd_a16;
                x86_dynarec_opcodes_dd_a32 = dynarec_ops_fpu_dd_a32;
                x86_dynarec_opcodes_de_a16 = dynarec_ops_fpu_de_a16;
                x86_dynarec_opcodes_de_a32 = dynarec_ops_fpu_de_a32;
                x86_dynarec_opcodes_df_a16 = dynarec_ops_fpu_df_a16;
                x86_dynarec_opcodes_df_a32 = dynarec_ops_fpu_df_a32;
        } else {
                x86_dynarec_opcodes_d8_a16 = dynarec_ops_nofpu_a16;
                x86_dynarec_opcodes_d8_a32 = dynarec_ops_nofpu_a32;
                x86_dynarec_opcodes_d9_a16 = dynarec_ops_nofpu_a16;
                x86_dynarec_opcodes_d9_a32 = dynarec_ops_nofpu_a32;
                x86_dynarec_opcodes_da_a16 = dynarec_ops_nofpu_a16;
                x86_dynarec_opcodes_da_a32 = dynarec_ops_nofpu_a32;
                x86_dynarec_opcodes_db_a16 = dynarec_ops_nofpu_a16;
                x86_dynarec_opcodes_db_a32 = dynarec_ops_nofpu_a32;
                x86_dynarec_opcodes_dc_a16 = dynarec_ops_nofpu_a16;
                x86_dynarec_opcodes_dc_a32 = dynarec_ops_nofpu_a32;
                x86_dynarec_opcodes_dd_a16 = dynarec_ops_nofpu_a16;
                x86_dynarec_opcodes_dd_a32 = dynarec_ops_nofpu_a32;
                x86_dynarec_opcodes_de_a16 = dynarec_ops_nofpu_a16;
                x86_dynarec_opcodes_de_a32 = dynarec_ops_nofpu_a32;
                x86_dynarec_opcodes_df_a16 = dynarec_ops_nofpu_a16;
                x86_dynarec_opcodes_df_a32 = dynarec_ops_nofpu_a32;
        }
        codegen_timing_set(&codegen_timing_486);

        if (hasfpu) {
                x86_opcodes_d8_a16 = ops_fpu_d8_a16;
                x86_opcodes_d8_a32 = ops_fpu_d8_a32;
                x86_opcodes_d9_a16 = ops_fpu_d9_a16;
                x86_opcodes_d9_a32 = ops_fpu_d9_a32;
                x86_opcodes_da_a16 = ops_fpu_da_a16;
                x86_opcodes_da_a32 = ops_fpu_da_a32;
                x86_opcodes_db_a16 = ops_fpu_db_a16;
                x86_opcodes_db_a32 = ops_fpu_db_a32;
                x86_opcodes_dc_a16 = ops_fpu_dc_a16;
                x86_opcodes_dc_a32 = ops_fpu_dc_a32;
                x86_opcodes_dd_a16 = ops_fpu_dd_a16;
                x86_opcodes_dd_a32 = ops_fpu_dd_a32;
                x86_opcodes_de_a16 = ops_fpu_de_a16;
                x86_opcodes_de_a32 = ops_fpu_de_a32;
                x86_opcodes_df_a16 = ops_fpu_df_a16;
                x86_opcodes_df_a32 = ops_fpu_df_a32;
        } else {
                x86_opcodes_d8_a16 = ops_nofpu_a16;
                x86_opcodes_d8_a32 = ops_nofpu_a32;
                x86_opcodes_d9_a16 = ops_nofpu_a16;
                x86_opcodes_d9_a32 = ops_nofpu_a32;
                x86_opcodes_da_a16 = ops_nofpu_a16;
                x86_opcodes_da_a32 = ops_nofpu_a32;
                x86_opcodes_db_a16 = ops_nofpu_a16;
                x86_opcodes_db_a32 = ops_nofpu_a32;
                x86_opcodes_dc_a16 = ops_nofpu_a16;
                x86_opcodes_dc_a32 = ops_nofpu_a32;
                x86_opcodes_dd_a16 = ops_nofpu_a16;
                x86_opcodes_dd_a32 = ops_nofpu_a32;
                x86_opcodes_de_a16 = ops_nofpu_a16;
                x86_opcodes_de_a32 = ops_nofpu_a32;
                x86_opcodes_df_a16 = ops_nofpu_a16;
                x86_opcodes_df_a32 = ops_nofpu_a32;
        }

        memset(&msr, 0, sizeof(msr));

        timing_misaligned = 0;
        cpu_cyrix_alignment = 0;
        cpu_CR4_mask = 0;

        switch (cpu_s->cpu_type) {
        case CPU_8088:
                break;

        default:
                fatal("cpu_set : unknown CPU type %i\n", cpu_s->cpu_type);
        }

        switch (fpu_type) {
        case FPU_NONE:
                break;

        case FPU_8087:
                x87_timings = x87_timings_8087;
                break;

        case FPU_287:
                x87_timings = x87_timings_287;
                break;

        case FPU_287XL:
        case FPU_387:
                x87_timings = x87_timings_387;
                break;

        default:
                x87_timings = x87_timings_486;
                break;
        }
}

void cpu_CPUID() {}

void cpu_RDMSR() {}

void cpu_WRMSR() {}

static int cyrix_addr;

#define CCR1_USE_SMI (1 << 1)
#define CCR1_SMAC (1 << 2)
#define CCR1_SM3 (1 << 7)

#define CCR3_SMI_LOCK (1 << 0)
#define CCR3_NMI_EN (1 << 1)

void x86_setopcodes(OpFn *opcodes, OpFn *opcodes_0f, OpFn *dynarec_opcodes, OpFn *dynarec_opcodes_0f) {
        x86_opcodes = opcodes;
        x86_opcodes_0f = opcodes_0f;
        x86_dynarec_opcodes = dynarec_opcodes;
        x86_dynarec_opcodes_0f = dynarec_opcodes_0f;
}

void cpu_update_waitstates() {
        cpu_s = &models[model]->cpu[cpu_manufacturer].cpus[cpu];

        if (is486)
                cpu_prefetch_width = 16;
        else
                cpu_prefetch_width = cpu_16bitbus ? 2 : 4;

        if (cpu_cache_int_enabled) {
                /* Disable prefetch emulation */
                cpu_prefetch_cycles = 0;
        } else if (cpu_cache_ext_enabled) {
                /* Use cache timings */
                cpu_prefetch_cycles = cpu_s->cache_read_cycles;
                cpu_cycles_read = cpu_s->cache_read_cycles;
                cpu_cycles_read_l = (cpu_16bitbus ? 2 : 1) * cpu_s->cache_read_cycles;
                cpu_cycles_write = cpu_s->cache_write_cycles;
                cpu_cycles_write_l = (cpu_16bitbus ? 2 : 1) * cpu_s->cache_write_cycles;
        } else {
                /* Use memory timings */
                cpu_prefetch_cycles = cpu_s->mem_read_cycles;
                cpu_cycles_read = cpu_s->mem_read_cycles;
                cpu_cycles_read_l = (cpu_16bitbus ? 2 : 1) * cpu_s->mem_read_cycles;
                cpu_cycles_write = cpu_s->mem_write_cycles;
                cpu_cycles_write_l = (cpu_16bitbus ? 2 : 1) * cpu_s->mem_write_cycles;
        }
        if (is486)
                cpu_prefetch_cycles = (cpu_prefetch_cycles * 11) / 16;
        cpu_mem_prefetch_cycles = cpu_prefetch_cycles;
        if (cpu_s->rspeed <= 8000000)
                cpu_rom_prefetch_cycles = cpu_mem_prefetch_cycles;
}

void cpu_set_turbo(int turbo) {
        if (cpu_turbo != turbo) {
                cpu_turbo = turbo;

                cpu_s = &models[model]->cpu[cpu_manufacturer].cpus[cpu];
               
                setpitclock(14318184.0);
        }
}

int cpu_get_turbo() { return cpu_turbo; }

int cpu_get_speed() {
        if (cpu_turbo)
                return cpu_turbo_speed;
        return cpu_nonturbo_speed;
}

void cpu_set_nonturbo_divider(int divider) {
        if (divider < 2)
                cpu_set_turbo(1);
        else {
                cpu_nonturbo_speed = cpu_turbo_speed / divider;
                cpu_set_turbo(0);
        }
}
