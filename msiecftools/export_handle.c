/*
 * Export handle
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
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "export_handle.h"
#include "log_handle.h"
#include "msiecftools_libcerror.h"
#include "msiecftools_libclocale.h"
#include "msiecftools_libcnotify.h"
#include "msiecftools_libfdatetime.h"
#include "msiecftools_libmsiecf.h"

#define EXPORT_HANDLE_NOTIFY_STREAM		stdout

/* Creates an export handle
 * Make sure the value export_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int export_handle_initialize(
     export_handle_t **export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_initialize";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid export handle value already set.",
		 function );

		return( -1 );
	}
	*export_handle = memory_allocate_structure(
	                  export_handle_t );

	if( *export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create export handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *export_handle,
	     0,
	     sizeof( export_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear export handle.",
		 function );

		goto on_error;
	}
	if( libmsiecf_file_initialize(
	     &( ( *export_handle )->input_file ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input file.",
		 function );

		goto on_error;
	}
	( *export_handle )->export_mode    = EXPORT_MODE_ITEMS;
	( *export_handle )->notify_stream  = EXPORT_HANDLE_NOTIFY_STREAM;
	( *export_handle )->ascii_codepage = LIBMSIECF_CODEPAGE_WINDOWS_1252;

	return( 1 );

on_error:
	if( *export_handle != NULL )
	{
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( -1 );
}

/* Frees an export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_free(
     export_handle_t **export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_free";
	int result            = 1;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( *export_handle != NULL )
	{
		if( ( *export_handle )->input_file != NULL )
		{
			if( libmsiecf_file_free(
			     &( ( *export_handle )->input_file ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input file.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *export_handle );

		*export_handle = NULL;
	}
	return( result );
}

/* Signals the export handle to abort
 * Returns 1 if successful or -1 on error
 */
