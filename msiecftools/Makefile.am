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
	@LIBMSIECF_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	msiecfexport \
	msiecfinfo

msiecfexport_SOURCES = \
	export_handle.c export_handle.h \
	log_handle.c log_handle.h \
	msiecfexport.c \
	msiecftools_getopt.c msiecftools_getopt.h \
	msiecftools_i18n.h \
	msiecftools_libbfio.h \
	msiecftools_libcerror.h \
	msiecftools_libclocale.h \
	msiecftools_libcnotify.h \
	msiecftools_libfdatetime.h \
	msiecftools_libmsiecf.h \
	msiecftools_libuna.h \
	msiecftools_output.c msiecftools_output.h \
	msiecftools_signal.c msiecftools_signal.h \
	msiecftools_unused.h

msiecfexport_LDADD = \
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
	msiecftools_getopt.c msiecftools_getopt.h \
	msiecftools_i18n.h \
	msiecftools_libbfio.h \
	msiecftools_libcerror.h \
	msiecftools_libclocale.h \
	msiecftools_libcnotify.h \
	msiecftools_libfdatetime.h \
	msiecftools_libmsiecf.h \
	msiecftools_libuna.h \
	msiecftools_output.c msiecftools_output.h \
	msiecftools_signal.c msiecftools_signal.h \
	msiecftools_unused.h

msiecfinfo_LDADD = \
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

