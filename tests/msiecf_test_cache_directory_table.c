/*
 * Library cache_directory_table type test program
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

#include "../libmsiecf/libmsiecf_cache_directory_table.h"

uint8_t msiecf_test_cache_directory_table_data1[ 52 ] = {
	0x04, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x4e, 0x32, 0x41, 0x44, 0x33, 0x31, 0x30, 0x35,
	0x57, 0x00, 0x00, 0x00, 0x38, 0x58, 0x45, 0x41, 0x38, 0x37, 0x31, 0x4c, 0x57, 0x00, 0x00, 0x00,
	0x4f, 0x31, 0x47, 0x56, 0x55, 0x44, 0x4d, 0x44, 0x56, 0x00, 0x00, 0x00, 0x48, 0x44, 0x54, 0x31,
	0x4a, 0x39, 0x58, 0x37 };

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

/* Tests the libmsiecf_cache_directory_table_initialize function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_cache_directory_table_initialize(
     void )
{
	libcerror_error_t *error                                 = NULL;
	libmsiecf_cache_directory_table_t *cache_directory_table = NULL;
	int result                                               = 0;

#if defined( HAVE_MSIECF_TEST_MEMORY )
	int number_of_malloc_fail_tests                          = 1;
	int number_of_memset_fail_tests                          = 1;
	int test_number                                          = 0;
#endif

	/* Test regular cases
	 */
	result = libmsiecf_cache_directory_table_initialize(
	          &cache_directory_table,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "cache_directory_table",
	 cache_directory_table );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_cache_directory_table_free(
	          &cache_directory_table,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "cache_directory_table",
	 cache_directory_table );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmsiecf_cache_directory_table_initialize(
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

	cache_directory_table = (libmsiecf_cache_directory_table_t *) 0x12345678UL;

	result = libmsiecf_cache_directory_table_initialize(
	          &cache_directory_table,
	          &error );

	cache_directory_table = NULL;

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
		/* Test libmsiecf_cache_directory_table_initialize with malloc failing
		 */
		msiecf_test_malloc_attempts_before_fail = test_number;

		result = libmsiecf_cache_directory_table_initialize(
		          &cache_directory_table,
		          &error );

		if( msiecf_test_malloc_attempts_before_fail != -1 )
		{
			msiecf_test_malloc_attempts_before_fail = -1;

			if( cache_directory_table != NULL )
			{
				libmsiecf_cache_directory_table_free(
				 &cache_directory_table,
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
			 "cache_directory_table",
			 cache_directory_table );

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
		/* Test libmsiecf_cache_directory_table_initialize with memset failing
		 */
		msiecf_test_memset_attempts_before_fail = test_number;

		result = libmsiecf_cache_directory_table_initialize(
		          &cache_directory_table,
		          &error );

		if( msiecf_test_memset_attempts_before_fail != -1 )
		{
			msiecf_test_memset_attempts_before_fail = -1;

			if( cache_directory_table != NULL )
			{
				libmsiecf_cache_directory_table_free(
				 &cache_directory_table,
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
			 "cache_directory_table",
			 cache_directory_table );

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
	if( cache_directory_table != NULL )
	{
		libmsiecf_cache_directory_table_free(
		 &cache_directory_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_cache_directory_table_free function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_cache_directory_table_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmsiecf_cache_directory_table_free(
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

/* Tests the libmsiecf_cache_directory_table_read_data function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_cache_directory_table_read_data(
     void )
{
	libcerror_error_t *error                                 = NULL;
	libmsiecf_cache_directory_table_t *cache_directory_table = NULL;
	int result                                               = 0;

	/* Initialize test
	 */
	result = libmsiecf_cache_directory_table_initialize(
	          &cache_directory_table,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "cache_directory_table",
	 cache_directory_table );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libmsiecf_cache_directory_table_read_data(
	          cache_directory_table,
	          msiecf_test_cache_directory_table_data1,
	          52,
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
	result = libmsiecf_cache_directory_table_read_data(
	          NULL,
	          msiecf_test_cache_directory_table_data1,
	          52,
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

	result = libmsiecf_cache_directory_table_read_data(
	          cache_directory_table,
	          NULL,
	          52,
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

	result = libmsiecf_cache_directory_table_read_data(
	          cache_directory_table,
	          msiecf_test_cache_directory_table_data1,
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

	result = libmsiecf_cache_directory_table_read_data(
	          cache_directory_table,
	          msiecf_test_cache_directory_table_data1,
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
	result = libmsiecf_cache_directory_table_free(
	          &cache_directory_table,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "cache_directory_table",
	 cache_directory_table );

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
	if( cache_directory_table != NULL )
	{
		libmsiecf_cache_directory_table_free(
		 &cache_directory_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_cache_directory_table_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_cache_directory_table_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle                         = NULL;
	libcerror_error_t *error                                 = NULL;
	libmsiecf_cache_directory_table_t *cache_directory_table = NULL;
	int result                                               = 0;

	/* Initialize test
	 */
	result = libmsiecf_cache_directory_table_initialize(
	          &cache_directory_table,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "cache_directory_table",
	 cache_directory_table );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = msiecf_test_open_file_io_handle(
	          &file_io_handle,
	          msiecf_test_cache_directory_table_data1,
	          52,
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
	result = libmsiecf_cache_directory_table_read_file_io_handle(
	          cache_directory_table,
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
	result = libmsiecf_cache_directory_table_read_file_io_handle(
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

	result = libmsiecf_cache_directory_table_read_file_io_handle(
	          cache_directory_table,
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

	result = libmsiecf_cache_directory_table_read_file_io_handle(
	          cache_directory_table,
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
	          msiecf_test_cache_directory_table_data1,
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

	result = libmsiecf_cache_directory_table_read_file_io_handle(
	          cache_directory_table,
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
	result = libmsiecf_cache_directory_table_free(
	          &cache_directory_table,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "cache_directory_table",
	 cache_directory_table );

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
	if( cache_directory_table != NULL )
	{
		libmsiecf_cache_directory_table_free(
		 &cache_directory_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_cache_directory_table_get_number_of_cache_directories function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_cache_directory_table_get_number_of_cache_directories(
     libmsiecf_cache_directory_table_t *cache_directory_table )
{
	libcerror_error_t *error        = NULL;
	int number_of_cache_directories = 0;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libmsiecf_cache_directory_table_get_number_of_cache_directories(
	          cache_directory_table,
	          &number_of_cache_directories,
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
	result = libmsiecf_cache_directory_table_get_number_of_cache_directories(
	          NULL,
	          &number_of_cache_directories,
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

	result = libmsiecf_cache_directory_table_get_number_of_cache_directories(
	          cache_directory_table,
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
#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )
	libcerror_error_t *error                                 = NULL;
	libmsiecf_cache_directory_table_t *cache_directory_table = NULL;
	int result                                               = 0;
#endif

	MSIECF_TEST_UNREFERENCED_PARAMETER( argc )
	MSIECF_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

	MSIECF_TEST_RUN(
	 "libmsiecf_cache_directory_table_initialize",
	 msiecf_test_cache_directory_table_initialize );

	MSIECF_TEST_RUN(
	 "libmsiecf_cache_directory_table_free",
	 msiecf_test_cache_directory_table_free );

	MSIECF_TEST_RUN(
	 "libmsiecf_cache_directory_table_read_data",
	 msiecf_test_cache_directory_table_read_data );

	MSIECF_TEST_RUN(
	 "libmsiecf_cache_directory_table_read_file_io_handle",
	 msiecf_test_cache_directory_table_read_file_io_handle );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize cache_directory_table for tests
	 */
	result = libmsiecf_cache_directory_table_initialize(
	          &cache_directory_table,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "cache_directory_table",
	 cache_directory_table );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_cache_directory_table_read_data(
	          cache_directory_table,
	          msiecf_test_cache_directory_table_data1,
	          52,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Run tests
	 */
	MSIECF_TEST_RUN_WITH_ARGS(
	 "libmsiecf_cache_directory_table_get_number_of_cache_directories",
	 msiecf_test_cache_directory_table_get_number_of_cache_directories,
	 cache_directory_table );

	/* TODO: add tests for libmsiecf_cache_directory_table_get_directory_name_by_index */

	/* Clean up
	 */
	result = libmsiecf_cache_directory_table_free(
	          &cache_directory_table,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "cache_directory_table",
	 cache_directory_table );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( cache_directory_table != NULL )
	{
		libmsiecf_cache_directory_table_free(
		 &cache_directory_table,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */
}

