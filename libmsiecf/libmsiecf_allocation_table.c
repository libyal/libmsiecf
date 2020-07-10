/*
 * Allocation table functions
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

#include "libmsiecf_allocation_table.h"
#include "libmsiecf_definitions.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcdata.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"

/* Reads an allocation table
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_allocation_table_read(
     libcdata_range_list_t *unallocated_block_list,
     libbfio_handle_t *file_io_handle,
     off64_t allocation_table_offset,
     size64_t file_size,
     off64_t base_offset,
     uint16_t block_size,
     uint32_t number_of_blocks,
     uint32_t blocks_allocated,
     libcerror_error_t **error )
{
	uint8_t *allocation_table_data       = NULL;
	static char *function                = "libmsiecf_allocation_table_read";
	off64_t offset                       = 0;
	off64_t unallocated_offset           = 0;
	size_t read_size                     = 0;
	size_t table_iterator                = 0;
	size_t unallocated_size              = 0;
	ssize_t read_count                   = 0;
	uint32_t calculated_blocks_allocated = 0;
	uint8_t bit_iterator                 = 0;
	uint8_t allocation_table_entry       = 0;
	int result                           = 0;

	if( unallocated_block_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid unallocated block list.",
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
	if( file_size > (size64_t) INT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid file size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( base_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid base offset value less than zero.",
		 function );

		return( -1 );
	}
	if( base_offset > (off64_t) file_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid base offset value exceeds file size.",
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
	/* Every bit in the allocation table represents one block
	 */
	read_size = number_of_blocks / 8;

	if( read_size == 0 )
	{
		return( 1 );
	}
	if( read_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid allocation table data size value exceeds maximum allocation size.",
		 function );

		goto on_error;
	}
	if( (off64_t) read_size > ( base_offset - allocation_table_offset ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid allocation table size value exceeds base offset.",
		 function );

		goto on_error;
	}
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     allocation_table_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek allocation table offset: %" PRIi64 ".",
		 function,
		 allocation_table_offset );

		goto on_error;
	}
	allocation_table_data = (uint8_t *) memory_allocate(
	                                     read_size );

	if( allocation_table_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create alloction table data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              allocation_table_data,
	              read_size,
	              error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read allocation table.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: allocation table:\n",
		 function );
		libcnotify_print_data(
		 allocation_table_data,
		 read_size,
		 0 );
	}
#endif
	for( table_iterator = 0;
	     table_iterator < read_size;
	     table_iterator++ )
	{
		allocation_table_entry = allocation_table_data[ table_iterator ];

		for( bit_iterator = 0;
		     bit_iterator < 8;
		     bit_iterator++ )
		{
			if( ( allocation_table_entry & 0x01 ) == 0 )
			{
				if( unallocated_size == 0 )
				{
					unallocated_offset = offset;
				}
				unallocated_size += block_size;
			}
			else if( unallocated_size > 0 )
			{
				result = libcdata_range_list_insert_range(
				          unallocated_block_list,
				          (uint64_t) ( base_offset + unallocated_offset ),
				          (uint64_t) unallocated_size,
				          NULL,
				          NULL,
				          NULL,
				          error );

				if( result == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to insert unallocated block in offset list.",
					 function );

					goto on_error;
				}
				unallocated_size = 0;
			}
			if( ( allocation_table_entry & 0x01 ) != 0 )
			{
				calculated_blocks_allocated++;
			}
			allocation_table_entry >>= 1;

			offset += block_size;

			if( offset >= (off64_t) file_size )
			{
				break;
			}
		}
		if( offset >= (off64_t) file_size )
		{
			break;
		}
	}
	if( unallocated_size > 0 )
	{
		result = libcdata_range_list_insert_range(
		          unallocated_block_list,
		          (uint64_t) ( base_offset + unallocated_offset ),
		          (uint64_t) unallocated_size,
		          NULL,
		          NULL,
		          NULL,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to insert unallocated block in offset list.",
			 function );

			goto on_error;
		}
		unallocated_size = 0;
	}
	memory_free(
	 allocation_table_data );

	allocation_table_data = NULL;

#if defined( HAVE_VERBOSE_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( blocks_allocated != calculated_blocks_allocated )
		{
			libcnotify_printf(
			 "%s: mismatch in blocks allocated (stored: %" PRIu32 ", calculated: %" PRIu32 ")\n",
			 function,
			 blocks_allocated,
			 calculated_blocks_allocated );
		}
	}
#endif
	return( 1 );

on_error:
	if( allocation_table_data != NULL )
	{
		memory_free(
		 allocation_table_data );
	}
	return( -1 );
}

