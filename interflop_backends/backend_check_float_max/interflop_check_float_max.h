
/*--------------------------------------------------------------------*/
/*--- Verrou: a FPU instrumentation tool.                          ---*/
/*--- Interface for floatin-point operations overloading           ---*/
/*--- designed to detect operation with FLT_MAX and DBL_MAX        ---*/
/*---                               interflop_check_float_max_.h   ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of Verrou, a FPU instrumentation tool.

   Copyright (C) 2014-2021 EDF
     B. Lathuilière <bruno.lathuiliere@edf.fr>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU Lesser General Public License is contained in the file COPYING.
*/

#ifndef __INTERFLOP_CHECK_FLOAT_MAX_H
#define __INTERFLOP_CHECK_FLOAT_MAX_H


#ifdef __cplusplus
extern "C" {
#endif
#define IFMAX_FCTNAME(FCT) interflop_check_float_max_##FCT

#include "../interflop.h"



  //  void IFMAX_FCTNAME(configure)(checkcancellation_conf_t mode,void* context);
  void IFMAX_FCTNAME(finalize)(void* context);

  const char* IFMAX_FCTNAME(get_backend_name)(void);
  const char* IFMAX_FCTNAME(get_backend_version)(void);

  void ifmax_set_max_handler(void (*)(void));
  void ifmax_set_debug_print_op(void (*printOpHandler)(int nbArg,const char*name, const double* args,const double* res));

  struct interflop_backend_interface_t IFMAX_FCTNAME(init)(void ** context);
   
  void IFMAX_FCTNAME(add_double) (double a, double b, double* res, void* context);    
  void IFMAX_FCTNAME(add_float)  (float a,  float b,  float*  res, void* context);
  void IFMAX_FCTNAME(sub_double) (double a, double b, double* res, void* context);
  void IFMAX_FCTNAME(sub_float)  (float a,  float b,  float*  res, void* context);
  void IFMAX_FCTNAME(mul_double) (double a, double b, double* res, void* context);
  void IFMAX_FCTNAME(mul_float)  (float a,  float b,  float*  res, void* context);
  void IFMAX_FCTNAME(div_double) (double a, double b, double* res, void* context);
  void IFMAX_FCTNAME(div_float)  (float a,  float b,  float*  res, void* context);

  void IFMAX_FCTNAME(cast_double_to_float) (double a, float* b, void* context);

  void IFMAX_FCTNAME(madd_double)(double a, double b, double c, double* res, void* context);
  void IFMAX_FCTNAME(madd_float) (float a,  float b,  float c,  float*  res, void* context);

  
#ifdef __cplusplus
}
#endif

#endif /* ndef __INTERFLOP_CHECK_FLOAT_MAX_H */
