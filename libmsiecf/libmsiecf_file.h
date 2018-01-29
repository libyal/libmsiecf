/*
 * File functions
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

#if !defined( _LIBMSIECF_INTERNAL_FILE_H )
#define _LIBMSIECF_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include "libmsiecf_extern.h"
#include "libmsiecf_io_handle.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcdata.h"
#include "libmsiecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmsiecf_internal_file libmsiecf_internal_file_t;

struct libmsiecf_internal_file
{
	/* The IO handle
	 */
	libmsiecf_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The cache directory descriptors array
	 */
	libcdata_array_t *directory_array;

	/* The item descriptors array
	 */
	libcdata_array_t *item_array;

	/* The recovered item descriptors array
	 */
	libcdata_array_t *recovered_item_array;

	/* The unallocated block list
	 */
	libcdata_range_list_t *unallocated_block_list;
};

LIBMSIECF_EXTERN \
int libmsiecf_file_initialize(
     libmsiecf_file_t **file,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_free(
     libmsiecf_file_t **file,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_signal_abort(
     libmsiecf_file_t *file,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_open(
     libmsiecf_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBMSIECF_EXTERN \
int libmsiecf_file_open_wide(
     libmsiecf_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBMSIECF_EXTERN \
int libmsiecf_file_open_file_io_handle(
     libmsiecf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_close(
     libmsiecf_file_t *file,
     libcerror_error_t **error );

int libmsiecf_file_open_read(
     libmsiecf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_size(
     libmsiecf_file_t *file,
     size64_t *size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_ascii_codepage(
     libmsiecf_file_t *file,
     int *ascii_codepage,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_set_ascii_codepage(
     libmsiecf_file_t *file,
     int ascii_codepage,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_format_version(
     libmsiecf_file_t *file,
     uint8_t *major_version,
     uint8_t *minor_version,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_number_of_unallocated_blocks(
     libmsiecf_file_t *file,
     int *number_of_unallocated_blocks,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_unallocated_block(
     libmsiecf_file_t *file,
     int unallocated_block_index,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_number_of_cache_directories(
     libmsiecf_file_t *file,
     int *number_of_cache_directories,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_cache_directory_name(
     libmsiecf_file_t *file,
     int cache_directory_index,
     char *string,
     size_t string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_number_of_items(
     libmsiecf_file_t *file,
     int *number_of_items,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_item(
     libmsiecf_file_t *file,
     int item_index,
     libmsiecf_item_t **item,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_item_by_index(
     libmsiecf_file_t *file,
     int item_index,
     libmsiecf_item_t **item,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_number_of_recovered_items(
     libmsiecf_file_t *file,
     int *number_of_recovered_items,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_recovered_item(
     libmsiecf_file_t *file,
     int recovered_item_index,
     libmsiecf_item_t **recovered_item,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_file_get_recovered_item_by_index(
     libmsiecf_file_t *file,
     int recovered_item_index,
     libmsiecf_item_t **recovered_item,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_INTERNAL_FILE_H ) */

