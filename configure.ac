AC_INIT([hello], [1.0], [lbthomsen@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
PKG_CHECK_MODULES(modbus, libmodbus >= 3)
AC_OUTPUT
