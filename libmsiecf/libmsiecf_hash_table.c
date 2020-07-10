/*
 * Hash table functions
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

#include "libmsiecf_definitions.h"
#include "libmsiecf_hash_table.h"
#include "libmsiecf_item_descriptor.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcdata.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"

#include "msiecf_hash_record.h"

/* Reads a hash table
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_hash_table_read(
     libcdata_array_t *hash_table,
     off64_t *next_hash_table_offset,
     libbfio_handle_t *file_io_handle,
     off64_t hash_table_offset,
     size32_t block_size,
     libcerror_error_t **error )
{
	msiecf_hash_record_header_t hash_record_header;

	uint8_t *hash_record_data                    = NULL;
	uint8_t *entry_data                          = NULL;
	static char *function                        = "libmsiecf_hash_table_read";
	size_t read_size                             = 0;
	size_t table_iterator                        = 0;
	ssize_t read_count                           = 0;
	uint32_t entry_hash                          = 0;
	uint32_t entry_offset                        = 0;
	uint32_t number_of_blocks                    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                         = 0;
	int number_of_items                          = 0;
#endif

	if( hash_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hash table.",
		 function );

		return( -1 );
	}
	if( next_hash_table_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid next hash table offset.",
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
	if( block_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid block size value zero or less.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading HASH record at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 hash_table_offset,
		 hash_table_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     hash_table_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek HASH record offset: %" PRIi64 ".",
		 function,
		 hash_table_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &hash_record_header,
	              sizeof( msiecf_hash_record_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( msiecf_hash_record_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read HASH record header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: HASH record header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &hash_record_header,
		 sizeof( msiecf_hash_record_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     hash_record_header.signature,
	     "HASH",
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
	 hash_record_header.number_of_blocks,
	 number_of_blocks );
	byte_stream_copy_to_uint32_little_endian(
	 hash_record_header.next_offset,
	 *next_hash_table_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: %c%c%c%c\n",
		 function,
		 hash_record_header.signature[ 0 ],
		 hash_record_header.signature[ 1 ],
		 hash_record_header.signature[ 2 ],
		 hash_record_header.signature[ 3 ] );

		libcnotify_printf(
		 "%s: number of blocks\t\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_blocks );

		libcnotify_printf(
		 "%s: next offset\t\t\t\t\t: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 *next_hash_table_offset,
		 *next_hash_table_offset );

		byte_stream_copy_to_uint32_little_endian(
		 hash_record_header.sequence_number,
		 value_32bit );
		libcnotify_printf(
		 "%s: sequence number\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	read_size = ( number_of_blocks * block_size ) - sizeof( msiecf_hash_record_header_t );

	if( read_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid HASH record data size value exceeds maximum allocation size.",
		 function );

		goto on_error;
	}
	if( ( read_size == 0 )
	 || ( ( read_size % 8 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported HASH record data size.",
		 function );

		goto on_error;
	}
	hash_record_data = (uint8_t *) memory_allocate(
	                                read_size );

	if( hash_record_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create HASH record data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              hash_record_data,
	              read_size,
	              error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read HASH record data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: HASH record data:\n",
		 function );
		libcnotify_print_data(
		 hash_record_data,
		 read_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	read_size /= 8;

	entry_data = hash_record_data;

	for( table_iterator = 0;
	     table_iterator < read_size;
	     table_iterator++ )
	{
		byte_stream_copy_to_uint32_little_endian(
		 entry_data,
		 entry_hash );

		entry_data += 4;

		byte_stream_copy_to_uint32_little_endian(
		 entry_data,
		 entry_offset );

		entry_data += 4;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: entry %03d hash\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 table_iterator,
			 entry_hash );
			libcnotify_printf(
			 "%s: entry %03d offset\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 table_iterator,
			 entry_offset );
		}
#endif
		/* Skip empty entries
		 */
		if( entry_hash == entry_offset )
		{
			continue;
		}
		/* Skip uninitialized entries
		 * These should only appear at the end of the HASH record data
		 */
		if( ( entry_hash == 0x0badf00d )
		 || ( entry_hash == 0xdeadbeef ) )
		{
			continue;
		}
		/* Skip invalid URL entries
		 */
		if( ( entry_hash & 0x0f ) == 0x01 )
		{
			continue;
		}
		/* Check if the entry record offset is block aligned
		 */
		if( ( entry_offset % block_size ) != 0 )
		{
			continue;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		number_of_items++;
#endif
		/* TODO flag hashed items
		 */

	}
	memory_free(
	 hash_record_data );

	hash_record_data = NULL;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: found %d hashed items.\n",
		 function,
		 number_of_items );
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( hash_record_data != NULL )
	{
		memory_free(
		 hash_record_data );
	}
	return( -1 );
}

