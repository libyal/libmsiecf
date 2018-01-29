/*
 * URL values functions
 *
 * Copyright (C) 2009-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include "libmsiecf_debug.h"
#include "libmsiecf_definitions.h"
#include "libmsiecf_hash.h"
#include "libmsiecf_io_handle.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"
#include "libmsiecf_libfdatetime.h"
#include "libmsiecf_libfole.h"
#include "libmsiecf_libfvalue.h"
#include "libmsiecf_property_type.h"
#include "libmsiecf_url_values.h"

#include "msiecf_url_record.h"

/* Creates URL values
 * Make sure the value url_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_values_initialize(
     libmsiecf_url_values_t **url_values,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_url_values_initialize";

	if( url_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid url values.",
		 function );

		return( -1 );
	}
	if( *url_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid url values value already set.",
		 function );

		return( -1 );
	}
	*url_values = memory_allocate_structure(
	               libmsiecf_url_values_t );

	if( *url_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create URL values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *url_values,
	     0,
	     sizeof( libmsiecf_url_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear URL values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *url_values != NULL )
	{
		memory_free(
		 *url_values );

		*url_values = NULL;
	}
	return( -1 );
}

/* Frees URL values
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_values_free(
     libmsiecf_url_values_t **url_values,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_url_values_free";
	int result            = 1;

	if( url_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL values.",
		 function );

		return( -1 );
	}
	if( *url_values != NULL )
	{
		if( ( *url_values )->location != NULL )
		{
			if( libfvalue_value_free(
			     &( ( *url_values )->location ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free location value.",
				 function );

				result = -1;
			}
		}
		if( ( *url_values )->filename != NULL )
		{
			if( libfvalue_value_free(
			     &( ( *url_values )->filename ),
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
		if( ( *url_values )->data != NULL )
		{
			memory_free(
			 ( *url_values )->data );
		}
		memory_free(
		 *url_values );

		*url_values = NULL;
	}
	return( result );
}

/* Reads the URL values from an URL record
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_url_values_read(
     libmsiecf_url_values_t *url_values,
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t url_record_offset,
     size32_t record_size,
     uint8_t item_flags,
     libcerror_error_t **error )
{
	uint8_t *url_record_data                    = NULL;
	static char *function                       = "libmsiecf_url_values_read";
	ssize_t read_count                          = 0;
	ssize_t value_size                          = 0;
	uint32_t data_offset                        = 0;
	uint32_t data_size                          = 0;
	uint32_t filename_offset                    = 0;
	uint32_t location_offset                    = 0;
	uint32_t cache_entry_flags                  = 0;
	uint32_t unknown_offset                     = 0;
	uint16_t first_year                         = 0;
	uint16_t second_year                        = 0;
	uint8_t first_day_of_month                  = 0;
	uint8_t first_month                         = 0;
	uint8_t number_of_days                      = 0;
	uint8_t second_day_of_month                 = 0;
	uint8_t second_month                        = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t date_time_string[ 32 ];

	libfdatetime_filetime_t *filetime           = NULL;
	libfdatetime_fat_date_time_t *fat_date_time = NULL;
	uint8_t *visited_entry_data                 = NULL;
	size_t string_index                         = 0;
	uint32_t value_32bit                        = 0;
	uint16_t value_16bit                        = 0;
	int result                                  = 0;
	int visited_entry_index                     = 0;
#endif

	if( url_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid URL values.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( record_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid record size value zero or less.",
		 function );

		return( -1 );
	}
#if SIZEOF_SIZE_T <= 4
	if( record_size > (size32_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid record size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
	if( ( record_size % 8 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported URL record size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading URL record at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 url_record_offset,
		 url_record_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     url_record_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek URL record offset: %" PRIi64 ".",
		 function,
		 url_record_offset );

		goto on_error;
	}
	/* Add one block for tainted records
	 */
	if( ( item_flags & LIBMSIECF_ITEM_FLAG_TAINTED ) != 0 )
	{
		record_size += LIBMSIECF_DEFAULT_BLOCK_SIZE;
	}
	url_record_data = (uint8_t *) memory_allocate(
	                               record_size );

	if( url_record_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create URL record data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              url_record_data,
	              record_size,
	              error );

	if( read_count != (ssize_t) record_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read URL record data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: URL record data:\n",
		 function );
		libcnotify_print_data(
		 url_record_data,
		 record_size,
		 0 );
	}
