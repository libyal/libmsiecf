#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libmsiecf/.libs/libmsiecf.1.dylib && test -f ./pymsiecf/.libs/pymsiecf.so;
then
	install_name_tool -change /usr/local/lib/libmsiecf.1.dylib ${PWD}/libmsiecf/.libs/libmsiecf.1.dylib ./pymsiecf/.libs/pymsiecf.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

