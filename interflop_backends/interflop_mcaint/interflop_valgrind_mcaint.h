#ifndef __INTERFLOP_VALGRIND_MCAINT_H__
#define __INTERFLOP_VALGRIND_MCAINT_H__

extern struct interflop_backend_interface_t backend_mcaint;
extern void *backend_mcaint_context;

void interflop_valgrind_mcaint_set_env_cli(void);
void interflop_valgrind_mcaint_init(void);
void interflop_valgrind_mcaint_finalize(void);

#endif /* __INTERFLOP_VALGRIND_MCAINT_H__ */