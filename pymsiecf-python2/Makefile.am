# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBMSIECF_DLL_IMPORT@

am_pymsiecf_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
	pymsiecf.c pymsiecf.h \
	pymsiecf_cache_directories.c pymsiecf_cache_directories.h \
	pymsiecf_codepage.c pymsiecf_codepage.h \
	pymsiecf_datetime.c pymsiecf_datetime.h \
	pymsiecf_error.c pymsiecf_error.h \
	pymsiecf_file.c pymsiecf_file.h \
	pymsiecf_file_object_io_handle.c pymsiecf_file_object_io_handle.h \
	pymsiecf_integer.c pymsiecf_integer.h \
	pymsiecf_item.c pymsiecf_item.h \
	pymsiecf_item_flags.c pymsiecf_item_flags.h \
	pymsiecf_item_types.c pymsiecf_item_types.h \
	pymsiecf_items.c pymsiecf_items.h \
	pymsiecf_leak.c pymsiecf_leak.h \
	pymsiecf_libbfio.h \
	pymsiecf_libcerror.h \
	pymsiecf_libclocale.h \
	pymsiecf_libmsiecf.h \
	pymsiecf_python.h \
	pymsiecf_redirected.c pymsiecf_redirected.h \
	pymsiecf_unused.h \
	pymsiecf_url.c pymsiecf_url.h \
	pymsiecf_url_types.c pymsiecf_url_types.h

pyexec_LTLIBRARIES = pymsiecf.la

nodist_pymsiecf_la_SOURCES = $(BUILT_SOURCES)

pymsiecf_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pymsiecf_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pymsiecf_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pymsiecf/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pymsiecf*.[ch]

distclean: clean
	/bin/rm -f Makefile

