#include "interflop_valgrind_checkcancellation.h"
#include "../../interflop_valgrind_stdlib.h"
#include "../../vr_main.h"
#include "interflop/interflop_checkcancellation.h"

struct interflop_backend_interface_t backend_checkcancellation;
void *backend_checkcancellation_context = NULL;

void interflop_valgrind_checkcancellation_init() {
  // Verrou Backend Initilisation
  interflop_set_handler("cancellationHandler", vr_handle_CC);
  interflop_set_handler("exit", _interflop_valgrind_exit);
  interflop_set_handler("fprintf", _interflop_valgrind_fprintf);
  interflop_set_handler("malloc", _interflop_valgrind_malloc);
  interflop_set_handler("strcasecmp", _interflop_valgrind_strcasecmp);
  interflop_set_handler("strtol", _interflop_valgrind_strtol);

  VgFile *_stderr = _interflop_stderr();
  interflop_checkcancellation_pre_init(VG_(tool_panic), _stderr,
                                       &backend_checkcancellation_context);

  checkcancellation_conf_t conf = {.threshold_b32 = 0, .threshold_b64 = 0};

  interflop_checkcancellation_configure(&conf,
                                        backend_checkcancellation_context);
  backend_checkcancellation =
      interflop_checkcancellation_init(backend_checkcancellation_context);

  VG_(umsg)
  ("Backend %s : %s\n", interflop_checkcancellation_get_backend_name(),
   interflop_checkcancellation_get_backend_version());
};