int export_handle_signal_abort(
     export_handle_t *export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_signal_abort";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	export_handle->abort = 1;

	if( export_handle->input_file != NULL )
	{
		if( libmsiecf_file_signal_abort(
		     export_handle->input_file,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input file to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the export mode
 * Returns 1 if successful, 0 if unsupported values or -1 on error
 */
int export_handle_set_export_mode(
     export_handle_t *export_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function = "export_handle_set_export_mode";
	size_t string_length  = 0;
	int result            = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( string_length == 3 )
	{
		if( system_string_compare(
		     string,
		     _SYSTEM_STRING( "all" ),
		     3 ) == 0 )
		{
			export_handle->export_mode = EXPORT_MODE_ALL;

			result = 1;
		}
	}
	else if( string_length == 5 )
	{
		if( system_string_compare(
		     string,
		     _SYSTEM_STRING( "items" ),
		     5 ) == 0 )
		{
			export_handle->export_mode = EXPORT_MODE_ITEMS;

			result = 1;
		}
	}
	else if( string_length == 9 )
	{
		if( system_string_compare(
		     string,
		     _SYSTEM_STRING( "recovered" ),
		     9 ) == 0 )
		{
			export_handle->export_mode = EXPORT_MODE_RECOVERED;

			result = 1;
		}
	}
	return( result );
}

/* Sets the ascii codepage
 * Returns 1 if successful or -1 on error
 */
int export_handle_set_ascii_codepage(
     export_handle_t *export_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function  = "export_handle_set_ascii_codepage";
	size_t string_length   = 0;
	uint32_t feature_flags = 0;
	int result             = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_KOI8
	              | LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	string_length = system_string_length(
	                 string );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libclocale_codepage_copy_from_string_wide(
	          &( export_handle->ascii_codepage ),
	          string,
	          string_length,
	          feature_flags,
	          error );
#else
	result = libclocale_codepage_copy_from_string(
	          &( export_handle->ascii_codepage ),
	          string,
	          string_length,
	          feature_flags,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine ASCII codepage.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Opens the export handle
 * Returns 1 if successful or -1 on error
 */
int export_handle_open(
     export_handle_t *export_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "export_handle_open";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( libmsiecf_file_set_ascii_codepage(
	     export_handle->input_file,
	     export_handle->ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set ASCII codepage in input file.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libmsiecf_file_open_wide(
	     export_handle->input_file,
	     filename,
	     LIBMSIECF_OPEN_READ,
	     error ) != 1 )
#else
	if( libmsiecf_file_open(
	     export_handle->input_file,
	     filename,
	     LIBMSIECF_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input file.",
		 function );

		return( -1 );
	}
	if( libmsiecf_file_get_format_version(
	     export_handle->input_file,
	     &( export_handle->major_version ),
	     &( export_handle->minor_version ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve format version.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the export handle
 * Returns the 0 if succesful or -1 on error
 */
int export_handle_close(
     export_handle_t *export_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_close";

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( libmsiecf_file_close(
	     export_handle->input_file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input file.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Exports the leak item
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_item_leak(
     export_handle_t *export_handle,
     libmsiecf_item_t *item,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	char cache_directory_name[ 9 ];

	system_character_t *filename  = NULL;
	static char *function         = "export_handle_export_item_leak";
	size_t filename_size          = 0;
	uint8_t cache_directory_index = 0;
	int result                    = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak item.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmsiecf_leak_get_utf16_filename_size(
	          item,
	          &filename_size,
	          error );
#else
	result = libmsiecf_leak_get_utf8_filename_size(
	          item,
	          &filename_size,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve filename size.",
		 function );

		goto on_error;
	}
	if( ( result != 0 )
	 && ( filename_size > 0 ) )
	{
		filename = system_string_allocate(
		            filename_size );

		if( filename == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create filename.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libmsiecf_leak_get_utf16_filename(
		          item,
		          (uint16_t *) filename,
		          filename_size,
		          error );
#else
		result = libmsiecf_leak_get_utf8_filename(
		          item,
		          (uint8_t *) filename,
		          filename_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve filename.",
			 function );

			goto on_error;
		}
		fprintf(
		 export_handle->notify_stream,
		 "Filename\t\t: %" PRIs_SYSTEM "\n",
		 filename );

		memory_free(
		 filename );

		filename = NULL;
	}
	if( libmsiecf_leak_get_cache_directory_index(
	     item,
	     &cache_directory_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve cache directory index.",
		 function );

		goto on_error;
	}
	fprintf(
	 export_handle->notify_stream,
	 "Cache directory index\t: %" PRIi8 " (0x%02" PRIx8 ")",
	 (int8_t) cache_directory_index,
	 cache_directory_index );

	if( ( cache_directory_index != (uint8_t) -1 )
	 && ( cache_directory_index != (uint8_t) -2 ) )
	{
		if( libmsiecf_file_get_cache_directory_name(
		     export_handle->input_file,
		     cache_directory_index,
		     cache_directory_name,
		     9,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache directory name.",
			 function );

			goto on_error;
		}
		/* Assumed that the directory name contains only basic ASCII characters
		 */
		fprintf(
		 export_handle->notify_stream,
		 " (%s)",
		 cache_directory_name );
	}
	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( filename != NULL )
	{
		memory_free(
		 filename );
	}
	return( -1 );
}

/* Exports the redirected item
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_item_redirected(
     export_handle_t *export_handle,
     libmsiecf_item_t *item,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	system_character_t *location = NULL;
	static char *function        = "export_handle_export_item_redirected";
	size_t location_size         = 0;
	int result                   = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected item.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmsiecf_redirected_get_utf16_location_size(
	          item,
	          &location_size,
	          error );
#else
	result = libmsiecf_redirected_get_utf8_location_size(
	          item,
	          &location_size,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve location size.",
		 function );

		goto on_error;
	}
	if( ( result != 0 )
	 && ( location_size > 0 ) )
	{
		location = system_string_allocate(
		            location_size );

		if( location == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create location.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libmsiecf_redirected_get_utf16_location(
		          item,
		          (uint16_t *) location,
		          location_size,
		          error );
#else
		result = libmsiecf_redirected_get_utf8_location(
		          item,
		          (uint8_t *) location,
		          location_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve location.",
			 function );

			goto on_error;
		}
		fprintf(
		 export_handle->notify_stream,
		 "Location\t\t: %" PRIs_SYSTEM "\n",
		 location );

		memory_free(
		 location );

		location = NULL;
	}

	return( 1 );

on_error:
	if( location != NULL )
	{
		memory_free(
		 location );
	}
	return( -1 );
}

/* Exports the url item
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_item_url(
     export_handle_t *export_handle,
     libmsiecf_item_t *item,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	char cache_directory_name[ 9 ];
	system_character_t date_time_string[ 48 ];

	libfdatetime_fat_date_time_t *fat_date_time = NULL;
	libfdatetime_filetime_t *filetime           = NULL;
	system_character_t *filename                = NULL;
	system_character_t *location                = NULL;
	static char *function                       = "export_handle_export_item_url";
	size_t filename_size                        = 0;
	size_t location_size                        = 0;
	uint64_t value_64bit                        = 0;
	uint32_t value_32bit                        = 0;
	uint8_t cache_directory_index               = 0;
	int result                                  = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid url item.",
		 function );

		return( -1 );
	}
	if( libfdatetime_fat_date_time_initialize(
	     &fat_date_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create FAT date time.",
		 function );

		goto on_error;
	}
	if( libfdatetime_filetime_initialize(
	     &filetime,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create filetime.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmsiecf_url_get_utf16_location_size(
	          item,
	          &location_size,
	          error );
#else
	result = libmsiecf_url_get_utf8_location_size(
	          item,
	          &location_size,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve location size.",
		 function );

		goto on_error;
	}
	if( ( result != 0 )
	 && ( location_size > 0 ) )
	{
		location = system_string_allocate(
		            location_size );

		if( location == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create location.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libmsiecf_url_get_utf16_location(
		          item,
		          (uint16_t *) location,
		          location_size,
		          error );
#else
		result = libmsiecf_url_get_utf8_location(
		          item,
		          (uint8_t *) location,
		          location_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve location.",
			 function );

			goto on_error;
		}
		fprintf(
		 export_handle->notify_stream,
		 "Location\t\t: %" PRIs_SYSTEM "\n",
		 location );

		memory_free(
		 location );

		location = NULL;
	}
	if( libmsiecf_url_get_primary_time(
	     item,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve primary time.",
		 function );

		goto on_error;
	}
	if( libfdatetime_filetime_copy_from_64bit(
	     filetime,
	     value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filetime from 64-bit value.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfdatetime_filetime_copy_to_utf16_string(
		  filetime,
		  (uint16_t *) date_time_string,
		  48,
		  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		  error );
#else
	result = libfdatetime_filetime_copy_to_utf8_string(
		  filetime,
		  (uint8_t *) date_time_string,
		  48,
		  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filetime to string.",
		 function );

		goto on_error;
	}
	fprintf(
	 export_handle->notify_stream,
	 "Primary time\t\t: %" PRIs_SYSTEM "\n",
	 date_time_string );

	if( libmsiecf_url_get_secondary_time(
	     item,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve secondary time.",
		 function );

		goto on_error;
	}
	if( value_64bit != 0 )
	{
		if( libfdatetime_filetime_copy_from_64bit(
		     filetime,
		     value_64bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime from 64-bit value.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 export_handle->notify_stream,
		 "Secondary time\t\t: %" PRIs_SYSTEM "\n",
		 date_time_string );
	}
	if( libmsiecf_url_get_expiration_time(
	     item,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve expiration time.",
		 function );

		goto on_error;
	}
	if( value_64bit != 0 )
	{
		if( ( export_handle->major_version == 4 )
		 && ( export_handle->minor_version == 7 ) )
		{
			if( value_64bit == 0x7fffffffffffffffULL )
			{
				date_time_string[ 0 ] = (system_character_t) 'N';
				date_time_string[ 1 ] = (system_character_t) 'e';
				date_time_string[ 2 ] = (system_character_t) 'v';
				date_time_string[ 3 ] = (system_character_t) 'e';
				date_time_string[ 4 ] = (system_character_t) 'r';
				date_time_string[ 5 ] = 0;
			}
			else
			{
				if( libfdatetime_filetime_copy_from_64bit(
				     filetime,
				     value_64bit,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy filetime from 64-bit value.",
					 function );

					goto on_error;
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfdatetime_filetime_copy_to_utf16_string(
					  filetime,
					  (uint16_t *) date_time_string,
					  48,
					  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
					  error );
#else
				result = libfdatetime_filetime_copy_to_utf8_string(
					  filetime,
					  (uint8_t *) date_time_string,
					  48,
					  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy filetime to string.",
					 function );

					goto on_error;
				}
			}
		}
		else if( ( export_handle->major_version == 5 )
		      && ( export_handle->minor_version == 2 ) )
		{
			if( value_64bit == 0xffffffffUL )
			{
				date_time_string[ 0 ] = (system_character_t) 'N';
				date_time_string[ 1 ] = (system_character_t) 'e';
				date_time_string[ 2 ] = (system_character_t) 'v';
				date_time_string[ 3 ] = (system_character_t) 'e';
				date_time_string[ 4 ] = (system_character_t) 'r';
				date_time_string[ 5 ] = 0;
			}
			else
			{
				if( libfdatetime_fat_date_time_copy_from_32bit(
				     fat_date_time,
				     (uint32_t) value_64bit,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy FAT date time from 32-bit value.",
					 function );

					goto on_error;
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfdatetime_fat_date_time_copy_to_utf16_string(
					  fat_date_time,
					  (uint16_t *) date_time_string,
					  48,
					  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
					  error );
#else
				result = libfdatetime_fat_date_time_copy_to_utf8_string(
					  fat_date_time,
					  (uint8_t *) date_time_string,
					  48,
					  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy FAT date time to string.",
					 function );

					goto on_error;
				}
			}
		}
		fprintf(
		 export_handle->notify_stream,
		 "Expiration time\t\t: %" PRIs_SYSTEM "\n",
		 date_time_string );
	}
	if( libmsiecf_url_get_last_checked_time(
	     item,
	     &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve last checked time.",
		 function );

		goto on_error;
	}
	if( value_32bit != 0 )
	{
		if( libfdatetime_fat_date_time_copy_from_32bit(
		     fat_date_time,
		     value_32bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy FAT date time from 32-bit value.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_fat_date_time_copy_to_utf16_string(
			  fat_date_time,
			  (uint16_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#else
		result = libfdatetime_fat_date_time_copy_to_utf8_string(
			  fat_date_time,
			  (uint8_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy FAT date time to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 export_handle->notify_stream,
		 "Last checked time\t: %" PRIs_SYSTEM "\n",
		 date_time_string );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libmsiecf_url_get_utf16_filename_size(
	          item,
	          &filename_size,
	          error );
#else
	result = libmsiecf_url_get_utf8_filename_size(
	          item,
	          &filename_size,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve filename size.",
		 function );

		goto on_error;
	}
	if( ( result != 0 )
	 && ( filename_size > 0 ) )
	{
		filename = system_string_allocate(
		            filename_size );

		if( filename == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create filename.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libmsiecf_url_get_utf16_filename(
		          item,
		          (uint16_t *) filename,
		          filename_size,
		          error );
#else
		result = libmsiecf_url_get_utf8_filename(
		          item,
		          (uint8_t *) filename,
		          filename_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve filename.",
			 function );

			goto on_error;
		}
		fprintf(
		 export_handle->notify_stream,
		 "Filename\t\t: %" PRIs_SYSTEM "\n",
		 filename );

		memory_free(
		 filename );

		filename = NULL;
	}
	if( libmsiecf_url_get_cache_directory_index(
	     item,
	     &cache_directory_index,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve cache directory index.",
		 function );

		goto on_error;
	}
	fprintf(
	 export_handle->notify_stream,
	 "Cache directory index\t: %" PRIi8 " (0x%02" PRIx8 ")",
	 (int8_t) cache_directory_index,
	 cache_directory_index );

	if( ( cache_directory_index != (uint8_t) -1 )
	 && ( cache_directory_index != (uint8_t) -2 ) )
	{
		if( libmsiecf_file_get_cache_directory_name(
		     export_handle->input_file,
		     cache_directory_index,
		     cache_directory_name,
		     9,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve cache directory name.",
			 function );

			goto on_error;
		}
		fprintf(
		 export_handle->notify_stream,
		 "(%s)",
		 cache_directory_name );
	}
	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	if( libfdatetime_fat_date_time_free(
	     &fat_date_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free FAT date time.",
		 function );

		goto on_error;
	}
	if( libfdatetime_filetime_free(
	     &filetime,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free filetime.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( filename != NULL )
	{
		memory_free(
		 filename );
	}
	if( fat_date_time != NULL )
	{
		libfdatetime_fat_date_time_free(
		 &fat_date_time,
		 NULL );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	if( location != NULL )
	{
		memory_free(
		 location );
	}
	return( -1 );
}

/* Exports the item
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_item(
     export_handle_t *export_handle,
     libmsiecf_item_t *item,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_export_item";
	off64_t item_offset   = 0;
	size64_t item_size    = 0;
	uint8_t item_flags    = 0;
	uint8_t item_type     = 0;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( libmsiecf_item_get_type(
	     item,
	     &item_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item type.",
		 function );
		
		goto on_error;
	}
	fprintf(
	 export_handle->notify_stream,
	 "Record type\t\t: " );

	switch( item_type )
	{
		case LIBMSIECF_ITEM_TYPE_LEAK:
			fprintf(
			 export_handle->notify_stream,
			 "LEAK" );

			break;

		case LIBMSIECF_ITEM_TYPE_REDIRECTED:
			fprintf(
			 export_handle->notify_stream,
			 "REDR" );

			break;

		case LIBMSIECF_ITEM_TYPE_URL:
			fprintf(
			 export_handle->notify_stream,
			 "URL" );

			break;
	}
	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	if( libmsiecf_item_get_flags(
	     item,
	     &item_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item flags.",
		 function );

		goto on_error;
	}
	if( libmsiecf_item_get_offset_range(
	     item,
	     &item_offset,
	     &item_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offset range.",
		 function );
		
		goto on_error;
	}
	fprintf(
	 export_handle->notify_stream,
	 "Offset range\t\t: %" PRIi64 " - %" PRIi64 " (%" PRIu64 ")",
	 item_offset,
	 item_offset + item_size,
	 item_size );

	if( ( item_flags & LIBMSIECF_ITEM_FLAG_PARTIAL ) != 0 )
	{
		fprintf(
		 export_handle->notify_stream,
		 " (partial)" );
	}
	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	switch( item_type )
	{
		case LIBMSIECF_ITEM_TYPE_LEAK:
			if( export_handle_export_item_leak(
			     export_handle,
			     item,
			     log_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GENERIC,
				 "%s: unable to export leak item.",
				 function );

				return( -1 );
			}
			break;

		case LIBMSIECF_ITEM_TYPE_REDIRECTED:
			if( export_handle_export_item_redirected(
			     export_handle,
			     item,
			     log_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GENERIC,
				 "%s: unable to export redirected item.",
				 function );

				return( -1 );
			}
			break;

		case LIBMSIECF_ITEM_TYPE_URL:
			if( export_handle_export_item_url(
			     export_handle,
			     item,
			     log_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GENERIC,
				 "%s: unable to export url item.",
				 function );

				return( -1 );
			}
			break;
	}
	fprintf(
	 export_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( item != NULL )
	{
		libmsiecf_item_free(
		 &item,
		 NULL );
	}
	return( -1 );
}

/* Exports the items
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_items(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	libmsiecf_item_t *item = NULL;
	static char *function  = "export_handle_export_items";
	int item_iterator      = 0;
	int number_of_items    = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( libmsiecf_file_get_number_of_items(
	     export_handle->input_file,
	     &number_of_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of items.",
		 function );

		return( -1 );
	}
	fprintf(
	 export_handle->notify_stream,
	 "Number of items: %d.\n\n",
	 number_of_items );

	for( item_iterator = 0;
	     item_iterator < number_of_items;
	     item_iterator++ )
	{
		if( libmsiecf_file_get_item_by_index(
		     export_handle->input_file,
		     item_iterator,
		     &item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve item %d.",
			 function,
			 item_iterator );

			return( -1 );
		}
		if( export_handle_export_item(
		     export_handle,
		     item,
		     log_handle,
		     error ) != 1 )
		{
			fprintf(
			 export_handle->notify_stream,
			 "Unable to export item %d out of %d.\n",
			 item_iterator,
			 number_of_items );

			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to export item %d.",
			 function,
			 item_iterator );

			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libcnotify_print_error_backtrace(
				 *error );
			}
			libcerror_error_free(
			 error );
		}
		if( libmsiecf_item_free(
		     &item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free item.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Exports the recovered items
 * Returns 1 if successful or -1 on error
 */
int export_handle_export_recovered_items(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	libmsiecf_item_t *recovered_item = NULL;
	static char *function            = "export_handle_export_recovered_items";
	int number_of_recovered_items    = 0;
	int recovered_item_iterator      = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( libmsiecf_file_get_number_of_recovered_items(
	     export_handle->input_file,
	     &number_of_recovered_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of recovered items.",
		 function );

		return( -1 );
	}
	fprintf(
	 export_handle->notify_stream,
	 "Number of recovered items: %d.\n\n",
	 number_of_recovered_items );

	for( recovered_item_iterator = 0;
	     recovered_item_iterator < number_of_recovered_items;
	     recovered_item_iterator++ )
	{
		if( libmsiecf_file_get_recovered_item_by_index(
		     export_handle->input_file,
		     recovered_item_iterator,
		     &recovered_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve recovered item %d.",
			 function,
			 recovered_item_iterator );

			return( -1 );
		}
		if( export_handle_export_item(
		     export_handle,
		     recovered_item,
		     log_handle,
		     error ) != 1 )
		{
			fprintf(
			 export_handle->notify_stream,
			 "Unable to export recovered item %d out of %d.\n",
			 recovered_item_iterator,
			 number_of_recovered_items );

			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to export recovered item %d.",
			 function,
			 recovered_item_iterator );

			if( ( error != NULL )
			 && ( *error != NULL ) )
			{
				libcnotify_print_error_backtrace(
				 *error );
			}
			libcerror_error_free(
			 error );
		}
		if( libmsiecf_item_free(
		     &recovered_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free recovered item.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Exports the items from the file
 * Returns the 1 if succesful, 0 if no items are available or -1 on error
 */
int export_handle_export_file(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	static char *function = "export_handle_export_file";
	int result            = 0;

	if( export_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export handle.",
		 function );

		return( -1 );
	}
	if( export_handle->export_mode != EXPORT_MODE_RECOVERED )
	{
		fprintf(
		 export_handle->notify_stream,
		 "Exporting items.\n" );

		result = export_handle_export_items(
			  export_handle,
			  log_handle,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to export items.",
			 function );

			return( -1 );
		}
	}
	if( export_handle->export_mode != EXPORT_MODE_ITEMS )
	{
		fprintf(
		 export_handle->notify_stream,
		 "Exporting recovered items.\n" );

		result = export_handle_export_recovered_items(
			  export_handle,
			  log_handle,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to export recovered items.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

