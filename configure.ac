AM_PATH_PYTHON([3])

m4_include(verrou/ax_interflop_stdlib.m4)
m4_include(verrou/ax_interflop_rng.m4)
m4_include(verrou/ax_intrinsic_fma.m4)

AC_DEFUN([WITH_INTERFLOP_BACKEND],
[
  # WITH_INTERFLOP_BACKEND([backend],[BACKEND],[required])
  # Add --with-interflop-backend-[backend] option
  # Raise an error if $withval=no and required set to true
  AC_ARG_WITH([interflop-backend-$1],
    AS_HELP_STRING([--with-interflop-backend-$1@<:@=DIR@:>@],
      [use interflop-backend-$1 located in DIR]),
    [with_interflop_backend_$1="$withval"],
    [with_interflop_backend_$1=yes])

  AM_CONDITIONAL([LINK_INTERFLOP_BACKEND_$2], [test "x$with_interflop_backend_$1" != "xno"])
  if test "x$with_interflop_backend_$1" = "xno"; then
    if [ $3 = true ]; then
      AC_MSG_ERROR([--with-interflop-backend-$1=no was given. Need to link with interflop-backend-$1 backend.])
    else
      AC_MSG_NOTICE([--with-interflop-backend-$1=no was given. Do not link with interflop-backend-$1 backend.])
    fi
    with_interflop_backend_$1_path=
  elif test "x$with_interflop_backend_$1" = "xyes"; then
    with_interflop_backend_$1_path=$(interflop-config --prefix)
  else
    with_interflop_backend_$1_path="$with_interflop_backend_$1"
  fi
  AC_DEFINE_UNQUOTED(INTERFLOP_BACKEND_$2_PATH, "$with_interflop_backend_$1_path", [interflop-backend-$1 install path])
  AC_SUBST(INTERFLOP_BACKEND_$2_PATH, [$with_interflop_backend_$1_path])

  AC_DEFINE_UNQUOTED(INTERFLOP_BACKEND_$2_LIBDIR, "$with_interflop_backend_$1_path/lib", [interflop-backend-$1 lib path])
  AC_SUBST(INTERFLOP_BACKEND_$2_LIBDIR, [$with_interflop_backend_$1_path/lib])

  AC_DEFINE_UNQUOTED(INTERFLOP_BACKEND_$2_INCLUDEDIR, "$with_interflop_backend_$1_path/include", [interflop-backend-$1 include path])
  AC_SUBST(INTERFLOP_BACKEND_$2_INCLUDEDIR, [$with_interflop_backend_$1_path/include])


])

# --with-interflop-stdlib
AX_INTERFLOP_STDLIB()
AX_INTRINSIC_FMA()
AX_INTERFLOP_RNG()

# --with-interflop-backend-verrou
WITH_INTERFLOP_BACKEND(verrou, VERROU, true)

# --with-interflop-backend-checkfloatmax
WITH_INTERFLOP_BACKEND(checkfloatmax, CHECKFLOATMAX, true)

# --with-interflop-backend-checkcancellation
WITH_INTERFLOP_BACKEND(checkcancellation, CHECKCANCELLATION, true)

# --with-interflop-backend-checkdenormal
WITH_INTERFLOP_BACKEND(checkdenormal, CHECKDENORMAL, true)

# --with-interflop-backend-bitmask
WITH_INTERFLOP_BACKEND(bitmask, BITMASK, false)

# --with-interflop-backend-cancellation
WITH_INTERFLOP_BACKEND(cancellation, CANCELLATION, false)

# --with-interflop-backend-mcaint
WITH_INTERFLOP_BACKEND(mcaint, MCAINT, false)

# --with-interflop-backend-mcaquad
WITH_INTERFLOP_BACKEND(mcaquad, MCAQUAD, true)

# --with-interflop-backend-vprec
WITH_INTERFLOP_BACKEND(vprec, VPREC, false)

#--enable-profiling for exact operation
AC_CACHE_CHECK([verrou profiling exact], vg_cv_verrou_profiling_exact,
  [AC_ARG_ENABLE(verrou-profiling-exact,
    [  --enable-verrou-profiling-exact          enables profiling of exact operation],
    [vg_cv_verrou_profiling_exact=$enableval],
    [vg_cv_verrou_profiling_exact=no])])

AM_CONDITIONAL([USE_PROFILING_EXACT], test x$vg_cv_verrou_profiling_exact = xyes,[])
AC_SUBST(vg_cv_verrou_profiling_exact)

#--enable-verrou-checknaninf
AC_CACHE_CHECK([verrou check nan inf], vg_cv_verrou_naninf,
  [AC_ARG_ENABLE(verrou-check-naninf,
    [  --enable-verrou-check-naninf          enables verrou check for nan and inf],
    [vg_cv_verrou_naninf=$enableval],
    [vg_cv_verrou_naninf=yes])])

AM_CONDITIONAL([USE_VERROU_NANINF], test x$vg_cv_verrou_naninf = xyes,[])
AC_SUBST(vg_cv_verrou_naninf)

# avx512
vg_test_no_avx512f_flag=-mno-avx512f
AC_LANG_PUSH(C++)
CXXFLAGS="$safe_CXXFLAGS $vg_test_no_avx512f_flag"
AC_MSG_CHECKING([for -mno-avx512f compil option])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
      #include <stdlib.h>
      ]], [[return EXIT_SUCCESS;]])],
    [
      CXXFLAGS="$safe_CXXFLAGS"
      AC_MSG_RESULT([yes])
    ],[
    CXXFLAGS="$safe_CXXFLAGS"
     vg_test_no_avx512f_flag=
      AC_MSG_RESULT([no])
  ])
AC_LANG_POP(C++)
AC_SUBST(vg_test_no_avx512f_flag)

AC_CONFIG_FILES([verrou/env.sh])
AC_CONFIG_FILES([verrou/unitTest/flag.mk])
