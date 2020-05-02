/*
 * Library file_header type test program
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

#include "../libmsiecf/libmsiecf_file_header.h"

uint8_t msiecf_test_file_header_data1[ 72 ] = {
	0x43, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x20, 0x55, 0x72, 0x6c, 0x43, 0x61, 0x63, 0x68, 0x65, 0x20,
	0x4d, 0x4d, 0x46, 0x20, 0x56, 0x65, 0x72, 0x20, 0x35, 0x2e, 0x32, 0x00, 0x00, 0x80, 0x00, 0x00,
	0x00, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

/* Tests the libmsiecf_file_header_initialize function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_header_initialize(
     void )
{
	libcerror_error_t *error             = NULL;
	libmsiecf_file_header_t *file_header = NULL;
	int result                           = 0;

#if defined( HAVE_MSIECF_TEST_MEMORY )
	int number_of_malloc_fail_tests      = 1;
	int number_of_memset_fail_tests      = 1;
	int test_number                      = 0;
#endif

	/* Test regular cases
	 */
	result = libmsiecf_file_header_initialize(
	          &file_header,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_file_header_free(
	          &file_header,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmsiecf_file_header_initialize(
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

	file_header = (libmsiecf_file_header_t *) 0x12345678UL;

	result = libmsiecf_file_header_initialize(
	          &file_header,
	          &error );

	file_header = NULL;

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
		/* Test libmsiecf_file_header_initialize with malloc failing
		 */
		msiecf_test_malloc_attempts_before_fail = test_number;

		result = libmsiecf_file_header_initialize(
		          &file_header,
		          &error );

		if( msiecf_test_malloc_attempts_before_fail != -1 )
		{
			msiecf_test_malloc_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				libmsiecf_file_header_free(
				 &file_header,
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
			 "file_header",
			 file_header );

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
		/* Test libmsiecf_file_header_initialize with memset failing
		 */
		msiecf_test_memset_attempts_before_fail = test_number;

		result = libmsiecf_file_header_initialize(
		          &file_header,
		          &error );

		if( msiecf_test_memset_attempts_before_fail != -1 )
		{
			msiecf_test_memset_attempts_before_fail = -1;

			if( file_header != NULL )
			{
				libmsiecf_file_header_free(
				 &file_header,
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
			 "file_header",
			 file_header );

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
	if( file_header != NULL )
	{
		libmsiecf_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_file_header_free function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_header_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmsiecf_file_header_free(
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

/* Tests the libmsiecf_file_header_read_data function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_header_read_data(
     void )
{
	libcerror_error_t *error             = NULL;
	libmsiecf_file_header_t *file_header = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libmsiecf_file_header_initialize(
	          &file_header,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libmsiecf_file_header_read_data(
	          file_header,
	          msiecf_test_file_header_data1,
	          72,
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
	result = libmsiecf_file_header_read_data(
	          NULL,
	          msiecf_test_file_header_data1,
	          72,
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

	result = libmsiecf_file_header_read_data(
	          file_header,
	          NULL,
	          72,
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

	result = libmsiecf_file_header_read_data(
	          file_header,
	          msiecf_test_file_header_data1,
	          (size_t) SSIZE_MAX + 1,
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

	result = libmsiecf_file_header_read_data(
	          file_header,
	          msiecf_test_file_header_data1,
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
	result = libmsiecf_file_header_free(
	          &file_header,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

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
	if( file_header != NULL )
	{
		libmsiecf_file_header_free(
		 &file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_file_header_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_header_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle     = NULL;
	libcerror_error_t *error             = NULL;
	libmsiecf_file_header_t *file_header = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libmsiecf_file_header_initialize(
	          &file_header,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "file_header",
	 file_header );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = msiecf_test_open_file_io_handle(
	          &file_io_handle,
	          msiecf_test_file_header_data1,
	          72,
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
	result = libmsiecf_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
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
	result = libmsiecf_file_header_read_file_io_handle(
	          NULL,
	          file_io_handle,
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

	result = libmsiecf_file_header_read_file_io_handle(
	          file_header,
	          NULL,
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

	result = libmsiecf_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
	          -1,
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
	          msiecf_test_file_header_data1,
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

	result = libmsiecf_file_header_read_file_io_handle(
	          file_header,
	          file_io_handle,
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
	result = libmsiecf_file_header_free(
	          &file_header,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "file_header",
	 file_header );

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
	if( file_header != NULL )
	{
		libmsiecf_file_header_free(
		 &file_header,
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
	 "libmsiecf_file_header_initialize",
	 msiecf_test_file_header_initialize );

	MSIECF_TEST_RUN(
	 "libmsiecf_file_header_free",
	 msiecf_test_file_header_free );

	MSIECF_TEST_RUN(
	 "libmsiecf_file_header_read_data",
	 msiecf_test_file_header_read_data );

	MSIECF_TEST_RUN(
	 "libmsiecf_file_header_read_file_io_handle",
	 msiecf_test_file_header_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */
}

