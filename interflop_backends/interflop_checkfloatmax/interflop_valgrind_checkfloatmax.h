#ifndef __INTERFLOP_VALGRIND_CHECKFLOATMAX_H__
#define __INTERFLOP_VALGRIND_CHECKFLOATMAX_H__

extern struct interflop_backend_interface_t backend_checkfloatmax;
extern void *backend_checkfloatmax_context;

void interflop_valgrind_checkfloatmax_init(void);

#endif /* __INTERFLOP_VALGRIND_CHECKFLOATMAX_H__ */