#endif
	if( memory_compare(
	     url_record_data,
	     "URL ",
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
	if( ( io_handle->major_version == 4 )
	 && ( io_handle->minor_version == 7 ) )
	{
		byte_stream_copy_to_uint64_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->secondary_filetime,
		 url_values->secondary_time );

		byte_stream_copy_to_uint64_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->primary_filetime,
		 url_values->primary_time );

		byte_stream_copy_to_uint64_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->expiration_time,
		 url_values->expiration_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->cached_file_size,
		 url_values->cached_file_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown_offset,
		 unknown_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->location_offset,
		 location_offset );

		url_values->cache_directory_index = ( (msiecf_url_record_header_v47_t *) url_record_data )->cache_directory_index;

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->filename_offset,
		 filename_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->data_offset,
		 data_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->data_size,
		 data_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->last_checked_time,
		 url_values->last_checked_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->number_of_hits,
		 url_values->number_of_hits );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->cache_entry_flags,
		 cache_entry_flags );
	}
	else if( ( io_handle->major_version == 5 )
	      && ( io_handle->minor_version == 2 ) )
	{
		byte_stream_copy_to_uint64_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->secondary_filetime,
		 url_values->secondary_time );

		byte_stream_copy_to_uint64_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->primary_filetime,
		 url_values->primary_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->expiration_time,
		 url_values->expiration_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->cached_file_size,
		 url_values->cached_file_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown_offset,
		 unknown_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->location_offset,
		 location_offset );

		url_values->cache_directory_index = ( (msiecf_url_record_header_v52_t *) url_record_data )->cache_directory_index;

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->filename_offset,
		 filename_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->data_offset,
		 data_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->data_size,
		 data_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->last_checked_time,
		 url_values->last_checked_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->number_of_hits,
		 url_values->number_of_hits );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v52_t *) url_record_data )->cache_entry_flags,
		 cache_entry_flags );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
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
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: %c%c%c%c\n",
		 function,
		 url_record_data[ 0 ],
		 url_record_data[ 1 ],
		 url_record_data[ 2 ],
		 url_record_data[ 3 ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_url_record_header_v47_t *) url_record_data )->number_of_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of blocks\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     ( (msiecf_url_record_header_v47_t *) url_record_data )->secondary_filetime,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy filetime from byte stream.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
		          filetime,
		          (uint16_t *) date_time_string,
		          32,
		          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		          error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
		          filetime,
		          (uint8_t *) date_time_string,
		          32,
		          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy filetime to date time string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: secondary time\t\t\t\t: %" PRIs_SYSTEM "\n",
		 function,
		 date_time_string );

		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     ( (msiecf_url_record_header_v47_t *) url_record_data )->primary_filetime,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy filetime from byte stream.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
		          filetime,
		          (uint16_t *) date_time_string,
		          32,
		          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		          error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
		          filetime,
		          (uint8_t *) date_time_string,
		          32,
		          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to copy filetime to date time string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: primary time\t\t\t\t\t: %" PRIs_SYSTEM "\n",
		 function,
		 date_time_string );

		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			if( libfdatetime_filetime_copy_from_byte_stream(
			     filetime,
			     ( (msiecf_url_record_header_v47_t *) url_record_data )->expiration_time,
			     8,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to copy filetime from byte stream.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libfdatetime_filetime_copy_to_utf16_string(
				  filetime,
				  (uint16_t *) date_time_string,
				  32,
				  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
				  error );
#else
			result = libfdatetime_filetime_copy_to_utf8_string(
				  filetime,
				  (uint8_t *) date_time_string,
				  32,
				  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to copy filetime to date time string.",
				 function );

				goto on_error;
			}
		}
		else if( ( io_handle->major_version == 5 )
		      && ( io_handle->minor_version == 2 ) )
		{
			if( libfdatetime_fat_date_time_copy_from_byte_stream(
			     fat_date_time,
			     ( (msiecf_url_record_header_v52_t *) url_record_data )->expiration_time,
			     4,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_CONVERSION,
				 LIBCERROR_CONVERSION_ERROR_GENERIC,
				 "%s: unable to copy FAT date time from byte stream.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libfdatetime_fat_date_time_copy_to_utf16_string(
				  fat_date_time,
				  (uint16_t *) date_time_string,
				  32,
				  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
				  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
				  error );
#else
			result = libfdatetime_fat_date_time_copy_to_utf8_string(
				  fat_date_time,
				  (uint8_t *) date_time_string,
				  32,
				  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_CONVERSION,
				 LIBCERROR_CONVERSION_ERROR_GENERIC,
				 "%s: unable to copy FAT date time to date time string.",
				 function );

				goto on_error;
			}
		}
		libcnotify_printf(
		 "%s: expiration time\t\t\t\t: %" PRIs_SYSTEM "\n",
		 function,
		 date_time_string );

		if( ( io_handle->major_version == 5 )
		 && ( io_handle->minor_version == 2 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown1,
			 value_32bit );

			libcnotify_printf(
			 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: cached file size\t\t\t\t: %" PRIu32 " bytes\n",
		 function,
		 url_values->cached_file_size );

		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown1,
			 value_32bit );

			libcnotify_printf(
			 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown3,
			 value_32bit );
		}
		else if( ( io_handle->major_version == 5 )
		      && ( io_handle->minor_version == 2 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown3,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown4,
			 value_32bit );
		}
		else if( ( io_handle->major_version == 5 )
		      && ( io_handle->minor_version == 2 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown4,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v47_t *) url_record_data )->non_releasable_time_delta,
			 value_32bit );
		}
		else if( ( io_handle->major_version == 5 )
		      && ( io_handle->minor_version == 2 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v52_t *) url_record_data )->non_releasable_time_delta,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: non-releasable time delta\t\t\t: %" PRIu32 " seconds\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown offset\t\t\t\t: %" PRIu32 "\n",
		 function,
		 unknown_offset );

		libcnotify_printf(
		 "%s: location offset\t\t\t\t: %" PRIu32 "\n",
		 function,
		 location_offset );

		libcnotify_printf(
		 "%s: cache directory index\t\t\t: %" PRIu8 "\n",
		 function,
		 url_values->cache_directory_index );

		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			libcnotify_printf(
			 "%s: unknown6\t\t\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
			 function,
			 ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown6[ 0 ],
			 ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown6[ 1 ],
			 ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown6[ 2 ] );
		}
		else if( ( io_handle->major_version == 5 )
		      && ( io_handle->minor_version == 2 ) )
		{
			libcnotify_printf(
			 "%s: unknown6\t\t\t\t\t: 0x%02" PRIx8 " 0x%02" PRIx8 " 0x%02" PRIx8 "\n",
			 function,
			 ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown6[ 0 ],
			 ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown6[ 1 ],
			 ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown6[ 2 ] );
		}
		libcnotify_printf(
		 "%s: filename offset\t\t\t\t: %" PRIu32 "\n",
		 function,
		 filename_offset );

		libcnotify_printf(
		 "%s: cache entry flags\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 cache_entry_flags );
		libmsiecf_debug_print_cache_entry_flags(
		 cache_entry_flags );
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: data offset\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 data_offset );
		libcnotify_printf(
		 "%s: data size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 data_size );

		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown8,
			 value_32bit );
		}
		else if( ( io_handle->major_version == 5 )
		      && ( io_handle->minor_version == 2 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown8,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown8\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			result = libfdatetime_fat_date_time_copy_from_byte_stream(
			          fat_date_time,
			          ( (msiecf_url_record_header_v47_t *) url_record_data )->last_checked_time,
			          4,
			          LIBFDATETIME_ENDIAN_LITTLE,
			          error );
		}
		else if( ( io_handle->major_version == 5 )
		      && ( io_handle->minor_version == 2 ) )
		{
			result = libfdatetime_fat_date_time_copy_from_byte_stream(
			          fat_date_time,
			          ( (msiecf_url_record_header_v52_t *) url_record_data )->last_checked_time,
			          4,
			          LIBFDATETIME_ENDIAN_LITTLE,
			          error );
		}
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to copy FAT date time from byte stream.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_fat_date_time_copy_to_utf16_string(
		          fat_date_time,
		          (uint16_t *) date_time_string,
		          32,
		          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		          error );
#else
		result = libfdatetime_fat_date_time_copy_to_utf8_string(
		          fat_date_time,
		          (uint8_t *) date_time_string,
		          32,
		          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to copy FAT date time to date time string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: last checked time\t\t\t\t: %" PRIs_SYSTEM "\n",
		 function,
		 date_time_string );

		libcnotify_printf(
		 "%s: number of hits\t\t\t\t: %" PRIu32 "\n",
		 function,
		 url_values->number_of_hits );

		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown9,
			 value_32bit );
		}
		else if( ( io_handle->major_version == 5 )
		      && ( io_handle->minor_version == 2 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown9,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown9\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( ( io_handle->major_version == 4 )
		 && ( io_handle->minor_version == 7 ) )
		{
			result = libfdatetime_fat_date_time_copy_from_byte_stream(
			          fat_date_time,
			          ( (msiecf_url_record_header_v47_t *) url_record_data )->unknown_time,
			          4,
			          LIBFDATETIME_ENDIAN_LITTLE,
			          error );
		}
		else if( ( io_handle->major_version == 5 )
		      && ( io_handle->minor_version == 2 ) )
		{
			result = libfdatetime_fat_date_time_copy_from_byte_stream(
			          fat_date_time,
			          ( (msiecf_url_record_header_v52_t *) url_record_data )->unknown_time,
			          4,
			          LIBFDATETIME_ENDIAN_LITTLE,
			          error );
		}
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to copy FAT date time from byte stream.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_fat_date_time_copy_to_utf16_string(
		          fat_date_time,
		          (uint16_t *) date_time_string,
		          32,
		          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		          error );
#else
		result = libfdatetime_fat_date_time_copy_to_utf8_string(
		          fat_date_time,
		          (uint8_t *) date_time_string,
		          32,
		          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_CONVERSION,
			 LIBCERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to create FAT date time string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: unknown time\t\t\t\t\t: %" PRIs_SYSTEM "\n",
		 function,
		 date_time_string );

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
	}
#endif
	if( unknown_offset > 0 )
	{
		if( unknown_offset > record_size )
		{
			if( ( item_flags & LIBMSIECF_ITEM_FLAG_PARTIAL ) == 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: unknown offset exceeds URL record data.",
				 function );

				goto on_error;
			}
			else
			{
				memory_free(
				 url_record_data );

				return( 1 );
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: unknown:\n",
			 function );
			libcnotify_print_data(
			 &( url_record_data[ unknown_offset ] ),
			 8,
			 0 );
		}
#endif
	}
	if( location_offset > 0 )
	{
		if( location_offset > record_size )
		{
			if( ( item_flags & LIBMSIECF_ITEM_FLAG_PARTIAL ) == 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: location offset exceeds size of URL record data.",
				 function );

				return( -1 );
			}
		}
		else
		{
			if( libfvalue_value_type_initialize(
			     &( url_values->location ),
			     LIBFVALUE_VALUE_TYPE_STRING_BYTE_STREAM,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create location value.",
				 function );

				goto on_error;
			}
			value_size = libfvalue_value_type_set_data_string(
			              url_values->location,
			              &( url_record_data[ location_offset ] ),
			              record_size - location_offset,
			              io_handle->ascii_codepage,
			              LIBFVALUE_VALUE_DATA_FLAG_MANAGED,
			              error );

			if( value_size == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set data of location value.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: location\t\t\t\t\t: ",
				 function );

				if( libfvalue_value_print(
				     url_values->location,
				     0,
				     0,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print location value.",
					 function );

					goto on_error;
				}
				libcnotify_printf(
				 "\n" );

				if( libmsiecf_hash_calculate(
				     &value_32bit,
				     &( url_record_data[ location_offset ] ),
				     record_size - location_offset,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to calculate location hash.",
					 function );

					goto on_error;
				}
				libcnotify_printf(
				 "%s: hash value\t\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );
			}
#endif
			if( ( url_record_data[ location_offset + value_size - 1 ] != 0 )
			 && ( ( item_flags & LIBMSIECF_ITEM_FLAG_PARTIAL ) == 0 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported unterminated location string.",
				 function );

				goto on_error;
			}
			if( url_values->type == LIBMSIECF_URL_ITEM_TYPE_UNDEFINED )
			{
				if( value_size >= 18 )
				{
					if( ( url_record_data[ location_offset ] == (uint8_t) ':' )
					 && ( url_record_data[ location_offset + 1 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 1 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 2 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 2 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 3 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 3 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 4 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 4 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 5 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 5 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 6 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 6 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 7 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 7 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 8 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 8 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 9 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 9 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 10 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 10 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 11 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 11 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 12 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 12 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 13 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 13 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 14 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 14 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 15 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 15 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 16 ] >= (uint8_t) '0' )
					 && ( url_record_data[ location_offset + 16 ] <= (uint8_t) '9' )
					 && ( url_record_data[ location_offset + 17 ] == (uint8_t) ':' ) )
					{
						first_year  = (uint16_t) url_record_data[ location_offset + 1 ] - (uint8_t) '0';
						first_year *= 10;
						first_year += (uint16_t) url_record_data[ location_offset + 2 ] - (uint8_t) '0';
						first_year *= 10;
						first_year += (uint16_t) url_record_data[ location_offset + 3 ] - (uint8_t) '0';
						first_year *= 10;
						first_year += (uint16_t) url_record_data[ location_offset + 4 ] - (uint8_t) '0';

						first_month  = url_record_data[ location_offset + 5 ] - (uint8_t) '0';
						first_month *= 10;
						first_month += url_record_data[ location_offset + 6 ] - (uint8_t) '0';

						first_day_of_month  = url_record_data[ location_offset + 7 ] - (uint8_t) '0';
						first_day_of_month *= 10;
						first_day_of_month += url_record_data[ location_offset + 8 ] - (uint8_t) '0';

						second_year  = (uint16_t) url_record_data[ location_offset + 9 ] - (uint8_t) '0';
						second_year *= 10;
						second_year += (uint16_t) url_record_data[ location_offset + 10 ] - (uint8_t) '0';
						second_year *= 10;
						second_year += (uint16_t) url_record_data[ location_offset + 11 ] - (uint8_t) '0';
						second_year *= 10;
						second_year += (uint16_t) url_record_data[ location_offset + 12 ] - (uint8_t) '0';

						second_month  = url_record_data[ location_offset + 13 ] - (uint8_t) '0';
						second_month *= 10;
						second_month += url_record_data[ location_offset + 14 ] - (uint8_t) '0';

						second_day_of_month  = url_record_data[ location_offset + 15 ] - (uint8_t) '0';
						second_day_of_month *= 10;
						second_day_of_month += url_record_data[ location_offset + 16 ] - (uint8_t) '0';

						number_of_days = 0;

						if( first_year == second_year )
						{
							if( first_month == second_month )
							{
								if( first_day_of_month < second_day_of_month )
								{
									number_of_days = second_day_of_month - first_day_of_month;
								}
							}
							else if( ( first_month + 1 ) == second_month )
							{
								switch( first_month )
								{
									case 3:
									case 5:
									case 7:
									case 8:
									case 10:
									case 12:
										number_of_days = ( 31 + second_day_of_month ) - first_day_of_month;
										break;

									case 2:
										if( ( ( ( first_year % 4 ) == 0 )
										  &&  ( ( first_year % 100 ) != 0 ) )
										 || ( ( first_year % 400 ) == 0 ) )
										{
											number_of_days = ( 29 + second_day_of_month ) - first_day_of_month;
										}
										else
										{
											number_of_days = ( 28 + second_day_of_month ) - first_day_of_month;
										}
										break;

									case 4:
									case 6:
									case 9:
									case 11:
										number_of_days = ( 30 + second_day_of_month ) - first_day_of_month;
										break;
								}
							}
						}
						else if( ( first_year + 1 ) == second_year )
						{
							if( ( first_month == 12 )
							 && ( second_month == 1 ) )
							{
								number_of_days = ( 31 + second_day_of_month ) - first_day_of_month;
							}
						}
						if( number_of_days == 1 )
						{
							url_values->type = LIBMSIECF_URL_ITEM_TYPE_HISTORY_DAILY;
						}
						else if( number_of_days == 7 )
						{
							url_values->type = LIBMSIECF_URL_ITEM_TYPE_HISTORY_WEEKLY;
						}
					}
				}
			}
			if( url_values->type == LIBMSIECF_URL_ITEM_TYPE_UNDEFINED )
			{
				if( value_size >= 11 )
				{
					if( memory_compare(
					     &( url_record_data[ location_offset ] ),
					     "iedownload:",
					     11 ) == 0 )
					{
						url_values->type = LIBMSIECF_URL_ITEM_TYPE_DOWNLOAD;
					}
				}
			}
			if( url_values->type == LIBMSIECF_URL_ITEM_TYPE_UNDEFINED )
			{
				if( value_size >= 9 )
				{
					if( memory_compare(
					     &( url_record_data[ location_offset ] ),
					     "DOMStore:",
					     9 ) == 0 )
					{
						url_values->type = LIBMSIECF_URL_ITEM_TYPE_DOM_STORE;
					}
					else if( memory_compare(
					          &( url_record_data[ location_offset ] ),
					          "feedplat:",
					          9 ) == 0 )
					{
						url_values->type = LIBMSIECF_URL_ITEM_TYPE_RSS_FEED;
					}
					else if( memory_compare(
					          &( url_record_data[ location_offset ] ),
					          "iecompat:",
					          9 ) == 0 )
					{
						url_values->type = LIBMSIECF_URL_ITEM_TYPE_COMPATIBILITY;
					}
					else if( memory_compare(
					          &( url_record_data[ location_offset ] ),
					          "PrivacIE:",
					          9 ) == 0 )
					{
						url_values->type = LIBMSIECF_URL_ITEM_TYPE_INPRIVATE_FILTERING;
					}
					else if( memory_compare(
					          &( url_record_data[ location_offset ] ),
					          "userdata:",
					          9 ) == 0 )
					{
						url_values->type = LIBMSIECF_URL_ITEM_TYPE_USER_DATA;
					}
				}
			}
			if( url_values->type == LIBMSIECF_URL_ITEM_TYPE_UNDEFINED )
			{
				if( value_size >= 8 )
				{
					if( memory_compare(
					     &( url_record_data[ location_offset ] ),
					     "Visited:",
					     8 ) == 0 )
					{
						url_values->type = LIBMSIECF_URL_ITEM_TYPE_HISTORY;
					}
				}
			}
			if( url_values->type == LIBMSIECF_URL_ITEM_TYPE_UNDEFINED )
			{
				if( value_size >= 7 )
				{
					if( memory_compare(
					     &( url_record_data[ location_offset ] ),
					     "Cookie:",
					     7 ) == 0 )
					{
						url_values->type = LIBMSIECF_URL_ITEM_TYPE_COOKIE;
					}
				}
			}
			if( url_values->type == LIBMSIECF_URL_ITEM_TYPE_UNDEFINED )
			{
				if( value_size >= 6 )
				{
					if( memory_compare(
					     &( url_record_data[ location_offset ] ),
					     "ietld:",
					     6 ) == 0 )
					{
						url_values->type = LIBMSIECF_URL_ITEM_TYPE_TLD;
					}
				}
			}
			if( url_values->type == LIBMSIECF_URL_ITEM_TYPE_UNDEFINED )
			{
				url_values->type = LIBMSIECF_URL_ITEM_TYPE_CACHE;

/* TODO way to determine unknown
				url_values->type = LIBMSIECF_URL_ITEM_TYPE_UNKNOWN;
*/
			}
		}
	}
	if( filename_offset > 0 )
	{
		if( filename_offset > record_size )
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
			if( libfvalue_value_type_initialize(
			     &( url_values->filename ),
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
			              url_values->filename,
			              &( url_record_data[ filename_offset ] ),
			              record_size - filename_offset,
			              io_handle->ascii_codepage,
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
				 "%s: filename\t\t\t\t\t: ",
				 function );

				if( libfvalue_value_print(
				     url_values->filename,
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
#endif
			if( ( url_record_data[ filename_offset + value_size - 1 ] != 0 )
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
	if( data_offset > 0 )
	{
		if( data_offset > record_size )
		{
			if( ( item_flags & LIBMSIECF_ITEM_FLAG_PARTIAL ) == 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: data offset exceeds size of URL record data.",
				 function );

				goto on_error;
			}
		}
		else
		{
			if( ( data_offset + data_size ) > record_size )
			{
				if( ( item_flags & LIBMSIECF_ITEM_FLAG_PARTIAL ) == 0 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: data size exceeds size of URL record data.",
					 function );

					goto on_error;
				}
				else
				{
					data_size = record_size - data_offset;
				}
			}
			url_values->data_size = (size_t) data_size;

			url_values->data = (uint8_t *) memory_allocate(
			                                sizeof( uint8_t ) * url_values->data_size );

			if( url_values->data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create data.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     url_values->data,
			     &( url_record_data[ data_offset ] ),
			     url_values->data_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to copy data.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: data:\n",
				 function );
				libcnotify_print_data(
				 &( url_record_data[ data_offset ] ),
				 data_size,
				 0 );

				if( url_values->type == LIBMSIECF_URL_ITEM_TYPE_CACHE )
				{
					/* The data string in not necessarily terminated by an end-of-string character
					 */
					libcnotify_printf(
					 "%s: data string\t\t\t\t\t: ",
					 function );

					for( string_index = 0;
					     string_index < data_size;
					     string_index++ )
					{
						libcnotify_printf(
						 "%c",
						 url_record_data[ data_offset + string_index ] );
					}
					libcnotify_printf(
					 "\n" );
				}
				else if( url_values->type == LIBMSIECF_URL_ITEM_TYPE_HISTORY )
				{
					visited_entry_data = &( url_record_data[ data_offset ] );

					do
					{
						visited_entry_index++;

						byte_stream_copy_to_uint16_little_endian(
						 visited_entry_data,
						 value_16bit );

						visited_entry_data += 2;

						libcnotify_printf(
						 "%s: data entry: %02d size\t\t\t\t: %" PRIu16 "\n",
						 function,
						 visited_entry_index,
						 value_16bit );

						libcnotify_printf(
						 "%s: data entry: %02d type\t\t\t\t: 0x%02" PRIx8 " (%s : %s)\n",
						 function,
						 visited_entry_index,
						 visited_entry_data[ 0 ],
						 libmsiecf_property_type_get_identifier(
						  NULL,
						  (uint32_t) visited_entry_data[ 0 ],
						  (uint32_t) visited_entry_data[ 1 ] ),
						 libmsiecf_property_type_get_description(
						  NULL,
						  (uint32_t) visited_entry_data[ 0 ],
						  (uint32_t) visited_entry_data[ 1 ] ) );

						libcnotify_printf(
						 "%s: data entry: %02d value type\t\t\t: 0x%02" PRIx8 " (%s : %s)\n",
						 function,
						 visited_entry_index,
						 visited_entry_data[ 1 ],
						 libfole_value_type_get_identifier(
						  (uint32_t) visited_entry_data[ 1 ] ),
						 libfole_value_type_get_description(
						  (uint32_t) visited_entry_data[ 1 ] ) );

						visited_entry_data += 2;

						if( value_16bit > 4 )
						{
							value_16bit -= 4;

							libcnotify_printf(
							 "%s: data entry: %02d value:\n",
							 function,
							 visited_entry_index );
							libcnotify_print_data(
							 visited_entry_data,
							 value_16bit,
							 0 );

							visited_entry_data += value_16bit;
						}
					}
					while( value_16bit > 0 );
				}
			}
#endif
		}
	}
	memory_free(
	 url_record_data );

	url_record_data = NULL;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
#if defined( HAVE_VERBOSE_OUTPUT )
	switch( url_values->type )
	{
		case LIBMSIECF_URL_ITEM_TYPE_COOKIE:
			if ( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_COOKIE ) == 0 )
			{
				libcnotify_printf(
				 "%s: detected type cookie but corresponding cache entry flag (COOKIE_CACHE_ENTRY) is not set.\n",
				 function );
			}
			break;

		case LIBMSIECF_URL_ITEM_TYPE_HISTORY:
			if ( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_URLHISTORY ) == 0 )
			{
				libcnotify_printf(
				 "%s: detected type history but corresponding cache entry flag (URLHISTORY_CACHE_ENTRY) is not set.\n",
				 function );
			}
			break;

		case LIBMSIECF_URL_ITEM_TYPE_HISTORY_DAILY:
		case LIBMSIECF_URL_ITEM_TYPE_HISTORY_WEEKLY:
			if ( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_URLHISTORY ) == 0 )
			{
				libcnotify_printf(
				 "%s: detected type history periodic but corresponding cache entry flag (URLHISTORY_CACHE_ENTRY) is not set.\n",
				 function );
			}
			break;
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	if( fat_date_time != NULL )
	{
		libfdatetime_fat_date_time_free(
		 &fat_date_time,
		 NULL );
	}
#endif
	if( url_record_data != NULL )
	{
		memory_free(
		 url_record_data );
	}
	return( -1 );
}

