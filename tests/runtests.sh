#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libmsiecf/.libs/libmsiecf.1.dylib && test -f ./pymsiecf/.libs/pymsiecf.so
then
	install_name_tool -change /usr/local/lib/libmsiecf.1.dylib ${PWD}/libmsiecf/.libs/libmsiecf.1.dylib ./pymsiecf/.libs/pymsiecf.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

