#include "interflop_valgrind_mcaint.h"
#include "../../interflop_valgrind_stdlib.h"
#include "../../vr_main.h"
#include "interflop/interflop_mca_int.h"

struct interflop_backend_interface_t backend_mcaint = {NULL};
void *backend_mcaint_context = NULL;

void interflop_valgrind_mcaint_set_env_cli(void) {
  vr_env_clo("VERROU_MCAINT_PRECISION_BINARY64", "--mcaint-precision-binary64");
  vr_env_clo("VERROU_MCAINT_PRECISION_BINARY32", "--mcaint-precision-binary32");
  vr_env_clo("VERROU_MCAINT_MODE", "--mcaint-mode");
  vr_env_clo("VERROU_MCAINT_DAZ", "--mcaint-daz");
  vr_env_clo("VERROU_MCAINT_FTZ", "--mcaint-ftz");
}

void interflop_valgrind_mcaint_init(void) {
  // mcaint Backend Initilisation
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
  interflop_mcaint_pre_init(VG_(tool_panic), _stderr, &backend_mcaint_context);

  VG_(umsg)
  ("Backend %s : %s\n", interflop_mcaint_get_backend_name(),
   interflop_mcaint_get_backend_version());

  mcaint_conf_t mcaint_conf = {
      .seed = vr.firstSeed,
      .sparsity = vr.mcaint_sparsity,
      .precision_binary32 = vr.mcaint_binary32_precision,
      .precision_binary64 = vr.mcaint_binary64_precision,
      .mode = vr.mcaint_mode,
      .err_mode = vr.mcaint_err_mode,
      .max_abs_err_exponent = vr.mcaint_max_abs_err_exponent,
      .daz = vr.mcaint_daz,
      .ftz = vr.mcaint_ftz};

  interflop_mcaint_configure(&mcaint_conf, backend_mcaint_context);
  backend_mcaint = interflop_mcaint_init(backend_mcaint_context);
};

void interflop_valgrind_mcaint_finalize(void) {
  if (backend_mcaint.interflop_finalize != NULL) {
    backend_mcaint.interflop_finalize(backend_mcaint_context);
  }
}