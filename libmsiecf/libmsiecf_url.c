/*
 * URL item functions
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
#include "libmsiecf_url.h"
#include "libmsiecf_url_values.h"

/* Retrieves the url item type
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_type(
     libmsiecf_item_t *url,
     uint8_t *url_item_type,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_type";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( url_item_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL item type.",
		 function );

		return( -1 );
	}
	*url_item_type = ( (libmsiecf_url_values_t *) internal_item->value )->type;

	return( 1 );
}

/* Retrieves the primary time
 * The returned time is a 64-bit version of a FILETIME value
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_primary_time(
     libmsiecf_item_t *url,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_primary_time";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	*filetime = ( (libmsiecf_url_values_t *) internal_item->value )->primary_time;

	return( 1 );
}

/* Retrieves the secondary time
 * The returned time is a 64-bit version of a FILETIME value
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_secondary_time(
     libmsiecf_item_t *url,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_secondary_time";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	*filetime = ( (libmsiecf_url_values_t *) internal_item->value )->secondary_time;

	return( 1 );
}

/* Retrieves the expiration time
 * The returned time is a 64-bit version of a FILETIME value in format version 4.7
 * The returned time is a 32-bit version of a FAT date time value in format version 5.2
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_expiration_time(
     libmsiecf_item_t *url,
     uint64_t *expiration_time,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_expiration_time";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( expiration_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid expiration time.",
		 function );

		return( -1 );
	}
	*expiration_time = ( (libmsiecf_url_values_t *) internal_item->value )->expiration_time;

	return( 1 );
}

/* Retrieves the last checked time
 * The returned time is a 32-bit version of a FAT date and time value
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_last_checked_time(
     libmsiecf_item_t *url,
     uint32_t *fat_date_time,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_last_checked_time";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( fat_date_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid FAT date time.",
		 function );

		return( -1 );
	}
	*fat_date_time = ( (libmsiecf_url_values_t *) internal_item->value )->last_checked_time;

	return( 1 );
}

/* Retrieves the cached file size
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_cached_file_size(
     libmsiecf_item_t *url,
     uint64_t *cached_file_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_cached_file_size";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	*cached_file_size = (uint64_t) ( (libmsiecf_url_values_t *) internal_item->value )->cached_file_size;

	return( 1 );
}

/* Retrieves the cache directory index
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_cache_directory_index(
     libmsiecf_item_t *url,
     uint8_t *cache_directory_index,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_cache_directory_index";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	*cache_directory_index = ( (libmsiecf_url_values_t *) internal_item->value )->cache_directory_index;

	return( 1 );
}

/* Retrieves the number of hits
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_number_of_hits(
     libmsiecf_item_t *url,
     uint32_t *number_of_hits,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_number_of_hits";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( number_of_hits == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of hits.",
		 function );

		return( -1 );
	}
	*number_of_hits = ( (libmsiecf_url_values_t *) internal_item->value )->number_of_hits;

	return( 1 );
}

/* Retrieves the size of the location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
int libmsiecf_url_get_location_size(
     libmsiecf_item_t *url,
     size_t *string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_location_size";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_data_size(
	     ( (libmsiecf_url_values_t *) internal_item->value )->location,
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
int libmsiecf_url_get_location(
     libmsiecf_item_t *url,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_location";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_data(
	     ( (libmsiecf_url_values_t *) internal_item->value )->location,
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
int libmsiecf_url_get_utf8_location_size(
     libmsiecf_item_t *url,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_utf8_location_size";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_utf8_string_size(
	     ( (libmsiecf_url_values_t *) internal_item->value )->location,
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
int libmsiecf_url_get_utf8_location(
     libmsiecf_item_t *url,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_utf8_location";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_to_utf8_string(
	     ( (libmsiecf_url_values_t *) internal_item->value )->location,
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
int libmsiecf_url_get_utf16_location_size(
     libmsiecf_item_t *url,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_utf16_location_size";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_utf16_string_size(
	     ( (libmsiecf_url_values_t *) internal_item->value )->location,
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
int libmsiecf_url_get_utf16_location(
     libmsiecf_item_t *url,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_utf16_location";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->location == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_to_utf16_string(
	     ( (libmsiecf_url_values_t *) internal_item->value )->location,
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

/* Retrieves the size of the filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
int libmsiecf_url_get_filename_size(
     libmsiecf_item_t *url,
     size_t *string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_filename_size";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_data_size(
	     ( (libmsiecf_url_values_t *) internal_item->value )->filename,
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
int libmsiecf_url_get_filename(
     libmsiecf_item_t *url,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_filename";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_data(
	     ( (libmsiecf_url_values_t *) internal_item->value )->filename,
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
int libmsiecf_url_get_utf8_filename_size(
     libmsiecf_item_t *url,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_utf8_filename_size";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_utf8_string_size(
	     ( (libmsiecf_url_values_t *) internal_item->value )->filename,
	     0,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve filename UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
int libmsiecf_url_get_utf8_filename(
     libmsiecf_item_t *url,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_utf8_filename";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_to_utf8_string(
	     ( (libmsiecf_url_values_t *) internal_item->value )->filename,
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
int libmsiecf_url_get_utf16_filename_size(
     libmsiecf_item_t *url,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_utf16_filename_size";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_get_utf16_string_size(
	     ( (libmsiecf_url_values_t *) internal_item->value )->filename,
	     0,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve filename UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
int libmsiecf_url_get_utf16_filename(
     libmsiecf_item_t *url,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_utf16_filename";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->filename == NULL )
	{
		return( 0 );
	}
	if( libfvalue_value_copy_to_utf16_string(
	     ( (libmsiecf_url_values_t *) internal_item->value )->filename,
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

/* Retrieves the size of the data
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_data_size(
     libmsiecf_item_t *url,
     size_t *data_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_data_size";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	if( ( (libmsiecf_url_values_t *) internal_item->value )->data == NULL )
	{
		*data_size = 0;
	}
	else
	{
		*data_size = ( (libmsiecf_url_values_t *) internal_item->value )->data_size;
	}
	return( 1 );
}

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_get_data(
     libmsiecf_item_t *url,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_url_get_data";

	if( url == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) url;

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
	if( internal_item->item_descriptor->type != LIBMSIECF_ITEM_TYPE_URL )
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
	if( ( (libmsiecf_url_values_t *) internal_item->value )->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item values - missing data.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size < ( (libmsiecf_url_values_t *) internal_item->value )->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: data too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     data,
	     ( (libmsiecf_url_values_t *) internal_item->value )->data,
	     ( (libmsiecf_url_values_t *) internal_item->value )->data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

