/*
 * Leak item functions
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
#include <types.h>

#include "libmsiecf_definitions.h"
#include "libmsiecf_item.h"
#include "libmsiecf_leak.h"
#include "libmsiecf_leak_values.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libfvalue.h"

/* Retrieves the cached file size
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_leak_get_cached_file_size(
     libmsiecf_item_t *leak,
     uint64_t *cached_file_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_leak_get_cached_file_size";

	if( leak == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) leak;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_LEAK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported item type: %" PRIu8 ".",
		 function,
		 internal_item->item_descriptor->type );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item values.",
		 function );

		return( -1 );
	}
	if( cached_file_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cached file size.",
		 function );

		return( -1 );
	}
	*cached_file_size = (uint64_t) ( (libmsiecf_leak_values_t *) internal_item->value )->cached_file_size;

	return( 1 );
}

/* Retrieves the cache directory index
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_leak_get_cache_directory_index(
     libmsiecf_item_t *leak,
     uint8_t *cache_directory_index,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_leak_get_cache_directory_index";

	if( leak == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) leak;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_LEAK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported item type: %" PRIu8 ".",
		 function,
		 internal_item->item_descriptor->type );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item values.",
		 function );

		return( -1 );
	}
	if( cache_directory_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache directory index.",
		 function );

		return( -1 );
	}
	*cache_directory_index = ( (libmsiecf_leak_values_t *) internal_item->value )->cache_directory_index;

	return( 1 );
}

/* Retrieves the size of the filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
int libmsiecf_leak_get_filename_size(
     libmsiecf_item_t *leak,
     size_t *string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_leak_get_filename_size";

	if( leak == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) leak;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_LEAK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported item type: %" PRIu8 ".",
		 function,
		 internal_item->item_descriptor->type );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item values.",
		 function );

		return( -1 );
	}
	if( ( (libmsiecf_leak_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_data_size(
	     ( (libmsiecf_leak_values_t *) internal_item->value )->filename,
	     string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve filename data size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
int libmsiecf_leak_get_filename(
     libmsiecf_item_t *leak,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_leak_get_filename";

	if( leak == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) leak;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_LEAK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported item type: %" PRIu8 ".",
		 function,
		 internal_item->item_descriptor->type );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item values.",
		 function );

		return( -1 );
	}
	if( ( (libmsiecf_leak_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_data(
	     ( (libmsiecf_leak_values_t *) internal_item->value )->filename,
	     (uint8_t *) string,
	     string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filename data to string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
int libmsiecf_leak_get_utf8_filename_size(
     libmsiecf_item_t *leak,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_leak_get_utf8_filename_size";

	if( leak == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) leak;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_LEAK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported item type: %" PRIu8 ".",
		 function,
		 internal_item->item_descriptor->type );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item values.",
		 function );

		return( -1 );
	}
	if( ( (libmsiecf_leak_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_utf8_string_size(
	     ( (libmsiecf_leak_values_t *) internal_item->value )->filename,
	     0,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 filename string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
int libmsiecf_leak_get_utf8_filename(
     libmsiecf_item_t *leak,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_leak_get_utf8_filename";

	if( leak == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) leak;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_LEAK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported item type: %" PRIu8 ".",
		 function,
		 internal_item->item_descriptor->type );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item values.",
		 function );

		return( -1 );
	}
	if( ( (libmsiecf_leak_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_to_utf8_string(
	     ( (libmsiecf_leak_values_t *) internal_item->value )->filename,
	     0,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filename to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
int libmsiecf_leak_get_utf16_filename_size(
     libmsiecf_item_t *leak,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_leak_get_utf16_filename_size";

	if( leak == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) leak;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_LEAK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported item type: %" PRIu8 ".",
		 function,
		 internal_item->item_descriptor->type );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item values.",
		 function );

		return( -1 );
	}
	if( ( (libmsiecf_leak_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_utf16_string_size(
	     ( (libmsiecf_leak_values_t *) internal_item->value )->filename,
	     0,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 filename string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
int libmsiecf_leak_get_utf16_filename(
     libmsiecf_item_t *leak,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_leak_get_utf16_filename";

	if( leak == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) leak;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_LEAK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported item type: %" PRIu8 ".",
		 function,
		 internal_item->item_descriptor->type );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item values.",
		 function );

		return( -1 );
	}
	if( ( (libmsiecf_leak_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_to_utf16_string(
	     ( (libmsiecf_leak_values_t *) internal_item->value )->filename,
	     0,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy filename to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

