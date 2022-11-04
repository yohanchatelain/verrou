
/*--------------------------------------------------------------------*/
/*--- Verrou: a FPU instrumentation tool.                          ---*/
/*--- This file contains code related command-line options.        ---*/
/*---                                                     vr_clo.c ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of Verrou, a FPU instrumentation tool.

   Copyright (C) 2014-2021 EDF
     F. Févotte     <francois.fevotte@edf.fr>
     B. Lathuilière <bruno.lathuiliere@edf.fr>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#include "vr_main.h"

void vr_env_clo(const HChar *env, const HChar *clo) {
  HChar *val = VG_(getenv)(env);
  if (val) {
    HChar tmp[256];
    VG_(snprintf)(tmp, 255, "%s=%s", clo, val);
    if (!vr_process_clo(tmp)) {
      VG_(umsg)("WARNING: unknown command-line option `%s'\n", tmp);
    }
  }
}

void vr_clo_defaults(void) {
  vr.backend = vr_verrou;
  vr.roundingMode = VR_NEAREST;
  vr.prandomUpdate = VR_PRANDOM_UPDATE_NONE;
  vr.prandomFixedInitialValue = -1.;
  vr.count = True;
  vr.instrument = VR_INSTR_ON;
  vr.verbose = False;
  vr.unsafe_llo_optim = False;

  vr.genExcludeBool = False;
  vr.exclude = NULL;
  vr.gen_exclude = NULL;
  //  vr.genAbove = NULL;

  vr.genIncludeSource = False;
  vr.includeSource = NULL;
  vr.sourceActivated = False;
  vr.excludeSourceRead = NULL;
  vr.sourceExcludeActivated = False;
  vr.genTrace = False;
  vr.includeTrace = NULL;
  vr.outputTraceRep = NULL;

  int opIt;
  for (opIt = 0; opIt < VR_OP; opIt++) {
    vr.instr_op[opIt] = False;
  }
  int vecIt;
  for (vecIt = 0; vecIt < VR_VEC; vecIt++) {
    vr.instr_vec[vecIt] = True;
  }
  vr.instr_vec[VR_VEC_SCAL] = False;

  vr.instr_prec[VR_PREC_FLT] = True;
  vr.instr_prec[VR_PREC_DBL] = True;
  vr.instr_prec[VR_PREC_DBL_TO_FLT] = True;

  vr.firstSeed = (ULong)(-1);
  vr.chooseSeed = False;
  vr.staticBackend = False;

#ifdef LINK_INTERFLOP_BACKEND_BITMASK
  vr.bitmask_binary64_precision = BITMASK_PRECISION_BINARY64_DEFAULT;
  vr.bitmask_binary32_precision = BITMASK_PRECISION_BINARY32_DEFAULT;
  vr.bitmask_mode = BITMASK_MODE_DEFAULT;
  vr.bitmask_operator = BITMASK_OPERATOR_DEFAULT;
  vr.bitmask_daz = BITMASK_DAZ_DEFAULT;
  vr.bitmask_ftz = BITMASK_FTZ_DEFAULT;
#endif

#ifdef LINK_INTERFLOP_BACKEND_CANCELLATION
  vr.cancellation_tolerance = CANCELLATION_TOLERANCE_DEFAULT;
  vr.cancellation_warning = CANCELLATION_WARNING_DEFAULT;
#endif

#ifdef LINK_INTERFLOP_BACKEND_MCAINT
  vr.mcaint_binary64_precision = MCAINT_PRECISION_BINARY64_DEFAULT;
  vr.mcaint_binary32_precision = MCAINT_PRECISION_BINARY32_DEFAULT;
  vr.mcaint_mode = MCAINT_MODE_DEFAULT;
  vr.mcaint_sparsity = MCAINT_SPARSITY_DEFAULT;
  vr.mcaint_err_mode = MCAINT_ERR_MODE_DEFAULT;
  vr.mcaint_max_abs_err_exponent = MCAINT_ABSOLUTE_ERROR_EXPONENT_DEFAULT;
  vr.mcaint_daz = MCAINT_DAZ_DEFAULT;
  vr.mcaint_ftz = MCAINT_FTZ_DEFAULT;
#endif

#ifdef LINK_INTERFLOP_BACKEND_MCAQUAD
  vr.mcaquad_binary64_precision = MCAQUAD_PRECISION_BINARY64_DEFAULT;
  vr.mcaquad_binary32_precision = MCAQUAD_PRECISION_BINARY32_DEFAULT;
  vr.mcaquad_mode = MCAQUAD_MODE_DEFAULT;
  vr.mcaquad_sparsity = MCAQUAD_SPARSITY_DEFAULT;
  vr.mcaquad_err_mode = MCAQUAD_ERR_MODE_DEFAULT;
  vr.mcaquad_max_abs_err_exponent = MCAQUAD_ABSOLUTE_ERROR_EXPONENT_DEFAULT;
  vr.mcaquad_daz = MCAQUAD_DAZ_DEFAULT;
  vr.mcaquad_ftz = MCAQUAD_FTZ_DEFAULT;
#endif

#ifdef LINK_INTERFLOP_BACKEND_VPREC
  // Default VPREC options
  vr.vprec_precision_binary64 = VPREC_PRECISION_BINARY64_DEFAULT;
  vr.vprec_range_binary64 = VPREC_RANGE_BINARY64_DEFAULT;
  vr.vprec_precision_binary32 = VPREC_PRECISION_BINARY32_DEFAULT;
  vr.vprec_range_binary32 = VPREC_RANGE_BINARY32_DEFAULT;
  vr.vprec_mode = VPREC_MODE_DEFAULT;
  vr.vprec_preset = (UInt)(-1);
  vr.vprec_error_mode = VPREC_ERR_MODE_DEFAULT;
  vr.vprec_max_abs_error_exponent = (UInt)(-1);
  vr.vprec_daz = False;
  vr.vprec_ftz = False;
#endif

  vr.checknan = True;
  vr.checkinf = True;

  vr.checkCancellation = False;
  vr.cc_threshold_binary32 = 18;
  vr.cc_threshold_binary64 = 40;

  vr.dumpCancellation = False;
  vr.cancellationSource = NULL;

  vr.checkDenorm = False;
  vr.ftz = False;
  vr.dumpDenorm = False;
  vr.cancellationSource = NULL;

  vr.checkFloatMax = False;
}

Bool vr_process_clo(const HChar *arg) {
  Bool bool_val;
  const HChar *str;
  UInt setResult;

  // Option --backend=
  if (VG_XACT_CLOM(cloPD, arg, "--backend=verrou", vr.backend, vr_verrou)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--backend=mcaquad", vr.backend,
                          vr_mcaquad)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--backend=checkdenorm", vr.backend,
                          vr_checkdenormal)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--backend=vprec", vr.backend,
                          vr_vprec)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--backend=bitmask", vr.backend,
                          vr_bitmask)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--backend=mcaint", vr.backend,
                          vr_mcaint)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--backend=cancellation", vr.backend,
                          vr_cancellation)) {
  }

  // Option --rounding-mode=
  else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=random", vr.roundingMode,
                        VR_RANDOM)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=random_det",
                          vr.roundingMode, VR_RANDOM_DET)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=random_comdet",
                          vr.roundingMode, VR_RANDOM_COMDET)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=average",
                          vr.roundingMode, VR_AVERAGE)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=average_det",
                          vr.roundingMode, VR_AVERAGE_DET)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=average_comdet",
                          vr.roundingMode, VR_AVERAGE_COMDET)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=prandom",
                          vr.roundingMode, VR_PRANDOM)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=prandom_det",
                          vr.roundingMode, VR_PRANDOM_DET)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=prandom_comdet",
                          vr.roundingMode, VR_PRANDOM_COMDET)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=nearest",
                          vr.roundingMode, VR_NEAREST)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=upward", vr.roundingMode,
                          VR_UPWARD)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=downward",
                          vr.roundingMode, VR_DOWNWARD)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=toward_zero",
                          vr.roundingMode, VR_ZERO)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=farthest",
                          vr.roundingMode, VR_FARTHEST)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=float", vr.roundingMode,
                          VR_FLOAT)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=native", vr.roundingMode,
                          VR_NATIVE)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--rounding-mode=ftz", vr.roundingMode,
                          VR_FTZ)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--prandom-update=func", vr.prandomUpdate,
                          VR_PRANDOM_UPDATE_FUNC)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--prandom-update=none", vr.prandomUpdate,
                          VR_PRANDOM_UPDATE_NONE)) {
  } else if (VG_STR_CLOM(cloPD, arg, "--prandom-pvalue", str)) {
    vr.prandomFixedInitialValue = VG_(strtod)(str, NULL);
    if (vr.prandomFixedInitialValue < 0 || vr.prandomFixedInitialValue > 1) {
      VG_(tool_panic)("\tpvalue has to be between 0 and 1\n");
    }
  }

#ifdef LINK_INTERFLOP_BACKEND_BITMASK
  // Option bitmask
  else if (VG_INT_CLOM(cloPD, arg, "--bitmask-binary64-precision",
                       vr.bitmask_binary64_precision)) {
  } else if (VG_INT_CLOM(cloPD, arg, "--bitmask-binary32-precision",
                         vr.bitmask_binary32_precision)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--bitmask-mode=ob", vr.bitmask_mode,
                          bitmask_mode_ob)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--bitmask-mode=ib", vr.bitmask_mode,
                          bitmask_mode_ib)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--bitmask-mode=full", vr.bitmask_mode,
                          bitmask_mode_full)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--bitmask-mode=ieee", vr.bitmask_mode,
                          bitmask_mode_ieee)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--bitmask-operator=zero",
                          vr.bitmask_operator, bitmask_operator_zero)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--bitmask-operator=one",
                          vr.bitmask_operator, bitmask_operator_one)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--bitmask-operator=rand",
                          vr.bitmask_operator, bitmask_operator_rand)) {
  } else if (VG_BOOL_CLO(arg, "--bitmask-daz", bool_val)) {
    vr.bitmask_daz = bool_val;
  } else if (VG_BOOL_CLO(arg, "--bitmask-ftz", bool_val)) {
    vr.bitmask_ftz = bool_val;
  }
#endif

#ifdef LINK_INTERFLOP_BACKEND_CANCELLATION
  // Option cancellation
  else if (VG_INT_CLOM(cloPD, arg, "--cancellation-tolerance",
                       vr.cancellation_tolerance)) {
  } else if (VG_BOOL_CLO(arg, "--cancellation-warning", bool_val)) {
    vr.cancellation_warning = bool_val;
  }
#endif

#ifdef LINK_INTERFLOP_BACKEND_MCAINT
  // Option bitmaskquad
  else if (VG_INT_CLOM(cloPD, arg, "--mca-binary64-precision",
                       vr.mcaint_binary64_precision)) {
  } else if (VG_INT_CLOM(cloPD, arg, "--mca-binary32-precision",
                         vr.mcaint_binary32_precision)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mca-mode=rr", vr.mcaint_mode,
                          mcaint_mode_rr)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mca-mode=pb", vr.mcaint_mode,
                          mcaint_mode_pb)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mca-mode=mca", vr.mcaint_mode,
                          mcaint_mode_mca)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mca-mode=ieee", vr.mcaint_mode,
                          mcaint_mode_ieee)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mcaint-error-mode=rel",
                          vr.mcaint_err_mode, mcaint_err_mode_rel)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mcaint-error-mode=abs",
                          vr.mcaint_err_mode, mcaint_err_mode_abs)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mcaint-error-mode=all",
                          vr.mcaint_err_mode, mcaint_err_mode_all)) {
  } else if (VG_INT_CLOM(cloPD, arg, "--mcaint-max-abs-error-exponent",
                         vr.mcaint_max_abs_err_exponent)) {
  } else if (VG_DBL_CLOM(cloPD, arg, "--sparsity", vr.mcaint_sparsity)) {
  } else if (VG_BOOL_CLO(arg, "--mcaint-daz", bool_val)) {
    vr.mcaint_daz = bool_val;
  } else if (VG_BOOL_CLO(arg, "--mcaint-ftz", bool_val)) {
    vr.mcaint_ftz = bool_val;
  }
#endif

#ifdef LINK_INTERFLOP_BACKEND_MCAQUAD
  // Option bitmaskquad
  else if (VG_INT_CLOM(cloPD, arg, "--mca-binary64-precision",
                       vr.mcaquad_binary64_precision)) {
  } else if (VG_INT_CLOM(cloPD, arg, "--mca-binary32-precision",
                         vr.mcaquad_binary32_precision)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mca-mode=rr", vr.mcaquad_mode,
                          mcaquad_mode_rr)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mca-mode=pb", vr.mcaquad_mode,
                          mcaquad_mode_pb)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mca-mode=mca", vr.mcaquad_mode,
                          mcaquad_mode_mca)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mca-mode=ieee", vr.mcaquad_mode,
                          mcaquad_mode_ieee)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mcaquad-error-mode=rel",
                          vr.mcaquad_err_mode, mcaquad_err_mode_rel)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mcaquad-error-mode=abs",
                          vr.mcaquad_err_mode, mcaquad_err_mode_abs)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--mcaquad-error-mode=all",
                          vr.mcaquad_err_mode, mcaquad_err_mode_all)) {
  } else if (VG_INT_CLOM(cloPD, arg, "--mcaquad-max-abs-error-exponent",
                         vr.mcaquad_max_abs_err_exponent)) {
  } else if (VG_DBL_CLOM(cloPD, arg, "--sparsity", vr.mcaquad_sparsity)) {
  } else if (VG_BOOL_CLO(arg, "--mcaquad-daz", bool_val)) {
    vr.mcaquad_daz = bool_val;
  } else if (VG_BOOL_CLO(arg, "--mcaquad-ftz", bool_val)) {
    vr.mcaquad_ftz = bool_val;
  }
#endif

  // Option checkdenorm
  else if (VG_BOOL_CLO(arg, "--check-denorm", bool_val)) {
    vr.checkDenorm = bool_val;
  }

#ifdef LINK_INTERFLOP_BACKEND_VPREC
  // Options VPREC
  else if (VG_INT_CLOM(cloPD, arg, "--vprec-precision-binary64",
                       vr.vprec_precision_binary64)) {
  } else if (VG_INT_CLOM(cloPD, arg, "--vprec-precision-binary32",
                         vr.vprec_precision_binary32)) {
  } else if (VG_INT_CLOM(cloPD, arg, "--vprec-range-binary64",
                         vr.vprec_range_binary64)) {
  } else if (VG_INT_CLOM(cloPD, arg, "--vprec-range-binary32",
                         vr.vprec_range_binary32)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-mode=ob", vr.vprec_mode,
                          vprecmode_ob)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-mode=ib", vr.vprec_mode,
                          vprecmode_ib)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-mode=full", vr.vprec_mode,
                          vprecmode_full)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-mode=ieee", vr.vprec_mode,
                          vprecmode_ieee)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-preset=binary16",
                          vr.vprec_preset, vprec_preset_binary16)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-preset=binary32",
                          vr.vprec_preset, vprec_preset_binary32)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-preset=bfloat16",
                          vr.vprec_preset, vprec_preset_bfloat16)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-preset=tensorfloat",
                          vr.vprec_preset, vprec_preset_tensorfloat)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-preset=fp24", vr.vprec_preset,
                          vprec_preset_fp24)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-preset=PXR24", vr.vprec_preset,
                          vprec_preset_PXR24)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-error-mode=rel",
                          vr.vprec_error_mode, vprec_err_mode_rel)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-error-mode=abs",
                          vr.vprec_error_mode, vprec_err_mode_abs)) {
  } else if (VG_XACT_CLOM(cloPD, arg, "--vprec-error-mode=all",
                          vr.vprec_error_mode, vprec_err_mode_all)) {
  } else if (VG_INT_CLOM(cloPD, arg, "--vprec-max-abs-error-exponent",
                         vr.vprec_max_abs_error_exponent)) {
  } else if (VG_BOOL_CLO(arg, "--vprec-daz", bool_val)) {
    vr.vprec_daz = bool_val;
  } else if (VG_BOOL_CLO(arg, "--vprec-ftz", bool_val)) {
    vr.vprec_ftz = bool_val;
  }
#endif
  // Options to choose op to instrument
  else if (VG_USET_CLOM(cloPD, arg, "--vr-instr",
                        "add,sub,mul,div,mAdd,mSub,conv", setResult)) {
    UInt instrTab[] = {0, 0, 0, 0, 0, 0, 0};
    UInt currentFlags = setResult;
    for (UInt i = 0; i < 7; i++) {
      instrTab[i] = currentFlags % 2;
      currentFlags = currentFlags / 2;
    }
    if (instrTab[0] != 0)
      vr.instr_op[VR_OP_ADD] = True;
    if (instrTab[1] != 0)
      vr.instr_op[VR_OP_SUB] = True;
    if (instrTab[2] != 0)
      vr.instr_op[VR_OP_MUL] = True;
    if (instrTab[3] != 0)
      vr.instr_op[VR_OP_DIV] = True;
    if (instrTab[4] != 0)
      vr.instr_op[VR_OP_MADD] = True;
    if (instrTab[5] != 0)
      vr.instr_op[VR_OP_MSUB] = True;
    if (instrTab[6] != 0)
      vr.instr_op[VR_OP_CONV] = True;
  }

  // Option to enable check-cancellation backend
  else if (VG_BOOL_CLO(arg, "--check-cancellation", bool_val)) {
    vr.checkCancellation = bool_val;
  } else if (VG_INT_CLO(arg, "--cc-threshold-binary64",
                        vr.cc_threshold_binary64)) {
  } else if (VG_INT_CLO(arg, "--cc-threshold-binary32",
                        vr.cc_threshold_binary32)) {
  }

  else if (VG_BOOL_CLO(arg, "--check-nan", bool_val)) {
    vr.checknan = bool_val;
  } else if (VG_BOOL_CLO(arg, "--check-inf", bool_val)) {
    vr.checkinf = bool_val;
  }

  else if (VG_BOOL_CLO(arg, "--check-max-float", bool_val)) {
    vr.checkFloatMax = bool_val;
  }

  // Options to choose op to instrument
  else if (VG_BOOL_CLO(arg, "--vr-instr-scalar", bool_val)) {
    vr.instr_vec[VR_VEC_SCAL] = bool_val;
  }

  else if (VG_BOOL_CLO(arg, "--vr-instr-llo", bool_val)) {
    vr.instr_vec[VR_VEC_LLO] = bool_val;
  }

  else if (VG_BOOL_CLO(arg, "--vr-instr-vec2", bool_val)) {
    vr.instr_vec[VR_VEC_FULL2] = bool_val;
  }

  else if (VG_BOOL_CLO(arg, "--vr-instr-vec4", bool_val)) {
    vr.instr_vec[VR_VEC_FULL4] = bool_val;
  }

  else if (VG_BOOL_CLO(arg, "--vr-instr-vec8", bool_val)) {
    vr.instr_vec[VR_VEC_FULL8] = bool_val;
  }

  else if (VG_BOOL_CLO(arg, "--vr-instr-flt", bool_val)) {
    vr.instr_prec[VR_PREC_FLT] = bool_val;
  }

  else if (VG_BOOL_CLO(arg, "--vr-instr-dbl", bool_val)) {
    vr.instr_prec[VR_PREC_DBL] = bool_val;
  }

  // Option --vr-verbose (to avoid verbose of valgrind)
  else if (VG_BOOL_CLO(arg, "--vr-verbose", bool_val)) {
    vr.verbose = bool_val;
  }

  // Option --vr-unsafe-llo-optim (performance optimization)
  else if (VG_BOOL_CLO(arg, "--vr-unsafe-llo-optim", bool_val)) {
    vr.unsafe_llo_optim = bool_val;
  }

  // Option --count-op
  else if (VG_BOOL_CLO(arg, "--count-op", bool_val)) {
    vr.count = bool_val;
  }

  // Instrumentation at start
  else if (VG_BOOL_CLOM(cloPD, arg, "--instr-atstart", bool_val)) {
    vr.instrument = bool_val ? VR_INSTR_ON : VR_INSTR_OFF;
  }

  // Enable static-backend loading for verrou backend
  else if (VG_BOOL_CLOM(cloPD, arg, "--vr-static-backend", bool_val)) {
    vr.staticBackend = bool_val ? True : False;
  }

  // Exclusion of specified symbols
  else if (VG_STR_CLOM(cloPD, arg, "--gen-exclude", str)) {
    // vr.excludeFile = VG_(strdup)("vr.process_clo.gen-exclude", str);
    vr.excludeFile = VG_(expand_file_name)("vr.process_clo.gen-exclude", str);
    vr.genExcludeBool = True;
  }
  /* else if (VG_STR_CLOM (cloPD, arg, "--gen-above", str)) { */
  /*   vr.genAbove = VG_(strdup)("vr.process_clo.gen-above", str); */
  /* } */
  else if (VG_STR_CLOM(cloPD, arg, "--exclude", str)) {
    vr.exclude = vr_loadExcludeList(vr.exclude, str);
  }

  else if (VG_STR_CLOM(cloPD, arg, "--trace", str)) {
    vr.includeTrace = vr_loadIncludeTraceList(vr.includeTrace, str);
    vr.genTrace = True;
  }

  else if (VG_STR_CLOM(cloPD, arg, "--output-trace-rep", str)) {
    // vr.includeSourceFile = VG_(strdup)("vr.process_clo.gen-source", str);
    vr.outputTraceRep = VG_(expand_file_name)("vr.process_clo.trace-rep", str);
  }
  // Instrumentation of only specified source lines
  else if (VG_STR_CLOM(cloPD, arg, "--gen-source", str)) {
    // vr.includeSourceFile = VG_(strdup)("vr.process_clo.gen-source", str);
    vr.includeSourceFile =
        VG_(expand_file_name)("vr.process_clo.gen-source", str);
    vr.genIncludeSource = True;
  } else if (VG_STR_CLOM(cloPD, arg, "--source", str)) {
    vr.includeSource = vr_loadIncludeSourceList(vr.includeSource, str);
    vr.sourceActivated = True;
  }

  else if (VG_STR_CLOM(cloPD, arg, "--warn-unknown-source", str)) {
    vr.excludeSourceRead = vr_loadIncludeSourceList(vr.excludeSourceRead, str);
    vr.sourceExcludeActivated = True;
  }

  else if (VG_STR_CLOM(cloPD, arg, "--cc-gen-file", str)) {
    vr.cancellationDumpFile =
        VG_(expand_file_name)("vr.process_clo.cc-file", str);
    vr.dumpCancellation = True;
  }

  else if (VG_STR_CLOM(cloPD, arg, "--cd-gen-file", str)) {
    vr.denormDumpFile = VG_(expand_file_name)("vr.process_clo.cd-file", str);
    vr.dumpDenorm = True;
  }

  // Set the pseudo-Random Number Generator
  else if (VG_STR_CLOM(cloPD, arg, "--vr-seed", str)) {
    // Returns 0 if no number could be converted, and 'endptr'
    // is set to the start of the string.  None of them test that the number
    // fits into 64 bits.
    HChar *endptr = NULL;
    Long seed = VG_(strtoull10)(str, &endptr);
    if (seed == 0 && endptr == str) {
      HChar buf[64];
      VG_(sprintf)(buf, "invalid seed prodived: --vr-seed=%s\n", str);
      VG_(tool_panic)(buf);
    }
    vr.firstSeed = seed;
    vr.chooseSeed = True;
  }

  // Unknown option
  else {
    return False;
  }

  return True;
}

void vr_print_usage(void) {
  VG_(printf)
  (
#include "vr_clo.txt"
  );
}

void vr_print_debug_usage(void) { vr_print_usage(); }
