dnl Function to detect if libmsiecf dependencies are available
AC_DEFUN([AX_LIBMSIECF_CHECK_LOCAL],
 [dnl Check for internationalization functions in libmsiecf/libmsiecf_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

