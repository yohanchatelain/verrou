#ifndef __INTERFLOP_VALGRIND_CANCELLATION_H__
#define __INTERFLOP_VALGRIND_CANCELLATION_H__

extern struct interflop_backend_interface_t backend_cancellation;
extern void *backend_cancellation_context;

void interflop_valgrind_cancellation_set_env_cli(void);
void interflop_valgrind_cancellation_init(void);
void interflop_valgrind_cancellation_finalize(void);

#endif /* __INTERFLOP_VALGRIND_CANCELLATION_H__ */