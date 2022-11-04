#include "interflop_valgrind_cancellation.h"
#include "../../interflop_valgrind_stdlib.h"
#include "../../vr_main.h"
#include "interflop/interflop_cancellation.h"

struct interflop_backend_interface_t backend_cancellation = {NULL};
void *backend_cancellation_context = NULL;

void interflop_valgrind_cancellation_set_env_cli(void) {
  vr_env_clo("VERROU_CANCELLATION_TOLERANCE", "--cancellation-tolerance");
  vr_env_clo("VERROU_CANCELLATION_WARNING", "--cancellation-warning");
}

void interflop_valgrind_cancellation_init(void) {
  // cancellation Backend Initilisation
  interflop_set_handler("exit", _interflop_valgrind_exit);
  interflop_set_handler("fopen", _interflop_valgrind_fopen);
  interflop_set_handler("fprintf", _interflop_valgrind_fprintf);
  interflop_set_handler("getenv", _interflop_valgrind_getenv);
  interflop_set_handler("gettid", _interflop_valgrind_gettid);
  interflop_set_handler("malloc", _interflop_valgrind_malloc);
  interflop_set_handler("sprintf", _interflop_valgrind_sprintf);
  interflop_set_handler("strcasecmp", _interflop_valgrind_strcasecmp);
  interflop_set_handler("strerror", _interflop_valgrind_strerror);
  interflop_set_handler("strtod", _interflop_valgrind_strtod);
  interflop_set_handler("strtol", _interflop_valgrind_strtol);
  interflop_set_handler("vfprintf", _interflop_valgrind_vfprintf);
  interflop_set_handler("vwarnx", _interflop_valgrind_vwarnx);
  interflop_set_handler("gettimeofday", _interflop_valgrind_gettimeofday);

  VgFile *_stderr = _interflop_stderr();
  interflop_cancellation_pre_init(VG_(tool_panic), _stderr,
                                  &backend_cancellation_context);

  VG_(umsg)
  ("Backend %s : %s\n", interflop_cancellation_get_backend_name(),
   interflop_cancellation_get_backend_version());

  cancellation_conf_t cancellation_conf = {.seed = vr.firstSeed,
                                           .tolerance =
                                               vr.cancellation_tolerance,
                                           .warning = vr.cancellation_warning};

  interflop_cancellation_configure(&cancellation_conf,
                                   backend_cancellation_context);
  backend_cancellation =
      interflop_cancellation_init(backend_cancellation_context);
};

void interflop_valgrind_cancellation_finalize(void) {
  if (backend_cancellation.interflop_finalize != NULL) {
    backend_cancellation.interflop_finalize(backend_cancellation_context);
  }
}