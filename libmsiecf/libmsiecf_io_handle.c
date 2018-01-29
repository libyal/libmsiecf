/*
 * Input/Output (IO) handle
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

#include "libmsiecf_allocation_table.h"
#include "libmsiecf_codepage.h"
#include "libmsiecf_debug.h"
#include "libmsiecf_definitions.h"
#include "libmsiecf_directory_descriptor.h"
#include "libmsiecf_hash_table.h"
#include "libmsiecf_io_handle.h"
#include "libmsiecf_item_descriptor.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcdata.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"
#include "libmsiecf_redirected_values.h"
#include "libmsiecf_url_values.h"

#include "msiecf_file_header.h"
#include "msiecf_record.h"

char *msiecf_file_signature = "Client UrlCache MMF Ver ";

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_io_handle_initialize(
     libmsiecf_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_io_handle_initialize";

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
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libmsiecf_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libmsiecf_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	( *io_handle )->block_size     = LIBMSIECF_DEFAULT_BLOCK_SIZE;
	( *io_handle )->ascii_codepage = LIBMSIECF_CODEPAGE_WINDOWS_1252;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_io_handle_free(
     libmsiecf_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_io_handle_free";
	int result            = 1;

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
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( result );
}

/* Clears an IO handle
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_io_handle_clear(
     libmsiecf_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_io_handle_clear";

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
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libmsiecf_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	io_handle->block_size     = LIBMSIECF_DEFAULT_BLOCK_SIZE;
	io_handle->ascii_codepage = LIBMSIECF_CODEPAGE_WINDOWS_1252;

	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_io_handle_read_file_header(
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *hash_table_offset,
     libcdata_array_t *cache_directory_table,
     libcdata_range_list_t *unallocated_block_list,
     libcerror_error_t **error )
{
	msiecf_file_header_t file_header;

	libmsiecf_directory_descriptor_t *directory_descriptor = NULL;
	uint8_t *cache_directories_data                        = NULL;
	uint8_t *cache_directory_entry                         = NULL;
	static char *function                                  = "libmsiecf_io_handle_read_file_header";
	size_t read_size                                       = 0;
	ssize_t read_count                                     = 0;
	uint32_t cache_directory_iterator                      = 0;
	uint32_t number_of_cache_directories                   = 0;
	uint32_t number_of_blocks                              = 0;
	uint32_t blocks_allocated                              = 0;
	int cached_directory_entry_index                       = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                                   = 0;
#endif

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
	if( hash_table_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hash table offset.",
		 function );

		return( -1 );
	}
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
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &file_header,
	              sizeof( msiecf_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( msiecf_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &file_header,
		 sizeof( msiecf_file_header_t ),
		 0 );
	}
#endif
	if( ( file_header.signature[ 27 ] != 0 )
	 || ( file_header.signature[ 26 ] < (uint8_t) '0' )
	 || ( file_header.signature[ 26 ] > (uint8_t) '9' )
	 || ( file_header.signature[ 25 ] != (uint8_t) '.' )
	 || ( file_header.signature[ 24 ] < (uint8_t) '0' )
	 || ( file_header.signature[ 24 ] > (uint8_t) '9' )
	 || ( memory_compare(
	       file_header.signature,
	       msiecf_file_signature,
	       24 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file signature.",
		 function );

		goto on_error;
	}
	io_handle->major_version = file_header.signature[ 24 ] - (uint8_t) '0';
	io_handle->minor_version = file_header.signature[ 26 ] - (uint8_t) '0';

	byte_stream_copy_to_uint32_little_endian(
	 file_header.file_size,
	 io_handle->file_size );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.hash_table_offset,
	 *hash_table_offset );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.number_of_blocks,
	 number_of_blocks );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.blocks_allocated,
	 blocks_allocated );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %s\n",
		 function,
		 file_header.signature );

		libcnotify_printf(
		 "%s: file size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 io_handle->file_size );

		libcnotify_printf(
		 "%s: hash table offset\t\t\t: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 *hash_table_offset,
		 *hash_table_offset );

		libcnotify_printf(
		 "%s: number of blocks\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_blocks );

		libcnotify_printf(
		 "%s: blocks allocated\t\t\t: %" PRIu32 "\n",
		 function,
		 blocks_allocated );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.cache_size_limit,
		 value_32bit );
		libcnotify_printf(
		 "%s: cache size limit\t\t\t: %" PRIu32 " bytes\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.cache_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: cache size\t\t\t: %" PRIu32 " bytes\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.non_releasable_cache_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: non-releasable cache size\t\t: %" PRIu32 " bytes\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 file_header.number_of_cache_directories,
	 number_of_cache_directories );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading cache directory table:\n" );
		libcnotify_printf(
		 "%s: number of cache directories\t: %" PRIu32 "\n",
		 function,
		 number_of_cache_directories );
	}
#endif
	if( number_of_cache_directories > 0 )
	{
		read_size = sizeof( msiecf_cache_directory_entry_t )
		          * number_of_cache_directories;

		cache_directories_data = (uint8_t *) memory_allocate(
						      read_size );


		if( cache_directories_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create cache directories data.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      cache_directories_data,
			      read_size,
			      error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read cache directories data.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: cache directories data:\n",
			 function );
			libcnotify_print_data(
			 cache_directories_data,
			 read_size,
			 0 );
		}
#endif
		cache_directory_entry = cache_directories_data;

		for( cache_directory_iterator = 0;
		     cache_directory_iterator < number_of_cache_directories;
		     cache_directory_iterator++ )
		{
			if( libmsiecf_directory_descriptor_initialize(
			     &directory_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create directory descriptor.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     directory_descriptor->name,
			     ( (msiecf_cache_directory_entry_t * ) cache_directory_entry )->name,
			     8 ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to set directory descriptor name.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (msiecf_cache_directory_entry_t * ) cache_directory_entry )->number_of_cached_files,
				 value_32bit );
				libcnotify_printf(
				 "%s: cache directory: %02" PRIu32 " number of cached files\t: %" PRIu32 "\n",
				 function,
				 cache_directory_iterator,
				 value_32bit );

				libcnotify_printf(
				 "%s: cache directory: %02" PRIu32 " name\t\t\t\t: %s\n",
				 function,
				 cache_directory_iterator,
				 directory_descriptor->name );
			}
#endif
			if( libcdata_array_append_entry(
			     cache_directory_table,
			     &cached_directory_entry_index,
			     (intptr_t *) directory_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append directory name to cached directory table.",
				 function );

				goto on_error;
			}
			directory_descriptor = NULL;

			cache_directory_entry += sizeof( msiecf_cache_directory_entry_t );
		}
		memory_free(
		 cache_directories_data );

		cache_directories_data = NULL;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
		libcnotify_printf(
		 "Reading allocation table:\n" );
	}
#endif
	if( libmsiecf_allocation_table_read(
	     unallocated_block_list,
	     file_io_handle,
	     0x250,
	     io_handle->file_size,
	     0x4000,
	     io_handle->block_size,
	     number_of_blocks,
	     blocks_allocated,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read allocation table.",
		 function );

		goto on_error;
	}
	if( ! ( ( ( io_handle->major_version == 4 )
	  &&      ( io_handle->minor_version == 7 ) )
	 ||     ( ( io_handle->major_version == 5 )
	  &&      ( io_handle->minor_version == 2 ) ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( directory_descriptor != NULL )
	{
		libmsiecf_directory_descriptor_free(
		 &directory_descriptor,
		 NULL );
	}
	if( cache_directories_data != NULL )
	{
		memory_free(
		 cache_directories_data );
	}
	return( -1 );
}

/* Reads the hash table from the HASH record blocks
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_io_handle_read_hash_table(
     libcdata_array_t *hash_table,
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t hash_table_offset,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_io_handle_read_hash_table";

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
	while( hash_table_offset != 0 )
	{
		if( libmsiecf_hash_table_read(
		     hash_table,
		     &hash_table_offset,
		     file_io_handle,
		     hash_table_offset,
		     io_handle->block_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read hash table at offset: %" PRIi64 ".",
			 function,
			 hash_table_offset );

			return( -1 );
		}
	}
	return( 1 );
}

/* Scans the allocated part of the file for records
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_io_handle_read_record_scan(
     libcdata_array_t *item_table,
     libcdata_array_t *recovered_item_table,
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcdata_range_list_t *unallocated_block_list,
     libcerror_error_t **error )
{
	msiecf_record_header_t record_header;

	libmsiecf_item_descriptor_t *item_descriptor      = NULL;
	libmsiecf_item_descriptor_t *last_item_descriptor = NULL;
	static char *function                             = "libmsiecf_io_handle_record_scan";
	intptr_t *value                                   = NULL;
	uint64_t range_offset                             = 0;
	uint64_t range_size                               = 0;
	size32_t remaining_record_size                    = 0;
	size32_t record_size                              = 0;
	ssize_t read_count                                = 0;
	uint32_t number_of_blocks                         = 0;
	int item_table_entry_index                        = 0;
	int detected_new_record                           = 0;
	int result                                        = 0;
	uint8_t item_type                                 = 0;
	uint8_t new_item_type                             = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	const char *record_type                           = NULL;
	int number_of_items                               = 0;
	int number_of_recovered_items                     = 0;
	int number_of_partial_recovered_items             = 0;
#endif

	if( item_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item table.",
		 function );

		return( -1 );
	}
	if( recovered_item_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid recovered item table.",
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
	while( file_offset < (off64_t) io_handle->file_size )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: scanning for record at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
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
			 "%s: unable to seek offset: %" PRIi64 ".",
			 function,
			 file_offset );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      (uint8_t *) &record_header,
			      sizeof( msiecf_record_header_t ),
			      error );

		if( read_count != (ssize_t) sizeof( msiecf_record_header_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read record header.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: record header:\n",
			 function );
			libcnotify_print_data(
			 (uint8_t *) &record_header,
			 sizeof( msiecf_record_header_t ),
			 0 );
		}
#endif
		detected_new_record = 0;

		/* The most common record type is checked first
		 */
		if( ( record_header.signature[ 0 ] == (uint8_t) 'U' )
		 && ( record_header.signature[ 1 ] == (uint8_t) 'R' )
		 && ( record_header.signature[ 2 ] == (uint8_t) 'L' )
		 && ( record_header.signature[ 3 ] == (uint8_t) ' ' ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 record_header.number_of_blocks,
			 number_of_blocks );

			new_item_type       = LIBMSIECF_ITEM_TYPE_URL;
			detected_new_record = 1;

#if defined( HAVE_DEBUG_OUTPUT )
			record_type = "URL";
#endif
		}
		else if( ( record_header.signature[ 0 ] == (uint8_t) 'H' )
		      && ( record_header.signature[ 1 ] == (uint8_t) 'A' )
		      && ( record_header.signature[ 2 ] == (uint8_t) 'S' )
		      && ( record_header.signature[ 3 ] == (uint8_t) 'H' ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 record_header.number_of_blocks,
			 number_of_blocks );

			new_item_type       = LIBMSIECF_ITEM_TYPE_UNDEFINED;
			detected_new_record = 1;

#if defined( HAVE_DEBUG_OUTPUT )
			record_type = "HASH";
#endif
		}
		else if( ( record_header.signature[ 0 ] == (uint8_t) 'R' )
		      && ( record_header.signature[ 1 ] == (uint8_t) 'E' )
		      && ( record_header.signature[ 2 ] == (uint8_t) 'D' )
		      && ( record_header.signature[ 3 ] == (uint8_t) 'R' ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 record_header.number_of_blocks,
			 number_of_blocks );

			new_item_type       = LIBMSIECF_ITEM_TYPE_REDIRECTED;
			detected_new_record = 1;

#if defined( HAVE_DEBUG_OUTPUT )
			record_type = "REDR";
#endif
		}
		else if( ( record_header.signature[ 0 ] == (uint8_t) 'L' )
		      && ( record_header.signature[ 1 ] == (uint8_t) 'E' )
		      && ( record_header.signature[ 2 ] == (uint8_t) 'A' )
		      && ( record_header.signature[ 3 ] == (uint8_t) 'K' ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 record_header.number_of_blocks,
			 number_of_blocks );

			new_item_type       = LIBMSIECF_ITEM_TYPE_LEAK;
			detected_new_record = 1;

#if defined( HAVE_DEBUG_OUTPUT )
			record_type = "LEAK";
#endif
		}
