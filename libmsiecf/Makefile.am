AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFOLE_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBMSIECF_DLL_EXPORT@

lib_LTLIBRARIES = libmsiecf.la

libmsiecf_la_SOURCES = \
	libmsiecf.c \
	libmsiecf_allocation_table.c libmsiecf_allocation_table.h \
	libmsiecf_codepage.h \
	libmsiecf_debug.c libmsiecf_debug.h \
	libmsiecf_definitions.h \
	libmsiecf_directory_descriptor.c libmsiecf_directory_descriptor.h \
	libmsiecf_error.c libmsiecf_error.h \
	libmsiecf_extern.h \
	libmsiecf_file.c libmsiecf_file.h \
	libmsiecf_hash.c libmsiecf_hash.h \
	libmsiecf_hash_table.c libmsiecf_hash_table.h \
	libmsiecf_io_handle.c libmsiecf_io_handle.h \
	libmsiecf_item.c libmsiecf_item.h \
	libmsiecf_item_descriptor.c libmsiecf_item_descriptor.h \
	libmsiecf_leak.c libmsiecf_leak.h \
	libmsiecf_leak_values.c libmsiecf_leak_values.h \
	libmsiecf_libbfio.h \
	libmsiecf_libcdata.h \
	libmsiecf_libcerror.h \
	libmsiecf_libclocale.h \
	libmsiecf_libcnotify.h \
	libmsiecf_libfdatetime.h \
	libmsiecf_libfole.h \
	libmsiecf_libfvalue.h \
	libmsiecf_libuna.h \
	libmsiecf_notify.c libmsiecf_notify.h \
	libmsiecf_property_type.c libmsiecf_property_type.h \
	libmsiecf_redirected.c libmsiecf_redirected.h \
	libmsiecf_redirected_values.c libmsiecf_redirected_values.h \
	libmsiecf_support.c libmsiecf_support.h \
	libmsiecf_types.h \
	libmsiecf_unused.h \
	libmsiecf_url.c libmsiecf_url.h \
	libmsiecf_url_values.c libmsiecf_url_values.h \
	msiecf_file_header.h \
	msiecf_hash_record.h \
	msiecf_leak_record.h \
	msiecf_record.h \
	msiecf_redr_record.h \
	msiecf_url_record.h

libmsiecf_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFOLE_LIBADD@ \
	@LIBFVALUE_LIBADD@ \
	@PTHREAD_LIBADD@

libmsiecf_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libmsiecf_definitions.h.in \
	libmsiecf.rc \
	libmsiecf.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libmsiecf_definitions.h
	/bin/rm -f libmsiecf.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libmsiecf ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libmsiecf_la_SOURCES)

