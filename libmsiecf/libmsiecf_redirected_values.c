/*
 * Redirected values functions
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
#include <types.h>

#include "libmsiecf_definitions.h"
#include "libmsiecf_hash.h"
#include "libmsiecf_io_handle.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"
#include "libmsiecf_libfvalue.h"
#include "libmsiecf_redirected_values.h"

#include "msiecf_redr_record.h"

/* Creates redirected values
 * Make sure the value redirected_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_redirected_values_initialize(
     libmsiecf_redirected_values_t **redirected_values,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_redirected_values_initialize";

	if( redirected_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected values.",
		 function );

		return( -1 );
	}
	if( *redirected_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid redirected values value already set.",
		 function );

		return( -1 );
	}
	*redirected_values = memory_allocate_structure(
	                      libmsiecf_redirected_values_t );

	if( *redirected_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create redirected values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *redirected_values,
	     0,
	     sizeof( libmsiecf_redirected_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear redirected values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *redirected_values != NULL )
	{
		memory_free(
		 *redirected_values );

		*redirected_values = NULL;
	}
	return( -1 );
}

/* Frees redirected values
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_redirected_values_free(
     libmsiecf_redirected_values_t **redirected_values,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_redirected_values_free";
	int result            = 1;

	if( redirected_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected values.",
		 function );

		return( -1 );
	}
	if( *redirected_values != NULL )
	{
		if( ( *redirected_values )->location != NULL )
		{
			if( libfvalue_value_free(
			     &( ( *redirected_values )->location ),
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
		memory_free(
		 *redirected_values );

		*redirected_values = NULL;
	}
	return( result );
}

/* Reads a redirected
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_redirected_values_read(
     libmsiecf_redirected_values_t *redirected_values,
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t redirected_offset,
     size32_t record_size,
     uint8_t item_flags,
     libcerror_error_t **error )
{
	uint8_t *redr_record_data = NULL;
	static char *function     = "libmsiecf_redirected_values_read";
	ssize_t read_count        = 0;
	ssize_t value_size        = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit      = 0;
#endif

	if( redirected_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid redirected values.",
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
		 "%s: unsupported REDR record size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading REDR record at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 redirected_offset,
		 redirected_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     redirected_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek REDR record offset: %" PRIi64 ".",
		 function,
		 redirected_offset );

		goto on_error;
	}
	redr_record_data = (uint8_t *) memory_allocate(
	                                sizeof( uint8_t ) * record_size );

	if( redr_record_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create REDR record data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              redr_record_data,
	              record_size,
	              error );

	if( read_count != (ssize_t) record_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read REDR record data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: REDR record data:\n",
		 function );
		libcnotify_print_data(
		 redr_record_data,
		 record_size,
		 0 );
	}
#endif
	if( memory_compare(
	     ( (msiecf_redr_record_header_t *) redr_record_data )->signature,
	     "REDR",
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 ( (msiecf_redr_record_header_t *) redr_record_data )->signature[ 0 ],
		 ( (msiecf_redr_record_header_t *) redr_record_data )->signature[ 1 ],
		 ( (msiecf_redr_record_header_t *) redr_record_data )->signature[ 2 ],
		 ( (msiecf_redr_record_header_t *) redr_record_data )->signature[ 3 ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_redr_record_header_t *) redr_record_data )->number_of_blocks,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of blocks\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_redr_record_header_t *) redr_record_data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (msiecf_redr_record_header_t *) redr_record_data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );
	}
#endif
	if( libfvalue_value_type_initialize(
	     &( redirected_values->location ),
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
	              redirected_values->location,
	              &( redr_record_data[ 16 ] ),
	              record_size - 16,
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
		 "%s: location\t\t\t\t: ",
		 function );

		if( libfvalue_value_print(
		     redirected_values->location,
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
		     &( redr_record_data[ 16 ] ),
		     record_size - 16,
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
		 "%s: hash value\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );
	}
#endif
	if( ( redr_record_data[ 16 + value_size - 1 ] != 0 )
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
	memory_free(
	 redr_record_data );

	redr_record_data = NULL;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( redirected_values->location != NULL )
	{
		libfvalue_value_free(
		 &( redirected_values->location ),
		 NULL );
	}
	if( redr_record_data != NULL )
	{
		memory_free(
		 redr_record_data );
	}
	return( -1 );
}

