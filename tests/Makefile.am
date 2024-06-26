AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
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
	@LIBMSIECF_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYMSIECF = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_msiecfinfo.sh \
	test_msiecfexport.sh \
	$(TESTS_PYMSIECF)

check_SCRIPTS = \
	pymsiecf_test_file.py \
	pymsiecf_test_support.py \
	test_library.sh \
	test_msiecfexport.sh \
	test_msiecfinfo.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	msiecf_test_allocation_table \
	msiecf_test_cache_directory_table \
	msiecf_test_directory_descriptor \
	msiecf_test_error \
	msiecf_test_file \
	msiecf_test_file_header \
	msiecf_test_hash_table \
	msiecf_test_io_handle \
	msiecf_test_item \
	msiecf_test_item_descriptor \
	msiecf_test_leak \
	msiecf_test_leak_values \
	msiecf_test_notify \
	msiecf_test_property_type \
	msiecf_test_redirected \
	msiecf_test_redirected_values \
	msiecf_test_support \
	msiecf_test_tools_info_handle \
	msiecf_test_tools_output \
	msiecf_test_tools_signal \
	msiecf_test_url \
	msiecf_test_url_values

msiecf_test_allocation_table_SOURCES = \
	msiecf_test_allocation_table.c \
	msiecf_test_functions.c msiecf_test_functions.h \
	msiecf_test_libbfio.h \
	msiecf_test_libcdata.h \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_allocation_table_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_cache_directory_table_SOURCES = \
	msiecf_test_cache_directory_table.c \
	msiecf_test_functions.c msiecf_test_functions.h \
	msiecf_test_libbfio.h \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_cache_directory_table_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_directory_descriptor_SOURCES = \
	msiecf_test_directory_descriptor.c \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_directory_descriptor_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_error_SOURCES = \
	msiecf_test_error.c \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_unused.h

msiecf_test_error_LDADD = \
	../libmsiecf/libmsiecf.la

msiecf_test_file_SOURCES = \
	msiecf_test_file.c \
	msiecf_test_functions.c msiecf_test_functions.h \
	msiecf_test_getopt.c msiecf_test_getopt.h \
	msiecf_test_libcerror.h \
	msiecf_test_libclocale.h \
	msiecf_test_libcnotify.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_libuna.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h

msiecf_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

msiecf_test_file_header_SOURCES = \
	msiecf_test_file_header.c \
	msiecf_test_functions.c msiecf_test_functions.h \
	msiecf_test_libbfio.h \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_file_header_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_hash_table_SOURCES = \
	msiecf_test_functions.c msiecf_test_functions.h \
	msiecf_test_hash_table.c \
	msiecf_test_libbfio.h \
	msiecf_test_libcdata.h \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_hash_table_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_io_handle_SOURCES = \
	msiecf_test_io_handle.c \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_io_handle_LDADD = \
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

msiecf_test_item_descriptor_SOURCES = \
	msiecf_test_item_descriptor.c \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_item_descriptor_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_leak_SOURCES = \
	msiecf_test_leak.c \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_unused.h

msiecf_test_leak_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_leak_values_SOURCES = \
	msiecf_test_functions.c msiecf_test_functions.h \
	msiecf_test_leak_values.c \
	msiecf_test_libbfio.h \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h

msiecf_test_leak_values_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_notify_SOURCES = \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_notify.c \
	msiecf_test_unused.h

msiecf_test_notify_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_property_type_SOURCES = \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_property_type.c \
	msiecf_test_unused.h

msiecf_test_property_type_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_redirected_SOURCES = \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_redirected.c \
	msiecf_test_unused.h

msiecf_test_redirected_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_redirected_values_SOURCES = \
	msiecf_test_functions.c msiecf_test_functions.h \
	msiecf_test_libbfio.h \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_redirected_values.c \
	msiecf_test_unused.h

msiecf_test_redirected_values_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_support_SOURCES = \
	msiecf_test_functions.c msiecf_test_functions.h \
	msiecf_test_getopt.c msiecf_test_getopt.h \
	msiecf_test_libbfio.h \
	msiecf_test_libcerror.h \
	msiecf_test_libclocale.h \
	msiecf_test_libcnotify.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_libuna.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_support.c \
	msiecf_test_unused.h

msiecf_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_tools_info_handle_SOURCES = \
	../msiecftools/info_handle.c ../msiecftools/info_handle.h \
	msiecf_test_libcerror.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_tools_info_handle.c \
	msiecf_test_unused.h

msiecf_test_tools_info_handle_LDADD = \
	@LIBFDATETIME_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_tools_output_SOURCES = \
	../msiecftools/msiecftools_output.c ../msiecftools/msiecftools_output.h \
	msiecf_test_libcerror.h \
	msiecf_test_macros.h \
	msiecf_test_tools_output.c \
	msiecf_test_unused.h

msiecf_test_tools_output_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_tools_signal_SOURCES = \
	../msiecftools/msiecftools_signal.c ../msiecftools/msiecftools_signal.h \
	msiecf_test_libcerror.h \
	msiecf_test_macros.h \
	msiecf_test_tools_signal.c \
	msiecf_test_unused.h

msiecf_test_tools_signal_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_url_SOURCES = \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_unused.h \
	msiecf_test_url.c

msiecf_test_url_LDADD = \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

msiecf_test_url_values_SOURCES = \
	msiecf_test_functions.c msiecf_test_functions.h \
	msiecf_test_libbfio.h \
	msiecf_test_libcerror.h \
	msiecf_test_libmsiecf.h \
	msiecf_test_macros.h \
	msiecf_test_memory.c msiecf_test_memory.h \
	msiecf_test_unused.h \
	msiecf_test_url_values.c

msiecf_test_url_values_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libmsiecf/libmsiecf.la \
	@LIBCERROR_LIBADD@

DISTCLEANFILES = \
	Makefile \
	Makefile.in \
	notify_stream.log

