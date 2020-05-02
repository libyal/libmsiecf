/*
 * Leak values functions
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
#include <system_string.h>
#include <types.h>

#include "libmsiecf_debug.h"
#include "libmsiecf_definitions.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"
#include "libmsiecf_libfdatetime.h"
#include "libmsiecf_libfvalue.h"
#include "libmsiecf_leak_values.h"

#include "msiecf_leak_record.h"

/* Creates leak values
 * Make sure the value leak_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_leak_values_initialize(
     libmsiecf_leak_values_t **leak_values,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_leak_values_initialize";

	if( leak_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak values.",
		 function );

		return( -1 );
	}
	if( *leak_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid leak values value already set.",
		 function );

		return( -1 );
	}
	*leak_values = memory_allocate_structure(
	                libmsiecf_leak_values_t );

	if( *leak_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create leak values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *leak_values,
	     0,
	     sizeof( libmsiecf_leak_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear leak values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *leak_values != NULL )
	{
		memory_free(
		 *leak_values );

		*leak_values = NULL;
	}
	return( -1 );
}

/* Frees leak values
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_leak_values_free(
     libmsiecf_leak_values_t **leak_values,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_leak_values_free";
	int result            = 1;

	if( leak_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak values.",
		 function );

		return( -1 );
	}
	if( *leak_values != NULL )
	{
		if( ( *leak_values )->filename != NULL )
		{
			if( libfvalue_value_free(
			     &( ( *leak_values )->filename ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free filename value.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *leak_values );

		*leak_values = NULL;
	}
	return( result );
}

/* Reads the leak values from a LEAK record
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_leak_values_read_data(
     libmsiecf_leak_values_t *leak_values,
     const uint8_t *data,
     size_t data_size,
     int ascii_codepage,
     uint8_t item_flags,
     libcerror_error_t **error )
{
	static char *function    = "libmsiecf_leak_values_read_data";
	ssize_t value_size       = 0;
	uint32_t filename_offset = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit     = 0;
#endif

	if( leak_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak values.",
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
	if( data_size < sizeof( msiecf_leak_record_header_t ) )
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
		 "%s: LEAK record data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	if( memory_compare(
	     ( (msiecf_leak_record_header_t *) data )->signature,
	     "LEAK",
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (msiecf_leak_record_header_t *) data )->cached_file_size,
	 leak_values->cached_file_size );

	leak_values->cache_directory_index = ( (msiecf_leak_record_header_t *) data )->cache_directory_index;

	byte_stream_copy_to_uint32_little_endian(
	 ( (msiecf_leak_record_header_t *) data )->filename_offset,
	 filename_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 ( (msiecf_leak_record_header_t *) data )->signature[ 0 ],
		 ( (msiecf_leak_record_header_t *) data )->signature[ 1 ],
		 ( (msiecf_leak_record_header_t *) data )->signature[ 2 ],
		 ( (msiecf_leak_record_header_t *) data )->signature[ 3 ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_leak_record_header_t *) data )->number_of_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of blocks\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown1:\n",
		 function );
		libcnotify_print_data(
		 ( (msiecf_leak_record_header_t *) data )->unknown1,
		 24,
		 0 );

		libcnotify_printf(
		 "%s: cached file size\t\t\t: %" PRIu32 " bytes\n",
		 function,
		 leak_values->cached_file_size );

		libcnotify_printf(
		 "%s: unknown3:\n",
		 function );
		libcnotify_print_data(
		 ( (msiecf_leak_record_header_t *) data )->unknown3,
		 8,
		 0 );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_leak_record_header_t *) data )->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown5:\n",
		 function );
		libcnotify_print_data(
		 ( (msiecf_leak_record_header_t *) data )->unknown5,
		 8,
		 0 );

		libcnotify_printf(
		 "%s: cache directory index\t\t\t: %" PRIu8 "\n",
		 function,
		 leak_values->cache_directory_index );

		libcnotify_printf(
		 "%s: unknown7:\n",
		 function );
		libcnotify_print_data(
		 ( (msiecf_leak_record_header_t *) data )->unknown7,
		 3,
		 0 );

		libcnotify_printf(
		 "%s: filename offset\t\t\t: %" PRIu32 "\n",
		 function,
		 filename_offset );

		libcnotify_printf(
		 "%s: unknown9:\n",
		 function );
		libcnotify_print_data(
		 ( (msiecf_leak_record_header_t *) data )->unknown9,
		 24,
		 0 );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_leak_record_header_t *) data )->unknown10,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown10\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		if( libmsiecf_debug_print_fat_date_time_value(
		     function,
		     "unknown time\t\t\t\t",
		     ( (msiecf_leak_record_header_t *) data )->unknown_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print FAT date time value.",
			 function );

			goto on_error;
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( filename_offset > 0 )
	{
		if( filename_offset > data_size )
		{
			if( ( item_flags & LIBMSIECF_ITEM_FLAG_PARTIAL ) == 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: filename offset exceeds size of URL record data.",
				 function );

				goto on_error;
			}
		}
		else
		{
/* TODO remove need for libfvalue */
			if( libfvalue_value_type_initialize(
			     &( leak_values->filename ),
			     LIBFVALUE_VALUE_TYPE_STRING_BYTE_STREAM,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create filename value.",
				 function );

				goto on_error;
			}
			value_size = libfvalue_value_type_set_data_string(
			              leak_values->filename,
			              &( data[ filename_offset ] ),
			              data_size - filename_offset,
			              ascii_codepage,
			              LIBFVALUE_VALUE_DATA_FLAG_MANAGED,
			              error );

			if( value_size == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set data of filename value.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: filename\t\t\t\t: ",
				 function );

				if( libfvalue_value_print(
				     leak_values->filename,
				     0,
				     0,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print filename value.",
					 function );

					goto on_error;
				}
				libcnotify_printf(
				 "\n" );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

			if( ( data[ filename_offset + value_size - 1 ] != 0 )
			 && ( ( item_flags & LIBMSIECF_ITEM_FLAG_PARTIAL ) == 0 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported unterminated filename string.",
				 function );

				goto on_error;
			}
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( leak_values->filename != NULL )
	{
		libfvalue_value_free(
		 &( leak_values->filename ),
		 NULL );
	}
	return( 1 );
}

