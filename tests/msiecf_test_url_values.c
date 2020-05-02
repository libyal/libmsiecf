/*
 * Library url_values type test program
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

#include "../libmsiecf/libmsiecf_io_handle.h"
#include "../libmsiecf/libmsiecf_url_values.h"

uint8_t msiecf_test_url_values_data1[ 512 ] = {
	0x55, 0x52, 0x4c, 0x20, 0x04, 0x00, 0x00, 0x00, 0x80, 0xf9, 0x58, 0x8e, 0x81, 0xee, 0xcd, 0x01,
	0xe0, 0x87, 0x44, 0x8e, 0x78, 0x1d, 0xce, 0x01, 0x6b, 0x42, 0x44, 0x52, 0x00, 0x00, 0x00, 0x00,
	0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x60, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x02, 0x00, 0x10, 0x10, 0xf8, 0x00, 0x00, 0x00,
	0x41, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x6a, 0x42, 0x44, 0x52, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6a, 0x42, 0x44, 0x52,
	0x00, 0x00, 0x00, 0x00, 0xef, 0xbe, 0xad, 0xde, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f,
	0x77, 0x77, 0x77, 0x2e, 0x67, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x63,
	0x68, 0x61, 0x72, 0x74, 0x3f, 0x63, 0x68, 0x73, 0x3d, 0x31, 0x35, 0x30, 0x78, 0x31, 0x35, 0x30,
	0x26, 0x63, 0x68, 0x74, 0x3d, 0x71, 0x72, 0x26, 0x63, 0x68, 0x6c, 0x3d, 0x68, 0x74, 0x74, 0x70,
	0x3a, 0x2f, 0x2f, 0x6c, 0x69, 0x62, 0x6d, 0x73, 0x69, 0x65, 0x63, 0x66, 0x2e, 0x67, 0x6f, 0x6f,
	0x67, 0x6c, 0x65, 0x63, 0x6f, 0x64, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x66, 0x69, 0x6c, 0x65,
	0x73, 0x2f, 0x6c, 0x69, 0x62, 0x6d, 0x73, 0x69, 0x65, 0x63, 0x66, 0x2d, 0x61, 0x6c, 0x70, 0x68,
	0x61, 0x2d, 0x32, 0x30, 0x31, 0x33, 0x30, 0x33, 0x30, 0x35, 0x2e, 0x74, 0x61, 0x72, 0x2e, 0x67,
	0x7a, 0x26, 0x63, 0x68, 0x6c, 0x64, 0x3d, 0x4c, 0x7c, 0x31, 0x26, 0x63, 0x68, 0x6f, 0x65, 0x3d,
	0x55, 0x54, 0x46, 0x2d, 0x38, 0x00, 0xad, 0xde, 0x63, 0x68, 0x61, 0x72, 0x74, 0x5b, 0x31, 0x5d,
	0x2e, 0x70, 0x6e, 0x67, 0x00, 0xbe, 0xad, 0xde, 0x48, 0x54, 0x54, 0x50, 0x2f, 0x31, 0x2e, 0x31,
	0x20, 0x32, 0x30, 0x30, 0x20, 0x4f, 0x4b, 0x0d, 0x0a, 0x58, 0x2d, 0x46, 0x72, 0x61, 0x6d, 0x65,
	0x2d, 0x4f, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x3a, 0x20, 0x41, 0x4c, 0x4c, 0x4f, 0x57, 0x41,
	0x4c, 0x4c, 0x0d, 0x0a, 0x41, 0x63, 0x63, 0x65, 0x73, 0x73, 0x2d, 0x43, 0x6f, 0x6e, 0x74, 0x72,
	0x6f, 0x6c, 0x2d, 0x41, 0x6c, 0x6c, 0x6f, 0x77, 0x2d, 0x4f, 0x72, 0x69, 0x67, 0x69, 0x6e, 0x3a,
	0x20, 0x2a, 0x0d, 0x0a, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x54, 0x79, 0x70, 0x65,
	0x3a, 0x20, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x2f, 0x70, 0x6e, 0x67, 0x0d, 0x0a, 0x58, 0x2d, 0x43,
	0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x54, 0x79, 0x70, 0x65, 0x2d, 0x4f, 0x70, 0x74, 0x69,
	0x6f, 0x6e, 0x73, 0x3a, 0x20, 0x6e, 0x6f, 0x73, 0x6e, 0x69, 0x66, 0x66, 0x0d, 0x0a, 0x43, 0x6f,
	0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x4c, 0x65, 0x6e, 0x67, 0x74, 0x68, 0x3a, 0x20, 0x31, 0x30,
	0x33, 0x30, 0x0d, 0x0a, 0x58, 0x2d, 0x58, 0x53, 0x53, 0x2d, 0x50, 0x72, 0x6f, 0x74, 0x65, 0x63,
	0x74, 0x69, 0x6f, 0x6e, 0x3a, 0x20, 0x31, 0x3b, 0x20, 0x6d, 0x6f, 0x64, 0x65, 0x3d, 0x62, 0x6c,
	0x6f, 0x63, 0x6b, 0x0d, 0x0a, 0x0d, 0x0a, 0x7e, 0x55, 0x3a, 0x2d, 0x0d, 0x0a, 0x00, 0xad, 0xde,
	0xef, 0xbe, 0xad, 0xde, 0xef, 0xbe, 0xad, 0xde, 0xef, 0xbe, 0xad, 0xde, 0xef, 0xbe, 0xad, 0xde,
	0xef, 0xbe, 0xad, 0xde, 0xef, 0xbe, 0xad, 0xde, 0xef, 0xbe, 0xad, 0xde, 0xef, 0xbe, 0xad, 0xde,
	0xef, 0xbe, 0xad, 0xde, 0xef, 0xbe, 0xad, 0xde, 0xef, 0xbe, 0xad, 0xde, 0xef, 0xbe, 0xad, 0xde };

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

/* Tests the libmsiecf_url_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_url_values_initialize(
     void )
{
	libcerror_error_t *error           = NULL;
	libmsiecf_url_values_t *url_values = NULL;
	int result                         = 0;

#if defined( HAVE_MSIECF_TEST_MEMORY )
	int number_of_malloc_fail_tests    = 1;
	int number_of_memset_fail_tests    = 1;
	int test_number                    = 0;
#endif

	/* Test regular cases
	 */
	result = libmsiecf_url_values_initialize(
	          &url_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "url_values",
	 url_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_url_values_free(
	          &url_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "url_values",
	 url_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmsiecf_url_values_initialize(
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

	url_values = (libmsiecf_url_values_t *) 0x12345678UL;

	result = libmsiecf_url_values_initialize(
	          &url_values,
	          &error );

	url_values = NULL;

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
		/* Test libmsiecf_url_values_initialize with malloc failing
		 */
		msiecf_test_malloc_attempts_before_fail = test_number;

		result = libmsiecf_url_values_initialize(
		          &url_values,
		          &error );

		if( msiecf_test_malloc_attempts_before_fail != -1 )
		{
			msiecf_test_malloc_attempts_before_fail = -1;

			if( url_values != NULL )
			{
				libmsiecf_url_values_free(
				 &url_values,
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
			 "url_values",
			 url_values );

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
		/* Test libmsiecf_url_values_initialize with memset failing
		 */
		msiecf_test_memset_attempts_before_fail = test_number;

		result = libmsiecf_url_values_initialize(
		          &url_values,
		          &error );

		if( msiecf_test_memset_attempts_before_fail != -1 )
		{
			msiecf_test_memset_attempts_before_fail = -1;

			if( url_values != NULL )
			{
				libmsiecf_url_values_free(
				 &url_values,
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
			 "url_values",
			 url_values );

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
	if( url_values != NULL )
	{
		libmsiecf_url_values_free(
		 &url_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_url_values_free function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_url_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmsiecf_url_values_free(
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

/* Tests the libmsiecf_url_values_read_data function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_url_values_read_data(
     void )
{
	libcerror_error_t *error           = NULL;
	libmsiecf_io_handle_t *io_handle   = NULL;
	libmsiecf_url_values_t *url_values = NULL;
	int result                         = 0;

	/* Initialize test
	 */
	result = libmsiecf_io_handle_initialize(
	          &io_handle,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->ascii_codepage = LIBMSIECF_CODEPAGE_WINDOWS_1252;
	io_handle->major_version  = 5;
	io_handle->minor_version  = 2;

	result = libmsiecf_url_values_initialize(
	          &url_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "url_values",
	 url_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libmsiecf_url_values_read_data(
	          url_values,
	          io_handle,
	          msiecf_test_url_values_data1,
	          512,
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
	result = libmsiecf_url_values_read_data(
	          NULL,
	          io_handle,
	          msiecf_test_url_values_data1,
	          512,
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

	result = libmsiecf_url_values_read_data(
	          url_values,
	          NULL,
	          msiecf_test_url_values_data1,
	          512,
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

	result = libmsiecf_url_values_read_data(
	          url_values,
	          io_handle,
	          NULL,
	          512,
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

	result = libmsiecf_url_values_read_data(
	          url_values,
	          io_handle,
	          msiecf_test_url_values_data1,
	          (size_t) SSIZE_MAX + 1,
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

	result = libmsiecf_url_values_read_data(
	          url_values,
	          io_handle,
	          msiecf_test_url_values_data1,
	          0,
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
	result = libmsiecf_url_values_free(
	          &url_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "url_values",
	 url_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_io_handle_free(
	          &io_handle,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( url_values != NULL )
	{
		libmsiecf_url_values_free(
		 &url_values,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libmsiecf_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_url_values_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_url_values_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle   = NULL;
	libcerror_error_t *error           = NULL;
	libmsiecf_io_handle_t *io_handle   = NULL;
	libmsiecf_url_values_t *url_values = NULL;
	int result                         = 0;

	/* Initialize test
	 */
	result = libmsiecf_io_handle_initialize(
	          &io_handle,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->ascii_codepage = LIBMSIECF_CODEPAGE_WINDOWS_1252;
	io_handle->major_version  = 5;
	io_handle->minor_version  = 2;

	result = libmsiecf_url_values_initialize(
	          &url_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "url_values",
	 url_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = msiecf_test_open_file_io_handle(
	          &file_io_handle,
	          msiecf_test_url_values_data1,
	          512,
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
	result = libmsiecf_url_values_read_file_io_handle(
	          url_values,
	          io_handle,
	          file_io_handle,
	          0,
	          512,
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
	result = libmsiecf_url_values_read_file_io_handle(
	          NULL,
	          io_handle,
	          file_io_handle,
	          0,
	          512,
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

	result = libmsiecf_url_values_read_file_io_handle(
	          url_values,
	          NULL,
	          file_io_handle,
	          0,
	          512,
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

	result = libmsiecf_url_values_read_file_io_handle(
	          url_values,
	          io_handle,
	          NULL,
	          0,
	          512,
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

	result = libmsiecf_url_values_read_file_io_handle(
	          url_values,
	          io_handle,
	          file_io_handle,
	          -1,
	          512,
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
	          msiecf_test_url_values_data1,
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

	result = libmsiecf_url_values_read_file_io_handle(
	          url_values,
	          io_handle,
	          file_io_handle,
	          0,
	          512,
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
	result = libmsiecf_url_values_free(
	          &url_values,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "url_values",
	 url_values );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_io_handle_free(
	          &io_handle,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( url_values != NULL )
	{
		libmsiecf_url_values_free(
		 &url_values,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libmsiecf_io_handle_free(
		 &io_handle,
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
	 "libmsiecf_url_values_initialize",
	 msiecf_test_url_values_initialize );

	MSIECF_TEST_RUN(
	 "libmsiecf_url_values_free",
	 msiecf_test_url_values_free );

	MSIECF_TEST_RUN(
	 "libmsiecf_url_values_read_data",
	 msiecf_test_url_values_read_data );

	MSIECF_TEST_RUN(
	 "libmsiecf_url_values_read_file_io_handle",
	 msiecf_test_url_values_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */
}

