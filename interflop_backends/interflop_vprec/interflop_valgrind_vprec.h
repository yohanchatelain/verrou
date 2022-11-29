#ifndef _INTERFLOP_VALGRIND_VPREC_H__
#define _INTERFLOP_VALGRIND_VPREC_H__

extern struct interflop_backend_interface_t backend_vprec;
extern void *backend_vprec_context;

void interflop_valgrind_vprec_set_env_cli(void);
void interflop_valgrind_vprec_init(void);

#endif /* _INTERFLOP_VALGRIND_VPREC_H__ */