#ifdef INVALIDDATARESET
		else if( ( record_header.signature[ 0 ] == 0x0d )
		      && ( record_header.signature[ 1 ] == 0xf0 )
		      && ( record_header.signature[ 2 ] == 0xad )
		      && ( record_header.signature[ 3 ] == 0x0b ) )
		{
			number_of_blocks    = 1;
			new_item_type       = LIBMSIECF_ITEM_TYPE_UNDEFINED;
			detected_new_record = 1;
		}
		else if( ( record_header.signature[ 0 ] == 0xef )
		      && ( record_header.signature[ 1 ] == 0xbe )
		      && ( record_header.signature[ 2 ] == 0xad )
		      && ( record_header.signature[ 3 ] == 0xde ) )
		{
			number_of_blocks    = 1;
			new_item_type       = LIBMSIECF_ITEM_TYPE_UNDEFINED;
			detected_new_record = 1;
		}
#endif
		else if( remaining_record_size == 0 )
		{
			number_of_blocks = 1;
			item_type        = LIBMSIECF_ITEM_TYPE_UNDEFINED;
		}
		if( last_item_descriptor != NULL )
		{
			/* Flag the previous item descriptor it can contain an invalid
			 * number of blocks value
			 */
			if( ( remaining_record_size == 0 )
			 && ( detected_new_record == 0 ) )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: marking record as tainted.\n",
					 function );
				}
