/*
 * Cache directory table functions
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

#include "libmsiecf_cache_directory_table.h"
#include "libmsiecf_directory_descriptor.h"
#include "libmsiecf_io_handle.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"

#include "msiecf_cache_directory_table.h"

/* Creates cache directory table
 * Make sure the value cache_directory_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_cache_directory_table_initialize(
     libmsiecf_cache_directory_table_t **cache_directory_table,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_cache_directory_table_initialize";

	if( cache_directory_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache directory table.",
		 function );

		return( -1 );
	}
	if( *cache_directory_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid cache directory table value already set.",
		 function );

		return( -1 );
	}
	*cache_directory_table = memory_allocate_structure(
	                          libmsiecf_cache_directory_table_t );

	if( *cache_directory_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create cache directory table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *cache_directory_table,
	     0,
	     sizeof( libmsiecf_cache_directory_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear cache directory table.",
		 function );

		memory_free(
		 *cache_directory_table );

		*cache_directory_table = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *cache_directory_table )->directory_descriptor_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create directory descriptor array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *cache_directory_table != NULL )
	{
		memory_free(
		 *cache_directory_table );

		*cache_directory_table = NULL;
	}
	return( -1 );
}

/* Frees cache directory table
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_cache_directory_table_free(
     libmsiecf_cache_directory_table_t **cache_directory_table,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_cache_directory_table_free";
	int result            = 1;

	if( cache_directory_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache directory table.",
		 function );

		return( -1 );
	}
	if( *cache_directory_table != NULL )
	{
		if( libcdata_array_free(
		     &( ( *cache_directory_table )->directory_descriptor_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libmsiecf_directory_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free directory descriptor array.",
			 function );

			result = -1;
		}
		memory_free(
		 *cache_directory_table );

		*cache_directory_table = NULL;
	}
	return( result );
}

/* Reads the cache directory table data
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_cache_directory_table_read_data(
     libmsiecf_cache_directory_table_t *cache_directory_table,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libmsiecf_directory_descriptor_t *directory_descriptor = NULL;
	static char *function                                  = "libmsiecf_cache_directory_table_read_data";
	size_t data_offset                                     = 0;
	uint32_t cache_directory_index                         = 0;
	uint32_t number_of_cache_directories                   = 0;
	int entry_index                                        = 0;

	if( cache_directory_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache directory table.",
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
	if( data_size < sizeof( msiecf_cache_directory_table_header_t ) )
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
		 "%s: cache directory table:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (msiecf_cache_directory_table_header_t *) data )->number_of_cache_directories,
	 number_of_cache_directories );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: number of cache directories\t: %" PRIu32 "\n",
		 function,
		 number_of_cache_directories );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( (size_t) number_of_cache_directories > ( ( data_size - sizeof( msiecf_cache_directory_table_header_t ) ) / sizeof( msiecf_cache_directory_entry_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of cache directories value out of bounds.",
		 function );

		goto on_error;
	}
	data_offset = sizeof( msiecf_cache_directory_table_header_t );

	for( cache_directory_index = 0;
	     cache_directory_index < number_of_cache_directories;
	     cache_directory_index++ )
	{
		if( libmsiecf_directory_descriptor_initialize(
		     &directory_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create directory descriptor: %" PRIu32 ".",
			 function,
			 cache_directory_index );

			goto on_error;
		}
		if( libmsiecf_directory_descriptor_read_data(
		     directory_descriptor,
		     &( data[ data_offset ] ),
		     sizeof( msiecf_cache_directory_entry_t ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read directory descriptor: %" PRIu32 ".",
			 function,
			 cache_directory_index );

			goto on_error;
		}
		data_offset += sizeof( msiecf_cache_directory_entry_t );

		if( libcdata_array_append_entry(
		     cache_directory_table->directory_descriptor_array,
		     &entry_index,
		     (intptr_t *) directory_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append directory descriptor: %" PRIu32 " to array.",
			 function,
			 cache_directory_index );

			goto on_error;
		}
		directory_descriptor = NULL;
	}
	return( 1 );

on_error:
	if( directory_descriptor != NULL )
	{
		libmsiecf_directory_descriptor_free(
		 &directory_descriptor,
		 NULL );
	}
	return( -1 );
}

/* Reads the cache directory table
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_cache_directory_table_read_file_io_handle(
     libmsiecf_cache_directory_table_t *cache_directory_table,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t header_data[ sizeof( msiecf_cache_directory_table_header_t ) ];

	uint8_t *table_data                  = NULL;
	static char *function                = "libmsiecf_cache_directory_table_read_file_io_handle";
	size_t table_data_size               = 0;
	ssize_t read_count                   = 0;
	uint32_t number_of_cache_directories = 0;

	if( cache_directory_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache directory table.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading cache directory table at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek cache directory table offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              header_data,
	              sizeof( msiecf_cache_directory_table_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( msiecf_cache_directory_table_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read cache directory table header data.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 header_data,
	 number_of_cache_directories );

	if( (size_t) number_of_cache_directories > ( ( MEMORY_MAXIMUM_ALLOCATION_SIZE - sizeof( msiecf_cache_directory_table_header_t ) ) / sizeof( msiecf_cache_directory_entry_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of cache directories value out of bounds.",
		 function );

		goto on_error;
	}
	table_data_size = sizeof( msiecf_cache_directory_table_header_t ) +
	                  ( (size_t) number_of_cache_directories * sizeof( msiecf_cache_directory_entry_t ) );

	if( ( table_data_size == 0 )
	 || ( table_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid table data size value exceeds out of bounds.",
		 function );

		goto on_error;
	}
	table_data = (uint8_t *) memory_allocate(
	                          table_data_size );

	if( table_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create cache directories table data.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     table_data,
	     header_data,
	     sizeof( msiecf_cache_directory_table_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy cache directories header data to table data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              &( table_data[ sizeof( msiecf_cache_directory_table_header_t ) ] ),
	              table_data_size - sizeof( msiecf_cache_directory_table_header_t ),
	              error );

	if( read_count != (ssize_t) ( table_data_size - sizeof( msiecf_cache_directory_table_header_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read cache directory table data.",
		 function );

		goto on_error;
	}
	if( libmsiecf_cache_directory_table_read_data(
	     cache_directory_table,
	     table_data,
	     table_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read cache directory table.",
		 function );

		goto on_error;
	}
	memory_free(
	 table_data );

	return( 1 );

on_error:
	if( table_data != NULL )
	{
		memory_free(
		 table_data );
	}
	return( -1 );
}

/* Retrieves the number of cache directories
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_cache_directory_table_get_number_of_cache_directories(
     libmsiecf_cache_directory_table_t *cache_directory_table,
     int *number_of_cache_directories,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_cache_directory_table_get_number_of_cache_directories";

	if( cache_directory_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache directory table.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     cache_directory_table->directory_descriptor_array,
	     number_of_cache_directories,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from directory descriptor array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the extended ASCII encoded name of a certain cache directory
 * The size should include the end of string character
 * The cache directory name consists of 8 characters + end of string character
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_cache_directory_table_get_directory_name_by_index(
     libmsiecf_cache_directory_table_t *cache_directory_table,
     int cache_directory_index,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	libmsiecf_directory_descriptor_t *directory_descriptor = NULL;
	static char *function                                  = "libmsiecf_cache_directory_table_get_directory_name_by_index";

	if( cache_directory_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid cache directory table.",
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
	if( string_size < 9 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid string size value too small.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     cache_directory_table->directory_descriptor_array,
	     cache_directory_index,
	     (intptr_t **) &directory_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve directory descriptor: %d.",
		 function,
		 cache_directory_index );

		return( -1 );
	}
	if( directory_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing directory descriptor: %d.",
		 function,
		 cache_directory_index );

		return( -1 );
	}
	/* Assumed that the directory name contains only basic ASCII characters
	 */
	if( memory_copy(
	     string,
	     directory_descriptor->name,
	     9 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set cache directory name.",
		 function );

		return( -1 );
	}
	return( 1 );
}

