#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include "plugin-api/paths.h"
#include "func_trace.h"

static FILE *trace_file = NULL;

__attribute__((no_instrument_function))
static void open_trace(void) {
    char path[1024];
    snprintf(path, sizeof(path), "%sfunction.log", logs_path);
    trace_file = fopen(path, "w");
}

__attribute__((no_instrument_function))
void instrumentation_init(void) {
    char path[1024];
    snprintf(path, sizeof(path), "%sfunction.log", logs_path);
    unlink(path);
    if (trace_file) {
        fclose(trace_file);
    }
    trace_file = fopen(path, "w");
}

__attribute__((no_instrument_function))
void instrumentation_close(void) {
    if (trace_file) {
        fclose(trace_file);
        trace_file = NULL;
    }
}

__attribute__((no_instrument_function))
static const char *symname(void *func) {
    Dl_info info;
    if (dladdr(func, &info) && info.dli_sname)
        return info.dli_sname;
    return NULL;
}

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *func, void *caller) {
    (void)caller;
    if (!trace_file)
        open_trace();
    const char *name = symname(func);
    if (name)
        fprintf(trace_file, "ENTER %s\n", name);
    else
        fprintf(trace_file, "ENTER %p\n", func);
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *func, void *caller) {
    (void)caller;
    if (!trace_file)
        open_trace();
    const char *name = symname(func);
    if (name)
        fprintf(trace_file, "EXIT %s\n", name);
    else
        fprintf(trace_file, "EXIT %p\n", func);
}

__attribute__((no_instrument_function))
static void instrumentation_destructor(void) __attribute__((destructor));
__attribute__((no_instrument_function))
static void instrumentation_destructor(void) {
    instrumentation_close();
}
