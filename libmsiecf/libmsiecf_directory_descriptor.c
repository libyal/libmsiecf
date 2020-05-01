/*
 * Cache directory descriptor functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libmsiecf_directory_descriptor.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"

#include "msiecf_cache_directory_table.h"

/* Creates a directory descriptor
 * Make sure the value directory_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_directory_descriptor_initialize(
     libmsiecf_directory_descriptor_t **directory_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_directory_descriptor_initialize";

	if( directory_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory descriptor.",
		 function );

		return( -1 );
	}
	if( *directory_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid directory descriptor value already set.",
		 function );

		return( -1 );
	}
	*directory_descriptor = memory_allocate_structure(
	                         libmsiecf_directory_descriptor_t );

	if( *directory_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create directory descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *directory_descriptor,
	     0,
	     sizeof( libmsiecf_directory_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear directory descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *directory_descriptor != NULL )
	{
		memory_free(
		 *directory_descriptor );

		*directory_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a directory descriptor
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_directory_descriptor_free(
     libmsiecf_directory_descriptor_t **directory_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_directory_descriptor_free";

	if( directory_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory descriptor.",
		 function );

		return( -1 );
	}
	if( *directory_descriptor != NULL )
	{
		memory_free(
		 *directory_descriptor );

		*directory_descriptor = NULL;
	}
	return( 1 );
}

/* Reads the directory descriptor data
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_directory_descriptor_read_data(
     libmsiecf_directory_descriptor_t *directory_descriptor,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_directory_descriptor_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( directory_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid directory descriptor.",
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
	if( data_size < sizeof( msiecf_cache_directory_entry_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: cache directory entry:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( msiecf_cache_directory_entry_t ),
		 0 );
	}
#endif
	if( memory_copy(
	     directory_descriptor->name,
	     ( (msiecf_cache_directory_entry_t * ) data )->name,
	     8 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name.",
		 function );

		return( -1 );
	}
	directory_descriptor->name[ 8 ] = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_cache_directory_entry_t * ) data )->number_of_cached_files,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of cached files\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: name\t\t\t\t: %s\n",
		 function,
		 directory_descriptor->name );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

