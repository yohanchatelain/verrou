#include "interflop_valgrind_checkdenormal.h"
#include "../../interflop_valgrind_stdlib.h"
#include "../../vr_main.h"
#include "interflop/interflop_checkdenormal.h"

struct interflop_backend_interface_t backend_checkdenormal;
void *backend_checkdenormal_context = NULL;

void interflop_valgrind_checkdenormal_init() {
  // CheckDenormal Backend Initilisation
  interflop_set_handler("denormalHandler", vr_handle_CD);
  interflop_set_handler("exit", _interflop_valgrind_exit);
  interflop_set_handler("fopen", _interflop_valgrind_fopen);
  interflop_set_handler("fprintf", _interflop_valgrind_fprintf);
  interflop_set_handler("getenv", _interflop_valgrind_getenv);
  interflop_set_handler("gettid", _interflop_valgrind_gettid);
  interflop_set_handler("malloc", _interflop_valgrind_malloc);
  interflop_set_handler("sprintf", _interflop_valgrind_sprintf);
  interflop_set_handler("strcasecmp", _interflop_valgrind_strcasecmp);
  interflop_set_handler("strerror", _interflop_valgrind_strerror);
  interflop_set_handler("strtol", _interflop_valgrind_strtol);
  interflop_set_handler("vfprintf", _interflop_valgrind_vfprintf);
  interflop_set_handler("vwarnx", _interflop_valgrind_vwarnx);

  VgFile *_stderr = _interflop_stderr();
  interflop_checkdenormal_pre_init(VG_(tool_panic), _stderr,
                                   &backend_checkdenormal_context);

  checkdenormal_conf_t conf = {.flushtozero = vr.ftz};

  interflop_checkdenormal_configure(&conf, backend_checkdenormal_context);
  backend_checkdenormal =
      interflop_checkdenormal_init(backend_checkdenormal_context);

  VG_(umsg)
  ("Backend %s : %s\n", interflop_checkdenormal_get_backend_name(),
   interflop_checkdenormal_get_backend_version());
};
