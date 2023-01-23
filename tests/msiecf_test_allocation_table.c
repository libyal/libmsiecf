/*
 * Library allocation_table type test program
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
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
#include "msiecf_test_libcdata.h"
#include "msiecf_test_libcerror.h"
#include "msiecf_test_libmsiecf.h"
#include "msiecf_test_macros.h"
#include "msiecf_test_memory.h"
#include "msiecf_test_unused.h"

#include "../libmsiecf/libmsiecf_allocation_table.h"
#include "../libmsiecf/libmsiecf_definitions.h"

uint8_t msiecf_test_allocation_table_data1[ 16 ] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

/* Tests the libmsiecf_allocation_table_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_allocation_table_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle        = NULL;
	libcdata_range_list_t *allocation_table = NULL;
	libcerror_error_t *error                = NULL;
	int result                              = 0;

	/* Initialize test
	 */
	result = libcdata_range_list_initialize(
	          &allocation_table,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "allocation_table",
	 allocation_table );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = msiecf_test_open_file_io_handle(
	          &file_io_handle,
	          msiecf_test_allocation_table_data1,
	          16,
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
	result = libmsiecf_allocation_table_read_file_io_handle(
	          allocation_table,
	          file_io_handle,
	          0,
	          32768,
	          0x4000,
	          LIBMSIECF_DEFAULT_BLOCK_SIZE,
	          128,
	          58,
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
	result = libmsiecf_allocation_table_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          0,
	          32768,
	          0x4000,
	          LIBMSIECF_DEFAULT_BLOCK_SIZE,
	          128,
	          58,
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

	result = libmsiecf_allocation_table_read_file_io_handle(
	          allocation_table,
	          NULL,
	          0,
	          32768,
	          0x4000,
	          LIBMSIECF_DEFAULT_BLOCK_SIZE,
	          128,
	          58,
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

	result = libmsiecf_allocation_table_read_file_io_handle(
	          allocation_table,
	          file_io_handle,
	          -1,
	          32768,
	          0x4000,
	          LIBMSIECF_DEFAULT_BLOCK_SIZE,
	          128,
	          58,
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

	/* Clean up
	 */
	result = libcdata_range_list_free(
	          &allocation_table,
	          NULL,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "allocation_table",
	 allocation_table );

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
	if( allocation_table != NULL )
	{
		libcdata_range_list_free(
		 &allocation_table,
		 NULL,
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
	 "libmsiecf_allocation_table_read_file_io_handle",
	 msiecf_test_allocation_table_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */
}

