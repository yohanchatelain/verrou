#ifndef __INTERFLOP_VALGRIND_BITMASK_H__
#define __INTERFLOP_VALGRIND_BITMASK_H__

extern struct interflop_backend_interface_t backend_bitmask;
extern void *backend_bitmask_context;

void interflop_valgrind_bitmask_set_env_cli(void);
void interflop_valgrind_bitmask_init(void);
void interflop_valgrind_bitmask_finalize(void);

#endif /* __INTERFLOP_VALGRIND_BITMASK_H__ */