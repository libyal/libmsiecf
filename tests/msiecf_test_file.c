/*
 * Library file type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "msiecf_test_functions.h"
#include "msiecf_test_getopt.h"
#include "msiecf_test_libcerror.h"
#include "msiecf_test_libclocale.h"
#include "msiecf_test_libmsiecf.h"
#include "msiecf_test_libuna.h"
#include "msiecf_test_macros.h"
#include "msiecf_test_memory.h"

#include "../libmsiecf/libmsiecf_file.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make msiecf_test_file generate verbose output
#define MSIECF_TEST_FILE_VERBOSE
 */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int msiecf_test_file_open_source(
     libmsiecf_file_t **file,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "msiecf_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( libmsiecf_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmsiecf_file_open_wide(
	          *file,
	          source,
	          LIBMSIECF_OPEN_READ,
	          error );
#else
	result = libmsiecf_file_open(
	          *file,
	          source,
	          LIBMSIECF_OPEN_READ,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libmsiecf_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int msiecf_test_file_close_source(
     libmsiecf_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "msiecf_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libmsiecf_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libmsiecf_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libmsiecf_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libmsiecf_file_t *file          = NULL;
	int result                      = 0;

#if defined( HAVE_MSIECF_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libmsiecf_file_initialize(
	          &file,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_file_free(
	          &file,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libmsiecf_file_initialize(
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

	file = (libmsiecf_file_t *) 0x12345678UL;

	result = libmsiecf_file_initialize(
	          &file,
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

	file = NULL;

#if defined( HAVE_MSIECF_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libmsiecf_file_initialize with malloc failing
		 */
		msiecf_test_malloc_attempts_before_fail = test_number;

		result = libmsiecf_file_initialize(
		          &file,
		          &error );

		if( msiecf_test_malloc_attempts_before_fail != -1 )
		{
			msiecf_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libmsiecf_file_free(
				 &file,
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
			 "file",
			 file );

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
		/* Test libmsiecf_file_initialize with memset failing
		 */
		msiecf_test_memset_attempts_before_fail = test_number;

		result = libmsiecf_file_initialize(
		          &file,
		          &error );

		if( msiecf_test_memset_attempts_before_fail != -1 )
		{
			msiecf_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libmsiecf_file_free(
				 &file,
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
			 "file",
			 file );

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
	if( file != NULL )
	{
		libmsiecf_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_file_free function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmsiecf_file_free(
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

/* Tests the libmsiecf_file_open function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libmsiecf_file_t *file   = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = msiecf_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_file_initialize(
	          &file,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libmsiecf_file_open(
	          file,
	          narrow_source,
	          LIBMSIECF_OPEN_READ,
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
	result = libmsiecf_file_open(
	          file,
	          narrow_source,
	          LIBMSIECF_OPEN_READ,
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
	result = libmsiecf_file_free(
	          &file,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libmsiecf_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libmsiecf_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libmsiecf_file_t *file   = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = msiecf_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_file_initialize(
	          &file,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libmsiecf_file_open_wide(
	          file,
	          wide_source,
	          LIBMSIECF_OPEN_READ,
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
	result = libmsiecf_file_open_wide(
	          file,
	          wide_source,
	          LIBMSIECF_OPEN_READ,
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
	result = libmsiecf_file_free(
	          &file,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libmsiecf_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libmsiecf_file_close function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libmsiecf_file_close(
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

/* Tests the libmsiecf_file_open and libmsiecf_file_close functions
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libmsiecf_file_t *file   = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libmsiecf_file_initialize(
	          &file,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmsiecf_file_open_wide(
	          file,
	          source,
	          LIBMSIECF_OPEN_READ,
	          &error );
#else
	result = libmsiecf_file_open(
	          file,
	          source,
	          LIBMSIECF_OPEN_READ,
	          &error );
#endif

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_file_close(
	          file,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmsiecf_file_open_wide(
	          file,
	          source,
	          LIBMSIECF_OPEN_READ,
	          &error );
#else
	result = libmsiecf_file_open(
	          file,
	          source,
	          LIBMSIECF_OPEN_READ,
	          &error );
#endif

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libmsiecf_file_close(
	          file,
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
	result = libmsiecf_file_free(
	          &file,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libmsiecf_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libmsiecf_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_signal_abort(
     libmsiecf_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libmsiecf_file_signal_abort(
	          file,
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
	result = libmsiecf_file_signal_abort(
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

/* Tests the libmsiecf_file_get_size function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_get_size(
     libmsiecf_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	int result               = 0;
	int size_is_set          = 0;

	/* Test regular cases
	 */
	result = libmsiecf_file_get_size(
	          file,
	          &size,
	          &error );

	MSIECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size_is_set = result;

	/* Test error cases
	 */
	result = libmsiecf_file_get_size(
	          NULL,
	          &size,
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

	if( size_is_set != 0 )
	{
		result = libmsiecf_file_get_size(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmsiecf_file_get_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_get_ascii_codepage(
     libmsiecf_file_t *file )
{
	libcerror_error_t *error  = NULL;
	int ascii_codepage        = 0;
	int ascii_codepage_is_set = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libmsiecf_file_get_ascii_codepage(
	          file,
	          &ascii_codepage,
	          &error );

	MSIECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	ascii_codepage_is_set = result;

	/* Test error cases
	 */
	result = libmsiecf_file_get_ascii_codepage(
	          NULL,
	          &ascii_codepage,
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

	if( ascii_codepage_is_set != 0 )
	{
		result = libmsiecf_file_get_ascii_codepage(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmsiecf_file_set_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_set_ascii_codepage(
     libmsiecf_file_t *file )
{
	int supported_codepages[ 15 ] = {
		LIBMSIECF_CODEPAGE_ASCII,
		LIBMSIECF_CODEPAGE_WINDOWS_874,
		LIBMSIECF_CODEPAGE_WINDOWS_932,
		LIBMSIECF_CODEPAGE_WINDOWS_936,
		LIBMSIECF_CODEPAGE_WINDOWS_949,
		LIBMSIECF_CODEPAGE_WINDOWS_950,
		LIBMSIECF_CODEPAGE_WINDOWS_1250,
		LIBMSIECF_CODEPAGE_WINDOWS_1251,
		LIBMSIECF_CODEPAGE_WINDOWS_1252,
		LIBMSIECF_CODEPAGE_WINDOWS_1253,
		LIBMSIECF_CODEPAGE_WINDOWS_1254,
		LIBMSIECF_CODEPAGE_WINDOWS_1255,
		LIBMSIECF_CODEPAGE_WINDOWS_1256,
		LIBMSIECF_CODEPAGE_WINDOWS_1257,
		LIBMSIECF_CODEPAGE_WINDOWS_1258 };

	int unsupported_codepages[ 17 ] = {
		LIBMSIECF_CODEPAGE_ISO_8859_1,
		LIBMSIECF_CODEPAGE_ISO_8859_2,
		LIBMSIECF_CODEPAGE_ISO_8859_3,
		LIBMSIECF_CODEPAGE_ISO_8859_4,
		LIBMSIECF_CODEPAGE_ISO_8859_5,
		LIBMSIECF_CODEPAGE_ISO_8859_6,
		LIBMSIECF_CODEPAGE_ISO_8859_7,
		LIBMSIECF_CODEPAGE_ISO_8859_8,
		LIBMSIECF_CODEPAGE_ISO_8859_9,
		LIBMSIECF_CODEPAGE_ISO_8859_10,
		LIBMSIECF_CODEPAGE_ISO_8859_11,
		LIBMSIECF_CODEPAGE_ISO_8859_13,
		LIBMSIECF_CODEPAGE_ISO_8859_14,
		LIBMSIECF_CODEPAGE_ISO_8859_15,
		LIBMSIECF_CODEPAGE_ISO_8859_16,
		LIBMSIECF_CODEPAGE_KOI8_R,
		LIBMSIECF_CODEPAGE_KOI8_U };

	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int index                = 0;
	int result               = 0;

	/* Test set ASCII codepage
	 */
	for( index = 0;
	     index < 15;
	     index++ )
	{
		codepage = supported_codepages[ index ];

		result = libmsiecf_file_set_ascii_codepage(
		          file,
		          codepage,
		          &error );

		MSIECF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        MSIECF_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
	/* Test error cases
	 */
	result = libmsiecf_file_set_ascii_codepage(
	          NULL,
	          LIBMSIECF_CODEPAGE_ASCII,
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

	for( index = 0;
	     index < 17;
	     index++ )
	{
		codepage = unsupported_codepages[ index ];

		result = libmsiecf_file_set_ascii_codepage(
		          file,
		          codepage,
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
	}
	/* Clean up
	 */
	result = libmsiecf_file_set_ascii_codepage(
	          file,
	          LIBMSIECF_CODEPAGE_WINDOWS_1252,
	          &error );

	MSIECF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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
	return( 0 );
}

/* Tests the libmsiecf_file_get_number_of_unallocated_blocks function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_get_number_of_unallocated_blocks(
     libmsiecf_file_t *file )
{
	libcerror_error_t *error                = NULL;
	int number_of_unallocated_blocks        = 0;
	int number_of_unallocated_blocks_is_set = 0;
	int result                              = 0;

	/* Test regular cases
	 */
	result = libmsiecf_file_get_number_of_unallocated_blocks(
	          file,
	          &number_of_unallocated_blocks,
	          &error );

	MSIECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_unallocated_blocks_is_set = result;

	/* Test error cases
	 */
	result = libmsiecf_file_get_number_of_unallocated_blocks(
	          NULL,
	          &number_of_unallocated_blocks,
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

	if( number_of_unallocated_blocks_is_set != 0 )
	{
		result = libmsiecf_file_get_number_of_unallocated_blocks(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmsiecf_file_get_number_of_cache_directories function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_get_number_of_cache_directories(
     libmsiecf_file_t *file )
{
	libcerror_error_t *error               = NULL;
	int number_of_cache_directories        = 0;
	int number_of_cache_directories_is_set = 0;
	int result                             = 0;

	/* Test regular cases
	 */
	result = libmsiecf_file_get_number_of_cache_directories(
	          file,
	          &number_of_cache_directories,
	          &error );

	MSIECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_cache_directories_is_set = result;

	/* Test error cases
	 */
	result = libmsiecf_file_get_number_of_cache_directories(
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

	if( number_of_cache_directories_is_set != 0 )
	{
		result = libmsiecf_file_get_number_of_cache_directories(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmsiecf_file_get_number_of_items function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_get_number_of_items(
     libmsiecf_file_t *file )
{
	libcerror_error_t *error   = NULL;
	int number_of_items        = 0;
	int number_of_items_is_set = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	result = libmsiecf_file_get_number_of_items(
	          file,
	          &number_of_items,
	          &error );

	MSIECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_items_is_set = result;

	/* Test error cases
	 */
	result = libmsiecf_file_get_number_of_items(
	          NULL,
	          &number_of_items,
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

	if( number_of_items_is_set != 0 )
	{
		result = libmsiecf_file_get_number_of_items(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libmsiecf_file_get_number_of_recovered_items function
 * Returns 1 if successful or 0 if not
 */
int msiecf_test_file_get_number_of_recovered_items(
     libmsiecf_file_t *file )
{
	libcerror_error_t *error             = NULL;
	int number_of_recovered_items        = 0;
	int number_of_recovered_items_is_set = 0;
	int result                           = 0;

	/* Test regular cases
	 */
	result = libmsiecf_file_get_number_of_recovered_items(
	          file,
	          &number_of_recovered_items,
	          &error );

	MSIECF_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	MSIECF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_recovered_items_is_set = result;

	/* Test error cases
	 */
	result = libmsiecf_file_get_number_of_recovered_items(
	          NULL,
	          &number_of_recovered_items,
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

	if( number_of_recovered_items_is_set != 0 )
	{
		result = libmsiecf_file_get_number_of_recovered_items(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	libmsiecf_file_t *file     = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = msiecf_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( MSIECF_TEST_FILE_VERBOSE )
	libmsiecf_notify_set_verbose(
	 1 );
	libmsiecf_notify_set_stream(
	 stderr,
	 NULL );
#endif

	MSIECF_TEST_RUN(
	 "libmsiecf_file_initialize",
	 msiecf_test_file_initialize );

	MSIECF_TEST_RUN(
	 "libmsiecf_file_free",
	 msiecf_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_open",
		 msiecf_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_open_wide",
		 msiecf_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBMSIECF_HAVE_BFIO )

		/* TODO add test for libmsiecf_file_open_file_io_handle */

#endif /* defined( LIBMSIECF_HAVE_BFIO ) */

		MSIECF_TEST_RUN(
		 "libmsiecf_file_close",
		 msiecf_test_file_close );

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_open_close",
		 msiecf_test_file_open_close,
		 source );

		/* Initialize test
		 */
		result = msiecf_test_file_open_source(
		          &file,
		          source,
		          &error );

		MSIECF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        MSIECF_TEST_ASSERT_IS_NOT_NULL(
	         "file",
	         file );

	        MSIECF_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_signal_abort",
		 msiecf_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT )

		/* TODO: add tests for libmsiecf_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBMSIECF_DLL_IMPORT ) */

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_get_size",
		 msiecf_test_file_get_size,
		 file );

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_get_ascii_codepage",
		 msiecf_test_file_get_ascii_codepage,
		 file );

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_set_ascii_codepage",
		 msiecf_test_file_set_ascii_codepage,
		 file );

		/* TODO: add tests for libmsiecf_file_get_format_version */

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_get_number_of_unallocated_blocks",
		 msiecf_test_file_get_number_of_unallocated_blocks,
		 file );

		/* TODO: add tests for libmsiecf_file_get_unallocated_block */

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_get_number_of_cache_directories",
		 msiecf_test_file_get_number_of_cache_directories,
		 file );

		/* TODO: add tests for libmsiecf_file_get_cache_directory_name */

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_get_number_of_items",
		 msiecf_test_file_get_number_of_items,
		 file );

		/* TODO: add tests for libmsiecf_file_get_item_by_index */

		MSIECF_TEST_RUN_WITH_ARGS(
		 "libmsiecf_file_get_number_of_recovered_items",
		 msiecf_test_file_get_number_of_recovered_items,
		 file );

		/* TODO: add tests for libmsiecf_file_get_recovered_item_by_index */

		/* Clean up
		 */
		result = msiecf_test_file_close_source(
		          &file,
		          &error );

		MSIECF_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		MSIECF_TEST_ASSERT_IS_NULL(
	         "file",
	         file );

	        MSIECF_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		msiecf_test_file_close_source(
		 &file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

