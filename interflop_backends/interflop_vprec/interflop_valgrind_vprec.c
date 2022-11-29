
#include "interflop_valgrind_vprec.h"
#include "../../interflop_valgrind_stdlib.h"
#include "vr_main.h"

struct interflop_backend_interface_t backend_vprec;

void *backend_vprec_context = NULL;

void interflop_valgrind_vprec_set_env_cli() {
  vr_env_clo("VERROU_VPREC_PRECISION_BINARY64", "--vprec-precision-binary64");
  vr_env_clo("VERROU_VPREC_RANGE_BINARY64", "--vprec-range-binary64");
  vr_env_clo("VERROU_VPREC_PRECISION_BINARY32", "--vprec-precision-binary32");
  vr_env_clo("VERROU_VPREC_RANGE_BINARY32", "--vprec-range-binary32");
  vr_env_clo("VERROU_VPREC_MODE", "--vprec-mode");
  vr_env_clo("VERROU_VPREC_PRESET", "--vprec-preset");
  vr_env_clo("VERROU_VPREC_ERROR_MODE", "--vprec-error-mode");
  vr_env_clo("VERROU_VPREC_MAX_ERROR_EXPONENT",
             "--vprec-max-abs-error-exponent");
  vr_env_clo("VERROU_VPREC_DAZ", "--vprec-daz");
  vr_env_clo("VERROU_VPREC_FTZ", "--vprec-ftz");
}

void interflop_valgrind_vprec_init() {
  interflop_set_handler("malloc", _interflop_valgrind_malloc);
  interflop_set_handler("fopen", _interflop_valgrind_fopen);
  interflop_set_handler("strcmp", _interflop_valgrind_strcmp);
  interflop_set_handler("strcasecmp", _interflop_valgrind_strcasecmp);
  interflop_set_handler("strtol", _interflop_valgrind_strtol);
  interflop_set_handler("getenv", _interflop_valgrind_getenv);
  interflop_set_handler("fprintf", _interflop_valgrind_fprintf);
  interflop_set_handler("strcpy", _interflop_valgrind_strcpy);
  interflop_set_handler("fclose", _interflop_valgrind_fclose);
  interflop_set_handler("gettid", _interflop_valgrind_gettid);
  interflop_set_handler("strerror", _interflop_valgrind_strerror);
  interflop_set_handler("sprintf", _interflop_valgrind_sprintf);
  interflop_set_handler("vwarnx", _interflop_valgrind_vwarnx);
  interflop_set_handler("vfprintf", _interflop_valgrind_vfprintf);
  interflop_set_handler("exit", _interflop_valgrind_exit);
  interflop_set_handler("strtok_r", _interflop_valgrind_strtok_r);
  interflop_set_handler("fgets", _interflop_valgrind_fgets);
  interflop_set_handler("free", _interflop_valgrind_free);
  interflop_set_handler("calloc", _interflop_valgrind_calloc);

  VgFile *_stderr = _interflop_stderr();
  interflop_vprec_pre_init(_stderr, VG_(tool_panic), &backend_vprec_context);

  VG_(umsg)
  ("Backend %s : %s\n", interflop_vprec_get_backend_name(),
   interflop_vprec_get_backend_version());

  vprec_conf_t vprec_conf = {.precision_binary32 = vr.vprec_precision_binary32,
                             .range_binary32 = vr.vprec_range_binary32,
                             .precision_binary64 = vr.vprec_precision_binary64,
                             .range_binary64 = vr.vprec_range_binary64,
                             .mode = vr.vprec_mode,
                             .preset = vr.vprec_preset,
                             .err_mode = vr.vprec_error_mode,
                             .max_abs_err_exponent =
                                 vr.vprec_max_abs_error_exponent,
                             .daz = vr.vprec_daz,
                             .ftz = vr.vprec_ftz};

  interflop_vprec_configure(vprec_conf, backend_vprec_context);

  backend_vprec = interflop_vprec_init(backend_vprec_context);
}