#ifndef __INTERFLOP_VPREC_H__
#define __INTERFLOP_VPREC_H__

#include <stdbool.h>

typedef enum {
  KEY_PREC_B32,
  KEY_PREC_B64,
  KEY_RANGE_B32,
  KEY_RANGE_B64,
  KEY_ERR_EXP,
  KEY_INPUT_FILE,
  KEY_OUTPUT_FILE,
  KEY_LOG_FILE,
  KEY_PRESET,
  KEY_MODE = 'm',
  KEY_ERR_MODE = 'e',
  KEY_INSTRUMENT = 'i',
  KEY_DAZ = 'd',
  KEY_FTZ = 'f'
} key_args;

static const char key_prec_b32_str[] = "precision-binary32";
static const char key_prec_b64_str[] = "precision-binary64";
static const char key_range_b32_str[] = "range-binary32";
static const char key_range_b64_str[] = "range-binary64";
static const char key_input_file_str[] = "prec-input-file";
static const char key_output_file_str[] = "prec-output-file";
static const char key_log_file_str[] = "prec-log-file";
static const char key_preset_str[] = "preset";
static const char key_mode_str[] = "mode";
static const char key_err_mode_str[] = "error-mode";
static const char key_err_exp_str[] = "max-abs-error-exponent";
static const char key_instrument_str[] = "instrument";
static const char key_daz_str[] = "daz";
static const char key_ftz_str[] = "ftz";

typedef struct {
  bool relErr;
  bool absErr;
  int absErr_exp;
  bool daz;
  bool ftz;
} t_context;

/* define the available VPREC modes of operation */
typedef enum {
  vprecmode_ieee,
  vprecmode_full,
  vprecmode_ib,
  vprecmode_ob,
  _vprecmode_end_
} vprec_mode;

/* define the available error modes */
typedef enum {
  vprec_err_mode_rel,
  vprec_err_mode_abs,
  vprec_err_mode_all,
  _vprec_err_end_
} vprec_err_mode;

/* define the possible VPREC operation */
typedef enum {
  vprec_add = '+',
  vprec_sub = '-',
  vprec_mul = '*',
  vprec_div = '/',
  vprec_fma = 'f',
} vprec_operation;

/* define the possible VPREC preset */
typedef enum {
  preset_binary16,
  preset_binary32,
  preset_bfloat16,
  preset_tensorfloat,
  preset_fp24,
  preset_PXR24,
  _preset_end_
} vprec_preset;

typedef enum {
  preset_precision_binary16 = 10,
  preset_precision_binary32 = 23,
  preset_precision_bfloat16 = 7,
  preset_precision_tensorfloat = 10,
  preset_precision_fp24 = 16,
  preset_precision_PXR24 = 15,
  _preset_precision_end_,
} vprec_preset_precision;

typedef enum {
  preset_range_binary16 = 5,
  preset_range_binary32 = 8,
  preset_range_bfloat16 = 8,
  preset_range_tensorfloat = 8,
  preset_range_fp24 = 7,
  preset_range_PXR24 = 8,
  _preset_range_end_
} vprec_preset_range;

/* define default environment variables and default parameters */

/* default values of precision and range for binary32 */
#define VPREC_PRECISION_BINARY32_MIN 1
#define VPREC_PRECISION_BINARY32_MAX FLOAT_PMAN_SIZE
#define VPREC_PRECISION_BINARY32_DEFAULT FLOAT_PMAN_SIZE
#define VPREC_RANGE_BINARY32_MIN 2
#define VPREC_RANGE_BINARY32_MAX FLOAT_EXP_SIZE
#define VPREC_RANGE_BINARY32_DEFAULT FLOAT_EXP_SIZE

/* default values of precision and range for binary64 */
#define VPREC_PRECISION_BINARY64_MIN 1
#define VPREC_PRECISION_BINARY64_MAX DOUBLE_PMAN_SIZE
#define VPREC_PRECISION_BINARY64_DEFAULT DOUBLE_PMAN_SIZE
#define VPREC_RANGE_BINARY64_MIN 2
#define VPREC_RANGE_BINARY64_MAX DOUBLE_EXP_SIZE
#define VPREC_RANGE_BINARY64_DEFAULT DOUBLE_EXP_SIZE

/* common default values */
#define VPREC_MODE_DEFAULT vprecmode_ob

/* configure structure for Verrou frontend */
typedef struct {
  unsigned int precision_binary32;
  unsigned int range_binary32;
  unsigned int precision_binary64;
  unsigned int range_binary64;
  vprec_mode mode;
  vprec_preset preset;
  vprec_err_mode err_mode;
  long max_abs_err_exponent;
  unsigned int daz;
  unsigned int ftz;
} vprec_conf_t;

const char *get_vprec_mode_name(vprec_mode mode);
extern void (*vprec_panicHandler)(const char *);
void vprec_set_panic_handler(void (*panicHandler)(const char *));

extern void (*vprec_debug_print_op)(int, const char *, const double *,
                                    const double *);
void vprec_set_debug_print_op(void (*printOpHandler)(
    int nbArg, const char *name, const double *args, const double *res));

/* Interflop API */
const char *interflop_vprec_get_backend_name(void);
const char *interflop_vprec_get_backend_version(void);
struct interflop_backend_interface_t interflop_vprec_init(int argc, char **argv,
                                                          void **context);

void interflop_vprec_configure(vprec_conf_t conf, void *context);
void interflop_vprec_add_float(float a, float b, float *c, void *context);
void interflop_vprec_sub_float(float a, float b, float *c, void *context);
void interflop_vprec_mul_float(float a, float b, float *c, void *context);
void interflop_vprec_div_float(float a, float b, float *c, void *context);
void interflop_vprec_add_double(double a, double b, double *c, void *context);
void interflop_vprec_sub_double(double a, double b, double *c, void *context);
void interflop_vprec_mul_double(double a, double b, double *c, void *context);
void interflop_vprec_div_double(double a, double b, double *c, void *context);
void interflop_vprec_cast_double_to_float(double a, float *b, void *context);
void interflop_vprec_madd_float(float a, float b, float c, float *res,
                                void *context);
void interflop_vprec_madd_double(double a, double b, double c, double *res,
                                 void *context);
void interflop_vprec_enter_function(interflop_function_stack_t *stack,
                                    void *context, int nb_args, va_list ap);
void interflop_vprec_exit_function(interflop_function_stack_t *stack,
                                   void *context, int nb_args, va_list ap);

void interflop_vprec_user_call(void *context, interflop_call_id id, va_list ap);
void interflop_vprec_finalize(void *context);

#endif /* __INTERFLOP_VPREC_H__ */