#endif
				last_item_descriptor->flags |= LIBMSIECF_ITEM_FLAG_TAINTED;
			}
			last_item_descriptor = NULL;
		}
		if( detected_new_record != 0 )
		{
			/* Add an unallocated partial item
			 */
			if( remaining_record_size != 0 )
			{
				if( libmsiecf_item_descriptor_initialize(
				     &item_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create item descriptor.",
					 function );

					goto on_error;
				}
				if( item_descriptor == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing item descriptor.",
					 function );

					goto on_error;
				}
				item_descriptor->type        = item_type;
				item_descriptor->record_size = record_size - remaining_record_size;
				item_descriptor->file_offset = file_offset - item_descriptor->record_size;
				item_descriptor->flags       = LIBMSIECF_ITEM_FLAG_RECOVERED
				                             | LIBMSIECF_ITEM_FLAG_PARTIAL;

#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: partial item at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
					 function,
					 file_offset - item_descriptor->record_size,
					 file_offset - item_descriptor->record_size );
				}
#endif
				if( libcdata_array_append_entry(
				     recovered_item_table,
				     &item_table_entry_index,
				     (intptr_t *) item_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append item descriptor to recovered item table.",
					 function );

					goto on_error;
				}
				last_item_descriptor = item_descriptor;
				item_descriptor      = NULL;

