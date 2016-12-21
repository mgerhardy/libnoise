# AC_EXG_BUILD_VERSION
#
# Setup version variables

AC_DEFUN(AC_EXG_BUILD_VERSION,
[
PACKAGE_VERSION_MAJOR=`echo $PACKAGE_VERSION|cut -d. -f1`
PACKAGE_VERSION_MINOR=`echo $PACKAGE_VERSION|cut -d. -f2`
PACKAGE_VERSION_MICRO=`echo $PACKAGE_VERSION|cut -d. -f3`
AC_SUBST(PACKAGE_VERSION_MAJOR)
AC_SUBST(PACKAGE_VERSION_MINOR)
AC_SUBST(PACKAGE_VERSION_MICRO)
])


# AC_EXG_BUILD_HOST
#
# Find out host family to select proper build subtrees (unix/darwin, carbon, win32)

AC_DEFUN(AC_EXG_BUILD_HOST,
[
CFLAGS=""

if test "$target_vendor" = "apple" ; then
  AC_ARG_WITH(mac-target,
      [  --with-mac-target=TARGET  either `carbon' (default) or `darwin'],
      mac_target="$withval",
      mac_target="carbon")
  case "$mac_target" in
    carbon)
      BUILD_HOST="carbon"
      EXG_CFLAGS="$EXG_CFLAGS -D_CARBON_"
      AC_MSG_ERROR([

  ** Sorry, the Carbon build is not yet supported via autoconf/automake.
  ** You can use --with-mac-target=darwin to build for Darwin/X11.
                   ])
      ;;
    darwin)
      BUILD_HOST="unix"
      EXG_CFLAGS="$EXG_CFLAGS -D_DARWIN_"
      ;;
    *)
      AC_MSG_ERROR([unknown Mac target (use `carbon' or `darwin'])
      ;;
  esac

  AC_MSG_CHECKING(for Fink)
  AC_ARG_WITH(fink,
      [  --with-fink=PATH    if PATH is omitted, /sw is used],
      fink_prefix="$withval",
      fink_prefix="none")
  if test $fink_prefix != none; then
    if test $fink_prefix = yes; then
      fink_prefix=/sw
    fi
    CPPFLAGS="$CPPFLAGS -I${fink_prefix}/include"
    LIBS="$LIBS -L${fink_prefix}/lib"
    AC_MSG_RESULT([yes, prefix is $fink_prefix])
  else
    AC_MSG_RESULT(no)
    AC_MSG_NOTICE([

  ** We recommend you install Fink (http://fink.sf.net) for the 3rd party
  ** libraries. Then you can invoke configure with --with-fink.
                  ])
  fi
else
  BUILD_HOST="unix"
fi

AC_SUBST(BUILD_HOST)
AM_CONDITIONAL(BUILD_HOST_UNIX, test "$BUILD_HOST" = "unix")
AM_CONDITIONAL(BUILD_HOST_LINUX, test "$target_os" = "linux-gnu")
AM_CONDITIONAL(BUILD_HOST_CARBON, test "$BUILD_HOST" = "carbon")
AM_CONDITIONAL(BUILD_HOST_WIN32, test "$BUILD_HOST" = "win32")

dnl FIXME: the x86 part is currently coded with MSVC inline assembly
#AM_CONDITIONAL(BUILD_HOST_X86, test `uname -m|egrep -c '^i.86$'` = 1)
AM_CONDITIONAL(BUILD_HOST_X86, false)
])


# AC_EXG_BUILD_DEBUG
#
# Set compiler flags and debug macros accordingly (gcc 3.x tuned)

AC_DEFUN(AC_EXG_BUILD_DEBUG,
[
AC_ARG_ENABLE(debug,
    [  --enable-debug          build in debug mode (no optimization, more verbose)],
    , enable_debug=yes)
OPTION="-pipe"
if test "$enable_debug" = "yes" ; then
  WARNING="-Wall -Wpointer-arith -Wstrict-prototypes"
  DEBUG="-g"
  OPTIMIZE=""
  DEFINE="-D_DEBUG_"
else
  WARNING="-Wall -Wpointer-arith -Wstrict-prototypes" # -Werror
  DEBUG="-g -O2"
#"-felide-constructors" is valid for C++ but not for C/ObjC
  OPTIMIZE="-march=$host_cpu -O2 -fPIC -fomit-frame-pointer -ffast-math"
  DEFINE=""
fi
CPPFLAGS="$CPPFLAGS $WARNING $OPTIMIZE $OPTION $DEFINE"
CXXFLAGS="$DEBUG"
])
