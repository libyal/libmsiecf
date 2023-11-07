include_HEADERS = \
	libmsiecf.h

pkginclude_HEADERS = \
	libmsiecf/codepage.h \
	libmsiecf/definitions.h \
	libmsiecf/error.h \
	libmsiecf/extern.h \
	libmsiecf/features.h \
	libmsiecf/types.h

EXTRA_DIST = \
	libmsiecf.h.in \
	libmsiecf/definitions.h.in \
	libmsiecf/features.h.in \
	libmsiecf/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libmsiecf.h
	-rm -f libmsiecf/definitions.h
	-rm -f libmsiecf/features.h
	-rm -f libmsiecf/types.h
	-rm -f Makefile

