/*
 * Redirected item functions
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
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libfvalue.h"
#include "libmsiecf_redirected.h"
#include "libmsiecf_redirected_values.h"

/* Retrieves the size of the location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
int libmsiecf_redirected_get_location_size(
     libmsiecf_item_t *redirected,
     size_t *string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_redirected_get_location_size";

	if( redirected == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) redirected;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_REDIRECTED )
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
	if( ( (libmsiecf_redirected_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_data_size(
	     ( (libmsiecf_redirected_values_t *) internal_item->value )->location,
	     string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve location data size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
int libmsiecf_redirected_get_location(
     libmsiecf_item_t *redirected,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_redirected_get_location";

	if( redirected == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) redirected;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_REDIRECTED )
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
	if( ( (libmsiecf_redirected_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_data(
	     ( (libmsiecf_redirected_values_t *) internal_item->value )->location,
	     (uint8_t *) string,
	     string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy location data to string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
int libmsiecf_redirected_get_utf8_location_size(
     libmsiecf_item_t *redirected,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_redirected_get_utf8_location_size";

	if( redirected == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) redirected;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_REDIRECTED )
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
	if( ( (libmsiecf_redirected_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_utf8_string_size(
	     ( (libmsiecf_redirected_values_t *) internal_item->value )->location,
	     0,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve location UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
int libmsiecf_redirected_get_utf8_location(
     libmsiecf_item_t *redirected,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_redirected_get_utf8_location";

	if( redirected == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) redirected;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_REDIRECTED )
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
	if( ( (libmsiecf_redirected_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_to_utf8_string(
	     ( (libmsiecf_redirected_values_t *) internal_item->value )->location,
	     0,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy location to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
int libmsiecf_redirected_get_utf16_location_size(
     libmsiecf_item_t *redirected,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_redirected_get_utf16_location_size";

	if( redirected == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) redirected;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_REDIRECTED )
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
	if( ( (libmsiecf_redirected_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_utf16_string_size(
	     ( (libmsiecf_redirected_values_t *) internal_item->value )->location,
	     0,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve location UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
int libmsiecf_redirected_get_utf16_location(
     libmsiecf_item_t *redirected,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_redirected_get_utf16_location";

	if( redirected == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) redirected;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_REDIRECTED )
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
	if( ( (libmsiecf_redirected_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_to_utf16_string(
	     ( (libmsiecf_redirected_values_t *) internal_item->value )->location,
	     0,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy location to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

