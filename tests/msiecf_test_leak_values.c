/*
 * Library leak_values type test program
 *
 * Copyright (C) 2009-2020, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "msiecf_test_functions.h"
#include "msiecf_test_libbfio.h"
#include "msiecf_test_libcerror.h"
#include "msiecf_test_libmsiecf.h"
#include "msiecf_test_macros.h"
#include "msiecf_test_memory.h"
#include "msiecf_test_unused.h"

#include "../libmsiecf/libmsiecf_leak_values.h"

uint8_t msiecf_test_leak_values_data1[ 384 ] = {
	0x4c, 0x45, 0x41, 0x4b, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x90, 0x96, 0xc3, 0x14, 0x73, 0x1d, 0xce, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x6c, 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x90, 0x00, 0x00, 0x00,
	0x41, 0x20, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x00, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x6a, 0x42, 0xdc, 0x4c, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6a, 0x42, 0xdc, 0x4c,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x73,
	0x75, 0x70, 0x70, 0x6f, 0x72, 0x74, 0x2e, 0x6d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74,
	0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x6b, 0x62, 0x2f, 0x32, 0x34, 0x39, 0x37, 0x32, 0x38, 0x31, 0x00,
	0x32, 0x34, 0x39, 0x37, 0x32, 0x38, 0x31, 0x5b, 0x31, 0x5d, 0x00, 0x00, 0x48, 0x54, 0x54, 0x50,
	0x2f, 0x31, 0x2e, 0x31, 0x20, 0x32, 0x30, 0x30, 0x20, 0x4f, 0x4b, 0x0d, 0x0a, 0x43, 0x6f, 0x6e,
	0x74, 0x65, 0x6e, 0x74, 0x2d, 0x54, 0x79, 0x70, 0x65, 0x3a, 0x20, 0x74, 0x65, 0x78, 0x74, 0x2f,
	0x68, 0x74, 0x6d, 0x6c, 0x3b, 0x20, 0x63, 0x68, 0x61, 0x72, 0x73, 0x65, 0x74, 0x3d, 0x75, 0x74,
	0x66, 0x2d, 0x38, 0x0d, 0x0a, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x45, 0x6e, 0x63,
	0x6f, 0x64, 0x69, 0x6e, 0x67, 0x3a, 0x20, 0x67, 0x7a, 0x69, 0x70, 0x0d, 0x0a, 0x58, 0x2d, 0x41,
	0x73, 0x70, 0x4e, 0x65, 0x74, 0x2d, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3a, 0x20, 0x34,
	0x2e, 0x30, 0x2e, 0x33, 0x30, 0x33, 0x31, 0x39, 0x0d, 0x0a, 0x58, 0x2d, 0x50, 0x6f, 0x77, 0x65,
	0x72, 0x65, 0x64, 0x2d, 0x42, 0x79, 0x3a, 0x20, 0x41, 0x53, 0x50, 0x2e, 0x4e, 0x45, 0x54, 0x0d,
	0x0a, 0x58, 0x2d, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x54, 0x79, 0x70, 0x65, 0x2d,
	0x4f, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x3a, 0x20, 0x6e, 0x6f, 0x73, 0x6e, 0x69, 0x66, 0x66,
	0x0d, 0x0a, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x4c, 0x65, 0x6e, 0x67, 0x74, 0x68,
	0x3a, 0x20, 0x32, 0x32, 0x33, 0x38, 0x30, 0x0d, 0x0a, 0x0d, 0x0a, 0x7e, 0x55, 0x3a, 0x2d, 0x0d,
	0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

/* Tests the libmsiecf_leak_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_leak_values_initialize(
     void )
{
	libcerror_error_t *error             = NULL;
	libmsiecf_leak_values_t *leak_values = NULL;
	int result                           = 0;

#if defined( HAVE_MSIECF_TEST_MEMORY )
	int number_of_malloc_fail_tests      = 1;
	int number_of_memset_fail_tests      = 1;
	int test_number                      = 0;
#endif

	/* Test regular cases
	 */
	result = libmsiecf_leak_values_initialize(
	          &leak_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "leak_values",
	 leak_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_leak_values_free(
	          &leak_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "leak_values",
	 leak_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmsiecf_leak_values_initialize(
	          NULL,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	leak_values = (libmsiecf_leak_values_t *) 0x12345678UL;

	result = libmsiecf_leak_values_initialize(
	          &leak_values,
	          &error );

	leak_values = NULL;

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_MSIECF_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libmsiecf_leak_values_initialize with malloc failing
		 */
		msiecf_test_malloc_attempts_before_fail = test_number;

		result = libmsiecf_leak_values_initialize(
		          &leak_values,
		          &error );

		if( msiecf_test_malloc_attempts_before_fail != -1 )
		{
			msiecf_test_malloc_attempts_before_fail = -1;

			if( leak_values != NULL )
			{
				libmsiecf_leak_values_free(
				 &leak_values,
				 NULL );
			}
		}
		else
		{
			MSIECF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			MSIECF_TEST_ASSERT_IS_NULL(
			 "leak_values",
			 leak_values );

			MSIECF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libmsiecf_leak_values_initialize with memset failing
		 */
		msiecf_test_memset_attempts_before_fail = test_number;

		result = libmsiecf_leak_values_initialize(
		          &leak_values,
		          &error );

		if( msiecf_test_memset_attempts_before_fail != -1 )
		{
			msiecf_test_memset_attempts_before_fail = -1;

			if( leak_values != NULL )
			{
				libmsiecf_leak_values_free(
				 &leak_values,
				 NULL );
			}
		}
		else
		{
			MSIECF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			MSIECF_TEST_ASSERT_IS_NULL(
			 "leak_values",
			 leak_values );

			MSIECF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_MSIECF_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( leak_values != NULL )
	{
		libmsiecf_leak_values_free(
		 &leak_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_leak_values_free function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_leak_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmsiecf_leak_values_free(
	          NULL,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmsiecf_leak_values_read_data function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_leak_values_read_data(
     void )
{
	libcerror_error_t *error             = NULL;
	libmsiecf_leak_values_t *leak_values = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libmsiecf_leak_values_initialize(
	          &leak_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "leak_values",
	 leak_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libmsiecf_leak_values_read_data(
	          leak_values,
	          msiecf_test_leak_values_data1,
	          384,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmsiecf_leak_values_read_data(
	          NULL,
	          msiecf_test_leak_values_data1,
	          384,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmsiecf_leak_values_read_data(
	          leak_values,
	          NULL,
	          384,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmsiecf_leak_values_read_data(
	          leak_values,
	          msiecf_test_leak_values_data1,
	          (size_t) SSIZE_MAX + 1,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmsiecf_leak_values_read_data(
	          leak_values,
	          msiecf_test_leak_values_data1,
	          0,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libmsiecf_leak_values_free(
	          &leak_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "leak_values",
	 leak_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( leak_values != NULL )
	{
		libmsiecf_leak_values_free(
		 &leak_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_leak_values_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_leak_values_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle     = NULL;
	libcerror_error_t *error             = NULL;
	libmsiecf_leak_values_t *leak_values = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libmsiecf_leak_values_initialize(
	          &leak_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "leak_values",
	 leak_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = msiecf_test_open_file_io_handle(
	          &file_io_handle,
	          msiecf_test_leak_values_data1,
	          384,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libmsiecf_leak_values_read_file_io_handle(
	          leak_values,
	          file_io_handle,
	          0,
	          384,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmsiecf_leak_values_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          0,
	          384,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmsiecf_leak_values_read_file_io_handle(
	          leak_values,
	          NULL,
	          0,
	          384,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libmsiecf_leak_values_read_file_io_handle(
	          leak_values,
	          file_io_handle,
	          -1,
	          384,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up file IO handle
	 */
	result = msiecf_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small
	 */
	result = msiecf_test_open_file_io_handle(
	          &file_io_handle,
	          msiecf_test_leak_values_data1,
	          8,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_leak_values_read_file_io_handle(
	          leak_values,
	          file_io_handle,
	          0,
	          384,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          0,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = msiecf_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libmsiecf_leak_values_free(
	          &leak_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "leak_values",
	 leak_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( leak_values != NULL )
	{
		libmsiecf_leak_values_free(
		 &leak_values,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc MSIECF_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] MSIECF_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc MSIECF_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] MSIECF_TEST_ATTRIBUTE_UNUSED )
#endif
{
	MSIECF_TEST_UNREFERENCED_PARAMETER( argc )
	MSIECF_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

	MSIECF_TEST_RUN(
	 "libmsiecf_leak_values_initialize",
	 msiecf_test_leak_values_initialize );

	MSIECF_TEST_RUN(
	 "libmsiecf_leak_values_free",
	 msiecf_test_leak_values_free );

	MSIECF_TEST_RUN(
	 "libmsiecf_leak_values_read_data",
	 msiecf_test_leak_values_read_data );

	MSIECF_TEST_RUN(
	 "libmsiecf_leak_values_read_file_io_handle",
	 msiecf_test_leak_values_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

