#ifndef __INTERFLOP_VALGRIND_MCAQUAD_H__
#define __INTERFLOP_VALGRIND_MCAQUAD_H__

extern struct interflop_backend_interface_t backend_mcaquad;
extern void *backend_mcaquad_context;

void interflop_valgrind_mcaquad_set_env_cli(void);
void interflop_valgrind_mcaquad_init(void);
void interflop_valgrind_mcaquad_finalize(void);

#endif /* __INTERFLOP_VALGRIND_MCAQUAD_H__ */