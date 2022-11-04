#include "interflop_valgrind_checkfloatmax.h"
#include "../../interflop_valgrind_stdlib.h"
#include "../../vr_main.h"
#include "interflop/interflop_checkfloatmax.h"

struct interflop_backend_interface_t backend_checkfloatmax;
void *backend_checkfloatmax_context = NULL;

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

void interflop_valgrind_checkfloatmax_init() {
  // CheckFloatMax Backend Initilisation
  interflop_set_handler("debug_print_op", print_op);
  interflop_set_handler("maxHandler", vr_handle_FLT_MAX);

  VgFile *_stderr = _interflop_stderr();
  interflop_checkfloatmax_pre_init(VG_(tool_panic), _stderr,
                                   &backend_checkfloatmax_context);

  checkfloatmax_conf_t conf = {};

  interflop_checkfloatmax_configure(&conf, backend_checkfloatmax_context);
  backend_checkfloatmax =
      interflop_checkfloatmax_init(backend_checkfloatmax_context);

  VG_(umsg)
  ("Backend %s : %s\n", interflop_checkfloatmax_get_backend_name(),
   interflop_checkfloatmax_get_backend_version());
};
