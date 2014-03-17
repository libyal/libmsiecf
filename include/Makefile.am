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
	/bin/rm -f libmsiecf.h
	/bin/rm -f libmsiecf/definitions.h
	/bin/rm -f libmsiecf/features.h
	/bin/rm -f libmsiecf/types.h
	/bin/rm -f Makefile