#if defined( HAVE_DEBUG_OUTPUT )
				number_of_partial_recovered_items++;
#endif
			}
			item_type             = new_item_type;
			remaining_record_size = 0;
		}
		if( remaining_record_size == 0 )
		{
			record_size = number_of_blocks * io_handle->block_size;

			result = libcdata_range_list_get_range_at_offset(
				  unallocated_block_list,
				  (uint64_t) file_offset,
				  &range_offset,
				  &range_size,
				  &value,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine if record offset range is unallocated.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				if( record_type != NULL )
				{
					libcnotify_printf(
					 "%s: found ",
					 function );

					if( result != 0 )
					{
						libcnotify_printf(
						 "unallocated " );
					}
					libcnotify_printf(
					 "%s record of size: %" PRIu32 " at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
					 function,
					 record_size,
					 file_offset,
					 file_offset );

					libcnotify_printf(
					 "\n" );
				}
			}
#endif
			if( item_type != LIBMSIECF_ITEM_TYPE_UNDEFINED )
			{
				/* Add an allocated item
				 */
				if( result == 0 )
				{
					if( libmsiecf_item_descriptor_initialize(
					     &item_descriptor,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_MEMORY,
						 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create item descriptor.",
						 function );

						goto on_error;
					}
					if( item_descriptor == NULL )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: missing item descriptor.",
						 function );

						goto on_error;
					}
					item_descriptor->type        = item_type;
					item_descriptor->file_offset = file_offset;
					item_descriptor->record_size = record_size;
					item_descriptor->flags       = 0;

					if( libcdata_array_append_entry(
					     item_table,
					     &item_table_entry_index,
					     (intptr_t *) item_descriptor,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
						 "%s: unable to append item descriptor to item table.",
						 function );

						goto on_error;
					}
					last_item_descriptor = item_descriptor;
					item_descriptor      = NULL;

					item_type = LIBMSIECF_ITEM_TYPE_UNDEFINED;
#if defined( HAVE_DEBUG_OUTPUT )
					record_type = NULL;

					number_of_items++;
#endif
				}
				/* Make sure the unallocated record is not partially overwritten
				 * by another record
				 */
				else
				{
					remaining_record_size = record_size;
				}
			}
		}
		if( remaining_record_size == 0 )
		{
			file_offset += (off64_t) record_size;
		}
		else
		{
			file_offset           += (size32_t) io_handle->block_size;
			remaining_record_size -= (size32_t) io_handle->block_size;

			/* Add an unallocated item
			 */
			if( remaining_record_size == 0 )
			{
				if( libmsiecf_item_descriptor_initialize(
				     &item_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create item descriptor.",
					 function );

					goto on_error;
				}
				if( item_descriptor == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing item descriptor.",
					 function );

					goto on_error;
				}
				item_descriptor->type        = item_type;
				item_descriptor->file_offset = file_offset - record_size;
				item_descriptor->record_size = record_size;
				item_descriptor->flags       = LIBMSIECF_ITEM_FLAG_RECOVERED;

				if( libcdata_array_append_entry(
				     recovered_item_table,
				     &item_table_entry_index,
				     (intptr_t *) item_descriptor,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append item descriptor to recovered item table.",
					 function );

					goto on_error;
				}
				last_item_descriptor = item_descriptor;
				item_descriptor      = NULL;

				item_type = LIBMSIECF_ITEM_TYPE_UNDEFINED;

#if defined( HAVE_DEBUG_OUTPUT )
				number_of_recovered_items++;

				record_type = NULL;
#endif
			}
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: found %d items.\n",
		 function,
		 number_of_items );

		libcnotify_printf(
		 "%s: recovered %d items (partial recovered items %d).\n",
		 function,
		 number_of_recovered_items + number_of_partial_recovered_items,
		 number_of_partial_recovered_items );

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( item_descriptor != NULL )
	{
		libmsiecf_item_descriptor_free(
		 &item_descriptor,
	 	 NULL );
	}
	return( -1 );
}

