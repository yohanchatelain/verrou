#ifndef __INTERFLOP_VALGRIND_VERROU_H__
#define __INTERFLOP_VALGRIND_VERROU_H__

extern struct interflop_backend_interface_t backend_verrou;
extern void *backend_verrou_context;

void interflop_valgrind_verrou_init(void);

#endif /* __INTERFLOP_VALGRIND_VERROU_H__ */