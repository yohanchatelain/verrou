#include "interflop_valgrind_mcaquad.h"
#include "../../interflop_valgrind_stdlib.h"
#include "../../vr_main.h"

struct interflop_backend_interface_t backend_mcaquad = {NULL};
void *backend_mcaquad_context = NULL;

void interflop_valgrind_mcaquad_set_env_cli(void) {
  vr_env_clo("VERROU_MCAQUAD_PRECISION_BINARY64",
             "--mcaquad-precision-binary64");
  vr_env_clo("VERROU_MCAQUAD_PRECISION_BINARY32",
             "--mcaquad-precision-binary32");
  vr_env_clo("VERROU_MCAQUAD_MODE", "--mcaquad-mode");
  vr_env_clo("VERROU_MCAQUAD_DAZ", "--mcaquad-daz");
  vr_env_clo("VERROU_MCAQUAD_FTZ", "--mcaquad-ftz");
}

void interflop_valgrind_mcaquad_init(void) {
  // mcaquad Backend Initilisation
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
  interflop_mcaquad_pre_init(VG_(tool_panic), _stderr,
                             &backend_mcaquad_context);

  VG_(umsg)
  ("Backend %s : %s\n", interflop_mcaquad_get_backend_name(),
   interflop_mcaquad_get_backend_version());

  mcaquad_conf_t mcaquad_conf = {
      .seed = vr.firstSeed,
      .sparsity = vr.mcaquad_sparsity,
      .precision_binary32 = vr.mcaquad_binary32_precision,
      .precision_binary64 = vr.mcaquad_binary64_precision,
      .mode = vr.mcaquad_mode,
      .err_mode = vr.mcaquad_err_mode,
      .max_abs_err_exponent = vr.mcaquad_max_abs_err_exponent,
      .daz = vr.mcaquad_daz,
      .ftz = vr.mcaquad_ftz};

  interflop_mcaquad_configure(&mcaquad_conf, backend_mcaquad_context);
  backend_mcaquad = interflop_mcaquad_init(backend_mcaquad_context);
};

void interflop_valgrind_mcaquad_finalize(void) {
  if (backend_mcaquad.interflop_finalize != NULL) {
    backend_mcaquad.interflop_finalize(backend_mcaquad_context);
  }
}