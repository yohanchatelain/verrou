#pragma once

#ifndef INTERFLOP_STATIC_INTERFACE_ENABLED
#error "INTERFLOP_STATIC_INTERFACE_ENABLED should be defined"
#endif
//#include "interflop_verrou/interflop_verrou.h"
#ifdef USE_VERROU_QUAD
//#include "backend_mcaquad/interflop_mcaquad.h"
#endif

#include "/home/yohan/Work/interflop-stdlib/interflop_stdlib.h"
#include "/home/yohan/Work/interflop-verrou-backend/interflop_verrou.h"
#include "/home/yohan/Work/interflop-vprec/common/vfc_hashmap.h"
#include "/home/yohan/Work/interflop-vprec/interflop_vprec.h"
#include "backend_check_float_max/interflop_check_float_max.h"
#include "backend_checkcancellation/interflop_checkcancellation.h"
#include "backend_checkdenorm/interflop_checkdenorm.h"
//#include "backend_vprec/interflop_vprec.h"