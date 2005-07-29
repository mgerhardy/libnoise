# =========================================================================
# AM_PATH_STLPORT : STLPort checking macros

AC_DEFUN(AM_PATH_STLPORT,
[ AC_REQUIRE_CPP()

AC_ARG_WITH( stlport,
    [  --with-stlport=<path>   path to the STLPort install files directory.
                          e.g. /usr/local/stlport])

AC_ARG_WITH( stlport-include,
    [  --with-stlport-include=<path>
                          path to the STLPort header files directory.
                          e.g. /usr/local/stlport/stlport])

AC_ARG_WITH( stlport-lib,
    [  --with-stlport-lib=<path>
                          path to the STLPort library files directory.
                          e.g. /usr/local/stlport/lib])

if test "$with_debug" = "full"
then
 stlport_lib="stlport_debug"
else
 stlport_lib="stlport"
fi

if test "$with_stlport" = no
then
    dnl The user explicitly disabled the use of the STLPorts
    AC_MSG_ERROR([STLPort is mandatory: do not specify --without-stlport])
else
    stlport_includes="/usr/include/stlport"
    if test "$with_stlport" -a "$with_stlport" != yes
    then
        stlport_includes="$with_stlport/stlport"
        stlport_libraries="$with_stlport/lib"

        if test ! -d "$stlport_includes"
        then
            stlport_includes="$with_stlport/include/stlport"
        fi
    fi
fi

if test "$with_stlport_include"
then
    stlport_includes="$with_stlport_include"
fi

if test "$with_stlport_lib"
then
    stlport_libraries="$with_stlport_lib"
fi

dnl Check for the 'pthread' library. SLTPort needs it.
AC_CHECK_LIB(pthread, main, , [AC_MSG_ERROR([cannot find the pthread library.])])

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

dnl Put STLPorts includes in CXXFLAGS
if test "$stlport_includes"
then
    CXXFLAGS="$CXXFLAGS -I$stlport_includes"
fi

dnl Put STLPorts libraries directory in LIBS
if test "$stlport_libraries"
then
    LIBS="-L$stlport_libraries $LIBS"
else
    stlport_libraries='default'
fi

dnl Test the headers

AC_CHECK_HEADER(algorithm,
    have_stlport_headers="yes",
    have_stlport_headers="no" )

AC_MSG_CHECKING(for STLPort headers)

if test "$have_stlport_headers" = "yes"
then
    AC_MSG_RESULT([$stlport_includes])
else
    AC_MSG_RESULT(no)
fi

AC_CHECK_LIB($stlport_lib, main,, have_stlport_libraries="no")

AC_MSG_CHECKING(for STLPort library)

if test "$have_stlport_libraries" != "no"
then
    AC_MSG_RESULT([$stlport_libraries])
else
    AC_MSG_RESULT(no)
fi

if test "$have_stlport_headers" = "yes" &&
    test "$have_stlport_libraries" != "no"
then
    have_stlport="yes"
else
    have_stlport="no"
fi

if test "$have_stlport" = "no"
then
    AC_MSG_ERROR([STLPort must be installed (http://www.stlport.org).])
fi

AC_LANG_RESTORE

])
