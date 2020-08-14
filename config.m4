dnl config.m4 for extension brunsli

PHP_ARG_WITH([brunsli],
  [for brunsli support],
  [AS_HELP_STRING([[--with-brunsli[=DIR]]],
    [Include brunsli support])])

if test "$PHP_BRUNSLI" != "no"; then
  AC_PATH_PROG(PKG_CONFIG, pkg-config, no)

  AC_MSG_CHECKING(for brunslienc-c)
  if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists brunslienc-c; then
    BRUNSLIENC_CFLAGS=`$PKG_CONFIG brunslienc-c --cflags`
    BRUNSLIENC_LIBS=`$PKG_CONFIG brunslienc-c --libs`
    AC_MSG_RESULT([from pkgconfig: brunslienc-c found])
    PHP_EVAL_INCLINE($BRUNSLIENC_CFLAGS)
    PHP_EVAL_LIBLINE($BRUNSLIENC_LIBS, BRUNSLI_SHARED_LIBADD)
  else
    AC_MSG_RESULT([pkgconfig: not found])
    BRUNSLI_PKG_CONFIG=no
  fi

  AC_MSG_CHECKING(for brunslidec-c)
  if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists brunslidec-c; then
    BRUNSLIDEC_CFLAGS=`$PKG_CONFIG brunslidec-c --cflags`
    BRUNSLIDEC_LIBS=`$PKG_CONFIG brunslidec-c --libs`
    AC_MSG_RESULT([from pkgconfig: brunslidec-c found])
    PHP_EVAL_INCLINE($BRUNSLIDEC_CFLAGS)
    PHP_EVAL_LIBLINE($BRUNSLIDEC_LIBS, BRUNSLI_SHARED_LIBADD)
  else
    AC_MSG_RESULT([pkgconfig: not found])
    BRUNSLI_PKG_CONFIG=no
  fi

  if test "$BRUNSLI_PKG_CONFIG" = "no"; then
    SEARCH_PATH="/usr/local /usr"
    SEARCH_FOR="/include/brunsli/encode.h"
    if test -r $PHP_BRUNSLI/$SEARCH_FOR; then
      BRUNSLI_DIR=$PHP_BRUNSLI
    else
      AC_MSG_CHECKING([for brunsli files in default path])
      for i in $SEARCH_PATH ; do
        if test -r $i/$SEARCH_FOR; then
          BRUNSLI_DIR=$i
          AC_MSG_RESULT(found in $i)
        fi
      done
    fi

    if test -z "$BRUNSLI_DIR"; then
      AC_MSG_RESULT([not found])
      AC_MSG_ERROR([Please reinstall the brunsli distribution])
    fi

    PHP_ADD_INCLUDE($BRUNSLI_DIR/include)

    PHP_CHECK_LIBRARY(brunslienc-c, EncodeBrunsli,
    [
      PHP_ADD_LIBRARY_WITH_PATH(brunslienc-c, $BRUNSLI_DIR/$PHP_LIBDIR, BRUNSLI_SHARED_LIBADD)
      AC_DEFINE(HAVE_BRUNSLI_ENCODE, 1, [ ])
    ],[
      AC_MSG_ERROR([requires brunsli encode library.])
    ], [
      -L$BRUNSLI_DIR/$PHP_LIBDIR
    ])

    PHP_CHECK_LIBRARY(brunslidec-c, DecodeBrunsli,
    [
      PHP_ADD_LIBRARY_WITH_PATH(brunslidec-c, $BRUNSLI_DIR/$PHP_LIBDIR, BRUNSLI_SHARED_LIBADD)
      AC_DEFINE(HAVE_BRUNSLI_DECODE, 1, [ ])
    ],[
      AC_MSG_ERROR([requires brunsli decode library.])
    ], [
      -L$BRUNSLI_DIR/$PHP_LIBDIR
    ])
  fi

  PHP_SUBST(BRUNSLI_SHARED_LIBADD)

  AC_DEFINE(HAVE_BRUNSLI, 1, [ Have brunsli support ])

  PHP_NEW_EXTENSION(brunsli, brunsli.c, $ext_shared)
fi