/* Reads the leak values from a LEAK record
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_leak_values_read_file_io_handle(
     libmsiecf_leak_values_t *leak_values,
     libbfio_handle_t *file_io_handle,
     off64_t leak_record_offset,
     size32_t record_size,
     int ascii_codepage,
     uint8_t item_flags,
     libcerror_error_t **error )
{
	uint8_t *record_data  = NULL;
	static char *function = "libmsiecf_leak_values_read_file_io_handle";
	ssize_t read_count    = 0;

	if( leak_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid leak values.",
		 function );

		return( -1 );
	}
	if( record_size > (size32_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid record size value exceeds maximum allocation size.",
		 function );

		return( -1 );
	}
	if( ( record_size == 0 )
	 || ( ( record_size % 8 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported record size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading LEAK record at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 leak_record_offset,
		 leak_record_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     leak_record_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek LEAK record offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 leak_record_offset,
		 leak_record_offset );

		goto on_error;
	}
	record_data = (uint8_t *) memory_allocate(
	                           sizeof( uint8_t ) * record_size );

	if( record_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create LEAK record data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              record_data,
	              (size_t) record_size,
	              error );

	if( read_count != (ssize_t) record_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read LEAK record data.",
		 function );

		goto on_error;
	}
	if( libmsiecf_leak_values_read_data(
	     leak_values,
	     record_data,
	     (size_t) record_size,
	     ascii_codepage,
	     item_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read LEAK record.",
		 function );

		goto on_error;
	}
	memory_free(
	 record_data );

	return( 1 );

on_error:
	if( record_data != NULL )
	{
		memory_free(
		 record_data );
	}
	return( -1 );
}

