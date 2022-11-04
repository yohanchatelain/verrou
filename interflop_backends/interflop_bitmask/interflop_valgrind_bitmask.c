#include "interflop_valgrind_bitmask.h"
#include "../../interflop_valgrind_stdlib.h"
#include "../../vr_main.h"
#include "interflop/interflop_bitmask.h"

struct interflop_backend_interface_t backend_bitmask = {NULL};
void *backend_bitmask_context = NULL;

void interflop_valgrind_bitmask_set_env_cli(void) {
  vr_env_clo("VERROU_BITMASK_PRECISION_BINARY64",
             "--bitmask-precision-binary64");
  vr_env_clo("VERROU_BITMASK_PRECISION_BINARY32",
             "--bitmask-precision-binary32");
  vr_env_clo("VERROU_BITMASK_MODE", "--bitmask-mode");
  vr_env_clo("VERROU_BITMASK_OPERATOR", "--bitmask-operator");
  vr_env_clo("VERROU_BITMASK_DAZ", "--bitmask-daz");
  vr_env_clo("VERROU_BITMASK_FTZ", "--bitmask-ftz");
}

void interflop_valgrind_bitmask_init(void) {
  // bitmask Backend Initilisation
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
  interflop_bitmask_pre_init(VG_(tool_panic), _stderr,
                             &backend_bitmask_context);

  VG_(umsg)
  ("Backend %s : %s\n", interflop_bitmask_get_backend_name(),
   interflop_bitmask_get_backend_version());

  bitmask_conf_t bitmask_conf = {
      .seed = vr.firstSeed,
      .binary32_precision = vr.bitmask_binary32_precision,
      .binary64_precision = vr.bitmask_binary64_precision,
      .mode = vr.bitmask_mode,
      .operator= vr.bitmask_operator,
      .daz = vr.bitmask_daz,
      .ftz = vr.bitmask_ftz};

  interflop_bitmask_configure(&bitmask_conf, backend_bitmask_context);
  backend_bitmask = interflop_bitmask_init(backend_bitmask_context);
};

void interflop_valgrind_bitmask_finalize(void) {
  if (backend_bitmask.interflop_finalize != NULL) {
    backend_bitmask.interflop_finalize(backend_bitmask_context);
  }
}