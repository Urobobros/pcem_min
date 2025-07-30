#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include "config.h"
#include "paths.h"
#include "ibm.h"

static FILE *portlogf = NULL;
static uint64_t portlog_start_time = 0;

static int portlog_start() {
#ifndef RELEASE_BUILD
    if (!portlogf) {
        char buf[1024];
        strcpy(buf, logs_path);
        put_backslash(buf);
        strcat(buf, "port.log");
        portlogf = fopen(buf, "wt");
        if (!portlogf) {
            fprintf(stderr, "Could not open port log file for writing: %s", strerror(errno));
            return 0;
        }
        portlog_start_time = timer_read();
    }
    return 1;
#else
    return 0;
#endif
}

void portlog_flush() {
#ifndef RELEASE_BUILD
    if (portlogf)
        fflush(portlogf);
#endif
}

void portlog_end() {
#ifndef RELEASE_BUILD
    if (portlogf) {
        fflush(portlogf);
        fclose(portlogf);
        portlogf = NULL;
    }
#endif
}

void portlog(const char *format, ...) {
#ifndef RELEASE_BUILD
    char buf[1024];
    if (!portlog_start())
        return;
    if (!portlog_start_time)
        portlog_start_time = timer_read();
    uint64_t now = timer_read();
    double ms = ((double)(now - portlog_start_time) * 1000.0) /
                (double)timer_freq;
    va_list ap;
    va_start(ap, format);
    vsprintf(buf, format, ap);
    va_end(ap);
    fprintf(portlogf, "[%10.3f ms] %s", ms, buf);
    fflush(portlogf);
#endif
}
