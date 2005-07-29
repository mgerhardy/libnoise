#
# usage: AC_CHECK_NATIVE_STL
# result: $native_stl == yes if the compiler provides native support
#         for stl, $native_stl == no otherwise
#
AC_DEFUN(AC_CHECK_NATIVE_STL,
[
AC_MSG_CHECKING([for native STL support])
if test "$GCC" = "yes"
then
	version=`$CXX --version | head -1`
	version_number=`echo "$version" | perl -pe 's/.*?\) (\d)\.(\d).*/\1\2/'`
	if test "$version_number" -ge 32
	then
		native_stl=yes
		AC_MSG_RESULT(yes [$version])
	fi
fi
if test "$native_stl" != "yes"
then
	AC_MSG_RESULT(no)
fi
])
