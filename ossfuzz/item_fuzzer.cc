/*
 * OSS-Fuzz target for libmsiecf item type
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

/* Exercises the getters of an item
 * Also exercises the "unsupported item type" branches
 * of the getters of non-matching item types
 */
void fuzzing_fuzz_item(
      libmsiecf_item_t *item )
{
	uint8_t data[8 * 1024]          = {};
	uint16_t utf16_string[4 * 1024] = {};
	char string[8 * 1024]           = {};
	size64_t size                   = 0;
	size_t value_size               = 0;
	off64_t offset                  = 0;
	uint8_t item_flags              = 0;
	uint8_t item_type               = 0;
	uint8_t value8                  = 0;
	uint32_t value32                = 0;
	uint64_t value64                = 0;

	libmsiecf_item_get_type(
	 item,
	 NULL,
	 NULL );

	libmsiecf_item_get_type(
	 item,
	 &item_type,
	 NULL );

	libmsiecf_item_get_flags(
	 item,
	 NULL,
	 NULL );

	libmsiecf_item_get_flags(
	 item,
	 &item_flags,
	 NULL );

	libmsiecf_item_get_offset(
	 item,
	 NULL,
	 NULL );

	libmsiecf_item_get_offset(
	 item,
	 &offset,
	 NULL );

	libmsiecf_item_get_offset_range(
	 item,
	 NULL,
	 NULL,
	 NULL );

	libmsiecf_item_get_offset_range(
	 item,
	 &offset,
	 &size,
	 NULL );

	libmsiecf_url_get_type(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_type(
	 item,
	 &value8,
	 NULL );

	libmsiecf_url_get_primary_time(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_primary_time(
	 item,
	 &value64,
	 NULL );

	libmsiecf_url_get_secondary_time(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_secondary_time(
	 item,
	 &value64,
	 NULL );

	libmsiecf_url_get_expiration_time(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_expiration_time(
	 item,
	 &value64,
	 NULL );

	libmsiecf_url_get_last_checked_time(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_last_checked_time(
	 item,
	 &value32,
	 NULL );

	libmsiecf_url_get_cached_file_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_cached_file_size(
	 item,
	 &value64,
	 NULL );

	libmsiecf_url_get_cache_directory_index(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_cache_directory_index(
	 item,
	 &value8,
	 NULL );

	libmsiecf_url_get_number_of_hits(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_number_of_hits(
	 item,
	 &value32,
	 NULL );

	libmsiecf_url_get_location_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_location_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_url_get_location(
	 item,
	 NULL,
	 sizeof( string ),
	 NULL );

	libmsiecf_url_get_location(
	 item,
	 string,
	 sizeof( string ),
	 NULL );

	libmsiecf_url_get_location(
	 item,
	 string,
	 1,
	 NULL );

	libmsiecf_url_get_utf8_location_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_utf8_location_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_url_get_utf8_location(
	 item,
	 NULL,
	 sizeof( data ),
	 NULL );

	libmsiecf_url_get_utf8_location(
	 item,
	 data,
	 sizeof( data ),
	 NULL );

	libmsiecf_url_get_utf8_location(
	 item,
	 data,
	 1,
	 NULL );

	libmsiecf_url_get_utf16_location_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_utf16_location_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_url_get_utf16_location(
	 item,
	 NULL,
	 sizeof( utf16_string ),
	 NULL );

	libmsiecf_url_get_utf16_location(
	 item,
	 utf16_string,
	 sizeof( utf16_string ),
	 NULL );

	libmsiecf_url_get_utf16_location(
	 item,
	 utf16_string,
	 1,
	 NULL );

	libmsiecf_url_get_filename_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_filename_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_url_get_filename(
	 item,
	 NULL,
	 sizeof( string ),
	 NULL );

	libmsiecf_url_get_filename(
	 item,
	 string,
	 sizeof( string ),
	 NULL );

	libmsiecf_url_get_filename(
	 item,
	 string,
	 1,
	 NULL );

	libmsiecf_url_get_utf8_filename_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_utf8_filename_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_url_get_utf8_filename(
	 item,
	 NULL,
	 sizeof( data ),
	 NULL );

	libmsiecf_url_get_utf8_filename(
	 item,
	 data,
	 sizeof( data ),
	 NULL );

	libmsiecf_url_get_utf8_filename(
	 item,
	 data,
	 1,
	 NULL );

	libmsiecf_url_get_utf16_filename_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_utf16_filename_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_url_get_utf16_filename(
	 item,
	 NULL,
	 sizeof( utf16_string ),
	 NULL );

	libmsiecf_url_get_utf16_filename(
	 item,
	 utf16_string,
	 sizeof( utf16_string ),
	 NULL );

	libmsiecf_url_get_utf16_filename(
	 item,
	 utf16_string,
	 1,
	 NULL );

	libmsiecf_url_get_data_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_url_get_data_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_url_get_data(
	 item,
	 NULL,
	 sizeof( data ),
	 NULL );

	libmsiecf_url_get_data(
	 item,
	 data,
	 sizeof( data ),
	 NULL );

	libmsiecf_url_get_data(
	 item,
	 data,
	 1,
	 NULL );

	libmsiecf_redirected_get_location_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_redirected_get_location_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_redirected_get_location(
	 item,
	 NULL,
	 sizeof( string ),
	 NULL );

	libmsiecf_redirected_get_location(
	 item,
	 string,
	 sizeof( string ),
	 NULL );

	libmsiecf_redirected_get_location(
	 item,
	 string,
	 1,
	 NULL );

	libmsiecf_redirected_get_utf8_location_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_redirected_get_utf8_location_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_redirected_get_utf8_location(
	 item,
	 NULL,
	 sizeof( data ),
	 NULL );

	libmsiecf_redirected_get_utf8_location(
	 item,
	 data,
	 sizeof( data ),
	 NULL );

	libmsiecf_redirected_get_utf8_location(
	 item,
	 data,
	 1,
	 NULL );

	libmsiecf_redirected_get_utf16_location_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_redirected_get_utf16_location_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_redirected_get_utf16_location(
	 item,
	 NULL,
	 sizeof( utf16_string ),
	 NULL );

	libmsiecf_redirected_get_utf16_location(
	 item,
	 utf16_string,
	 sizeof( utf16_string ),
	 NULL );

	libmsiecf_redirected_get_utf16_location(
	 item,
	 utf16_string,
	 1,
	 NULL );

	libmsiecf_leak_get_cached_file_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_leak_get_cached_file_size(
	 item,
	 &value64,
	 NULL );

	libmsiecf_leak_get_cache_directory_index(
	 item,
	 NULL,
	 NULL );

	libmsiecf_leak_get_cache_directory_index(
	 item,
	 &value8,
	 NULL );

	libmsiecf_leak_get_filename_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_leak_get_filename_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_leak_get_filename(
	 item,
	 NULL,
	 sizeof( string ),
	 NULL );

	libmsiecf_leak_get_filename(
	 item,
	 string,
	 sizeof( string ),
	 NULL );

	libmsiecf_leak_get_filename(
	 item,
	 string,
	 1,
	 NULL );

	libmsiecf_leak_get_utf8_filename_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_leak_get_utf8_filename_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_leak_get_utf8_filename(
	 item,
	 NULL,
	 sizeof( data ),
	 NULL );

	libmsiecf_leak_get_utf8_filename(
	 item,
	 data,
	 sizeof( data ),
	 NULL );

	libmsiecf_leak_get_utf8_filename(
	 item,
	 data,
	 1,
	 NULL );

	libmsiecf_leak_get_utf16_filename_size(
	 item,
	 NULL,
	 NULL );

	libmsiecf_leak_get_utf16_filename_size(
	 item,
	 &value_size,
	 NULL );

	libmsiecf_leak_get_utf16_filename(
	 item,
	 NULL,
	 sizeof( utf16_string ),
	 NULL );

	libmsiecf_leak_get_utf16_filename(
	 item,
	 utf16_string,
	 sizeof( utf16_string ),
	 NULL );

	libmsiecf_leak_get_utf16_filename(
	 item,
	 utf16_string,
	 1,
	 NULL );
}

/* Returns one of the codepages supported by libmsiecf_file_set_ascii_codepage
 * based on the first byte of the provided input
 */
int fuzzing_supported_codepage(
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
	libbfio_handle_t *file_io_handle = NULL;
	libmsiecf_file_t *file           = NULL;
	libmsiecf_item_t *item           = NULL;
	int ascii_codepage               = 0;
	int number_of_items              = 0;
	int number_of_recovered_items    = 0;
	int index                        = 0;
	int result                       = 0;

	libmsiecf_get_version();

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
	if( libmsiecf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBMSIECF_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libmsiecf_file;
	}
	/* Set a codepage before any of the item values are read
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
	 NULL,
	 NULL );

	if( libmsiecf_file_get_number_of_items(
	     file,
	     &number_of_items,
	     NULL ) != 1 )
	{
		goto on_error_libmsiecf_file;
	}
	for( index = 0;
	     index < number_of_items && index < 128;
	     index += 1 )
	{
		result = libmsiecf_file_get_item_by_index(
		          file,
		          index,
		          &item,
		          NULL );

		if( result == 1 )
		{
			libmsiecf_file_get_item_by_index(
			 file,
			 index,
			 &item,
			 NULL );

			fuzzing_fuzz_item(
			 item );

			libmsiecf_item_free(
			 &item,
			 NULL );
		}
	}
	/* Exercise the out-of-range error branch
	 */
	if( number_of_items < 2147483647 )
	{
		index = number_of_items + 1;
	}
	else
	{
		index = 2147483646;
	}
	libmsiecf_file_get_item_by_index(
	 file,
	 index,
	 &item,
	 NULL );

	result = libmsiecf_file_get_number_of_recovered_items(
	          file,
	          &number_of_recovered_items,
	          NULL );

	if( ( result == 1 )
	 && ( number_of_recovered_items > 0 ) )
	{
		result = libmsiecf_file_get_recovered_item_by_index(
		          file,
		          0,
		          &item,
		          NULL );

		if( result == 1 )
		{
			/* Exercise the "item already set" error branch
			 */
			libmsiecf_file_get_recovered_item_by_index(
			 file,
			 0,
			 &item,
			 NULL );

			fuzzing_fuzz_item(
			 item );

			libmsiecf_item_free(
			 &item,
			 NULL );
		}
	}
	libmsiecf_file_close(
	 file,
	 NULL );

on_error_libmsiecf_file:
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
