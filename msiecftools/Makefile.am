AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBMSIECF_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	msiecfexport \
	msiecfinfo

msiecfexport_SOURCES = \
	export_handle.c export_handle.h \
	log_handle.c log_handle.h \
	msiecfexport.c \
	msiecfoutput.c msiecfoutput.h \
	msiecftools_libbfio.h \
	msiecftools_libcerror.h \
	msiecftools_libclocale.h \
	msiecftools_libcnotify.h \
	msiecftools_libcsystem.h \
	msiecftools_libfdatetime.h \
	msiecftools_libmsiecf.h \
	msiecftools_libuna.h

msiecfexport_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

msiecfinfo_SOURCES = \
	info_handle.c info_handle.h \
	msiecfinfo.c \
	msiecfoutput.c msiecfoutput.h \
	msiecftools_libbfio.h \
	msiecftools_libcerror.h \
	msiecftools_libclocale.h \
	msiecftools_libcnotify.h \
	msiecftools_libcsystem.h \
	msiecftools_libfdatetime.h \
	msiecftools_libmsiecf.h \
	msiecftools_libuna.h

msiecfinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on msiecfexport ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(msiecfexport_SOURCES)
	@echo "Running splint on msiecfinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(msiecfinfo_SOURCES)

