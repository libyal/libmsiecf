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
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBMSIECF_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYMSIECF = \
	test_python_functions.sh \
	test_pymsiecf_set_ascii_codepage.sh
endif

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_msiecfinfo.sh \
	test_msiecfexport.sh \
	$(TESTS_PYMSIECF)

check_SCRIPTS = \
	pymsiecf_test_get_version.py \
	pymsiecf_test_open_close.py \
	pymsiecf_test_set_ascii_codepage.py \
	test_api_functions.sh \
	test_api_types.sh \
	test_msiecfexport.sh \
	test_msiecfinfo.sh \
	test_pymsiecf_set_ascii_codepage.sh \
	test_python_functions.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	msiecf_test_error \
	msiecf_test_file \
	msiecf_test_item \
	msiecf_test_open_close \
	msiecf_test_support

msiecf_test_error_SOURCES = \
	msiecf_test_error.c \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_unused.h

msiecf_test_error_LDADD = \
	../libmsiecf/libmsiecf.la

msiecf_test_file_SOURCES = \
	msiecf_test_file.c \
	msiecf_test_libcerror.h \
	msiecf_test_libclocale.h \
	msiecf_test_libcsystem.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_libuna.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_file_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_item_SOURCES = \
	msiecf_test_item.c \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_item_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_open_close_SOURCES = \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_libcsystem.h \
	msiecf_test_open_close.c

msiecf_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

msiecf_test_support_SOURCES = \
	msiecf_test_libcerror.h \
	msiecf_test_libclocale.h \
	msiecf_test_libcsystem.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_libuna.h \
	msiecf_test_macros.h \
	msiecf_test_support.c \
	msiecf_test_unused.h

msiecf_test_support_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

