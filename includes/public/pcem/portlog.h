#ifndef __PCEM_PORTLOG_H__
#define __PCEM_PORTLOG_H__

#ifdef __cplusplus
extern "C" {
#endif

void portlog_flush();
void portlog_end();
void portlog(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* __PCEM_PORTLOG_H__ */
