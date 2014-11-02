AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBMSIECF_DLL_IMPORT@

if HAVE_PYTHON
TESTS_PYMSIECF  = \
	test_pymsiecf_set_ascii_codepage.sh \
	test_pymsiecf_open_close.sh
endif

TESTS = \
	test_set_ascii_codepage.sh \
	test_open_close.sh \
	test_msiecfinfo.sh \
	test_msiecfexport.sh \
	$(TESTS_PYMSIECF)

check_SCRIPTS = \
	pymsiecf_test_open_close.py \
	pymsiecf_test_set_ascii_codepage.py \
	test_msiecfexport.sh \
	test_msiecfinfo.sh \
	test_open_close.sh \
	test_pymsiecf_open_close.sh \
	test_pymsiecf_set_ascii_codepage.sh \
	test_runner.sh \
	test_set_ascii_codepage.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS =  \
	msiecf_test_open_close \
	msiecf_test_set_ascii_codepage

msiecf_test_open_close_SOURCES = \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_libcstring.h \
	msiecf_test_open_close.c

msiecf_test_open_close_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

msiecf_test_set_ascii_codepage_SOURCES = \
	msiecf_test_libcerror.h \
	msiecf_test_libclocale.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_libcstring.h \
	msiecf_test_set_ascii_codepage.c

msiecf_test_set_ascii_codepage_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

