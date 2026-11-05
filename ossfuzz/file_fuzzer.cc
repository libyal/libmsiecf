/*
 * OSS-Fuzz target for libmsiecf file type
 *
 * Copyright (C) 2009-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libmsiecf.h"

#if !defined( LIBMSIECF_HAVE_BFIO )

/* Determines if a file contains a MSIECF file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libmsiecf_error_t **error );

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_open_file_io_handle(
     libmsiecf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libmsiecf_error_t **error );

#endif /* !defined( LIBMSIECF_HAVE_BFIO ) */

/* Returns one of the codepages supported by libmsiecf_file_set_ascii_codepage
 * based on the first byte of the provided input
 */
int
fuzzing_supported_codepage(
     const uint8_t *data,
     size_t size )
{
	/* The values accepted by libmsiecf_file_set_ascii_codepage
	 */
	int codepages[15] = {
		LIBMSIECF_CODEPAGE_ASCII,
		LIBMSIECF_CODEPAGE_WINDOWS_874,
		LIBMSIECF_CODEPAGE_WINDOWS_932,
		LIBMSIECF_CODEPAGE_WINDOWS_936,
		LIBMSIECF_CODEPAGE_WINDOWS_949,
		LIBMSIECF_CODEPAGE_WINDOWS_950,
		LIBMSIECF_CODEPAGE_WINDOWS_1250,
		LIBMSIECF_CODEPAGE_WINDOWS_1251,
		LIBMSIECF_CODEPAGE_WINDOWS_1252,
		LIBMSIECF_CODEPAGE_WINDOWS_1253,
		LIBMSIECF_CODEPAGE_WINDOWS_1254,
		LIBMSIECF_CODEPAGE_WINDOWS_1255,
		LIBMSIECF_CODEPAGE_WINDOWS_1256,
		LIBMSIECF_CODEPAGE_WINDOWS_1257,
		LIBMSIECF_CODEPAGE_WINDOWS_1258 };

	if( size == 0 )
	{
		return( codepages[0] );
	}
	return( codepages[data[0] % 15] );
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	char cache_directory_name[16]    = {};
	char error_string[1024]          = {};
	libbfio_handle_t *file_io_handle = NULL;
	libmsiecf_file_t *file           = NULL;
	libmsiecf_item_t *item           = NULL;
	size64_t unallocated_block_size  = 0;
	off64_t unallocated_block_offset = 0;
	uint8_t major_version            = 0;
	uint8_t minor_version            = 0;
	int ascii_codepage               = 0;
	int number_of_cache_directories  = 0;
	int number_of_items              = 0;
	int number_of_recovered_items    = 0;
	int number_of_unallocated_blocks = 0;
	int index                        = 0;
	int result                       = 0;

	/* Test the library support functions
	 */
	libmsiecf_get_version();

	libmsiecf_get_access_flags_read();

	libmsiecf_get_codepage(
	  &ascii_codepage,
	  NULL );

	libmsiecf_get_codepage(
	  NULL,
	  NULL );

	/* 0x12345 is not a supported codepage
	 */
	libmsiecf_set_codepage(
	  0x12345,
	  NULL );

	ascii_codepage = fuzzing_supported_codepage(
	                 data,
	                 size );

	libmsiecf_set_codepage(
	  ascii_codepage,
	  NULL );

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libmsiecf_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	libmsiecf_check_file_signature_file_io_handle(
	 NULL,
	 NULL );

	if( file_io_handle != NULL )
	{
		libmsiecf_check_file_signature_file_io_handle(
		 file_io_handle,
		 NULL );
	}
	libmsiecf_file_get_size(
	 file,
	 NULL,
	 NULL );

	libmsiecf_file_get_ascii_codepage(
	 file,
	 NULL,
	 NULL );

	libmsiecf_file_get_format_version(
	 file,
	 NULL,
	 NULL,
	 NULL );

	libmsiecf_file_get_number_of_unallocated_blocks(
	 file,
	 NULL,
	 NULL );

	libmsiecf_file_get_unallocated_block(
	 file,
	 0,
	 NULL,
	 NULL,
	 NULL );

	libmsiecf_file_get_number_of_cache_directories(
	 file,
	 NULL,
	 NULL );

	libmsiecf_file_get_cache_directory_name(
	 file,
	 0,
	 NULL,
	 sizeof( cache_directory_name ),
	 NULL );

	libmsiecf_file_get_number_of_items(
	 file,
	 NULL,
	 NULL );

	libmsiecf_file_get_item_by_index(
	 file,
	 0,
	 NULL,
	 NULL );

	libmsiecf_file_get_number_of_recovered_items(
	 file,
	 NULL,
	 NULL );

	libmsiecf_file_get_recovered_item_by_index(
	 file,
	 0,
	 NULL,
	 NULL );

	libmsiecf_file_signal_abort(
	 NULL,
	 NULL );

	libmsiecf_file_signal_abort(
	 file,
	 NULL );

	libmsiecf_file_open_file_io_handle(
	 NULL,
	 file_io_handle,
	 LIBMSIECF_OPEN_READ,
	 NULL );

	libmsiecf_file_open_file_io_handle(
	 file,
	 NULL,
	 LIBMSIECF_OPEN_READ,
	 NULL );

	libmsiecf_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 0,
	 NULL );

	/* LIBMSIECF_OPEN_READ_WRITE contains the unsupported write access flag
	 */
	libmsiecf_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 LIBMSIECF_OPEN_READ_WRITE,
	 NULL );

	libmsiecf_file_close(
	 NULL,
	 NULL );

	libmsiecf_file_close(
	 file,
	 NULL );

	/* Test the pre-open error path
	 */
	libmsiecf_file_get_size(
	 file,
	 &unallocated_block_size,
	 NULL );
	if( libmsiecf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBMSIECF_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libmsiecf;
	}
	/* Test the "file IO handle already set" error branch
	 */
	libmsiecf_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 LIBMSIECF_OPEN_READ,
	 NULL );

	/* Test the file functions with an opened file
	 */
	libmsiecf_file_get_size(
	 file,
	 NULL,
	 NULL );
	libmsiecf_file_get_ascii_codepage(
	 file,
	 NULL,
	 NULL );
	libmsiecf_file_get_format_version(
	 file,
	 NULL,
	 NULL,
	 NULL );
	libmsiecf_file_get_number_of_unallocated_blocks(
	 file,
	 NULL,
	 NULL );
	libmsiecf_file_get_unallocated_block(
	 file,
	 0,
	 NULL,
	 NULL,
	 NULL );
	libmsiecf_file_get_number_of_cache_directories(
	 file,
	 NULL,
	 NULL );
	libmsiecf_file_get_cache_directory_name(
	 file,
	 0,
	 NULL,
	 sizeof( cache_directory_name ),
	 NULL );
	libmsiecf_file_get_number_of_items(
	 file,
	 NULL,
	 NULL );
	libmsiecf_file_get_item_by_index(
	 file,
	 0,
	 NULL,
	 NULL );
	libmsiecf_file_get_number_of_recovered_items(
	 file,
	 NULL,
	 NULL );
	libmsiecf_file_get_recovered_item_by_index(
	 file,
	 0,
	 NULL,
	 NULL );

	libmsiecf_file_get_size(
	 file,
	 &unallocated_block_size,
	 NULL );
	libmsiecf_file_get_ascii_codepage(
	 file,
	 &ascii_codepage,
	 NULL );

	/* 0x12345 is not a supported codepage
	 */
	libmsiecf_file_set_ascii_codepage(
	 file,
	 0x12345,
	 NULL );

	ascii_codepage = fuzzing_supported_codepage(
	                 data,
	                 size );

	libmsiecf_file_set_ascii_codepage(
	 file,
	 ascii_codepage,
	 NULL );
	libmsiecf_file_get_ascii_codepage(
	 file,
	 &ascii_codepage,
	 NULL );
	libmsiecf_file_get_format_version(
	 file,
	 &major_version,
	 &minor_version,
	 NULL );
	libmsiecf_file_get_number_of_items(
	 file,
	 &number_of_items,
	 NULL );
	libmsiecf_file_get_number_of_recovered_items(
	 file,
	 &number_of_recovered_items,
	 NULL );

	if( number_of_items > 0 )
	{
		result = libmsiecf_file_get_item_by_index(
		          file,
		          0,
		          &item,
		          NULL );

		if( result == 1 )
		{
			libmsiecf_file_get_item_by_index(
			 file,
			 0,
			 &item,
			 NULL );

			libmsiecf_item_free(
			 &item,
			 NULL );
		}
	}
	result = libmsiecf_file_get_number_of_unallocated_blocks(
	        file,
	        &number_of_unallocated_blocks,
	        NULL );

	if( ( result == 1 )
	 && ( number_of_unallocated_blocks > 0 ) )
	{
		/* Iterate over a limited number of unallocated blocks
		 */
		for( index = 0;
		     index < number_of_unallocated_blocks && index < 64;
		     index += 1 )
		{
			libmsiecf_file_get_unallocated_block(
			 file,
			 index,
			 &unallocated_block_offset,
			 &unallocated_block_size,
			 NULL );
		}
		/* Test the out-of-range error branch
		 */
		if( number_of_unallocated_blocks < 2147483647 )
		{
			index = number_of_unallocated_blocks + 1;
		}
		else
		{
			index = 2147483646;
		}
		libmsiecf_file_get_unallocated_block(
		 file,
		 index,
		 &unallocated_block_offset,
		 &unallocated_block_size,
		 NULL );
	}
	result = libmsiecf_file_get_number_of_cache_directories(
	          file,
	          &number_of_cache_directories,
	          NULL );

	if( ( result == 1 )
	 && ( number_of_cache_directories > 0 ) )
	{
		/* Iterate over a limited number of cache directories
		 */
		for( index = 0;
		     index < number_of_cache_directories && index < 8;
		     index += 1 )
		{
			libmsiecf_file_get_cache_directory_name(
			 file,
			 index,
			 cache_directory_name,
			 sizeof( cache_directory_name ),
			 NULL );
		}
		/* Test the out-of-range error branch
		 */
		if( number_of_cache_directories < 2147483647 )
		{
			index = number_of_cache_directories + 1;
		}
		else
		{
			index = 2147483646;
		}
		libmsiecf_file_get_cache_directory_name(
		 file,
		 index,
		 cache_directory_name,
		 sizeof( cache_directory_name ),
		 NULL );
	}
	libmsiecf_file_signal_abort(
	 file,
	 NULL );

	libmsiecf_file_close(
	 file,
	 NULL );

on_error_libmsiecf:
	if( file != NULL )
	{
		libmsiecf_file_free(
		 &file,
		 NULL );
	}

on_error_libbfio:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

} /* extern "C" */
