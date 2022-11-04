#ifndef __INTERFLOP_VALGRIND_CHECKDENORMAL_H__
#define __INTERFLOP_VALGRIND_CHECKDENORMAL_H__

extern struct interflop_backend_interface_t backend_checkdenormal;
extern void *backend_checkdenormal_context;

void interflop_valgrind_checkdenormal_init(void);

#endif /* __INTERFLOP_VALGRIND_CHECKDENORMAL_H__ */