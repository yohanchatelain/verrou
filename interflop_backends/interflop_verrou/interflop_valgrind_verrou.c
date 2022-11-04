#include "interflop_valgrind_verrou.h"
#include "../../interflop_valgrind_stdlib.h"
#include "../../vr_main.h"
#include "interflop/interflop_verrou.h"

struct interflop_backend_interface_t backend_verrou;
void *backend_verrou_context = NULL;

static void print_op(int nbArg, const char *name, const double *args,
                     const double *res) {
  if (nbArg == 1) {
    VG_(umsg)("%s : %f => %f\n", name, args[0], *res);
  }
  if (nbArg == 2) {
    VG_(umsg)("%s : %f, %f => %f\n", name, args[0], args[1], *res);
  }
  if (nbArg == 3) {
    VG_(umsg)("%s : %f, %f, %f => %f\n", name, args[0], args[1], args[2], *res);
  }
}

void interflop_valgrind_verrou_init() {
  // Verrou Backend Initilisation
  interflop_set_handler("exit", _interflop_valgrind_exit);
  interflop_set_handler("fopen", _interflop_valgrind_fopen);
  interflop_set_handler("fprintf", _interflop_valgrind_fprintf);
  interflop_set_handler("getenv", _interflop_valgrind_getenv);
  interflop_set_handler("gettid", _interflop_valgrind_gettid);
  interflop_set_handler("gettimeofday", _interflop_valgrind_gettimeofday);
  interflop_set_handler("infHandler", vr_handle_Inf);
  interflop_set_handler("malloc", _interflop_valgrind_malloc);
  interflop_set_handler("nanHandler", vr_handle_NaN);
  interflop_set_handler("sprintf", _interflop_valgrind_sprintf);
  interflop_set_handler("strcasecmp", _interflop_valgrind_strcasecmp);
  interflop_set_handler("strerror", _interflop_valgrind_strerror);
  interflop_set_handler("strtol", _interflop_valgrind_strtol);
  interflop_set_handler("vfprintf", _interflop_valgrind_vfprintf);
  interflop_set_handler("vwarnx", _interflop_valgrind_vwarnx);

  // Use only verrou backend is configured to use it
  interflop_set_handler("debug_print_op", print_op);

  VgFile *_stderr = _interflop_stderr();
  interflop_verrou_pre_init(VG_(tool_panic), _stderr, &backend_verrou_context);

  verrou_conf_t conf = {.rounding_mode = vr.roundingMode,
                        .default_rounding_mode = vr.roundingMode,
                        .seed = vr.firstSeed,
                        .choose_seed = vr.chooseSeed,
                        .static_backend = vr.staticBackend};
  interflop_verrou_configure(&conf, backend_verrou_context);
  backend_verrou = interflop_verrou_init(backend_verrou_context);

#ifdef PROFILING_EXACT
  verrou_init_profiling_exact();
#endif

  VG_(umsg)
  ("Backend %s : %s\n", interflop_verrou_get_backend_name(),
   interflop_verrou_get_backend_version());
};
