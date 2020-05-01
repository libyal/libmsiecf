/*
 * Input/Output (IO) handle
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

#if !defined( _LIBMSIECF_IO_HANDLE_H )
#define _LIBMSIECF_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcdata.h"
#include "libmsiecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern char *msiecf_file_signature;

typedef struct libmsiecf_io_handle libmsiecf_io_handle_t;

struct libmsiecf_io_handle
{
	/* The major version
	 */
	uint8_t major_version;

	/* The minor version
	 */
	uint8_t minor_version;

	/* The file size
	 */
	size64_t file_size;

	/* The data block size
	 */
	uint16_t block_size;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libmsiecf_io_handle_initialize(
     libmsiecf_io_handle_t **io_handle,
     libcerror_error_t **error );

int libmsiecf_io_handle_free(
     libmsiecf_io_handle_t **io_handle,
     libcerror_error_t **error );

int libmsiecf_io_handle_clear(
     libmsiecf_io_handle_t *io_handle,
     libcerror_error_t **error );

int libmsiecf_io_handle_read_hash_table(
     libcdata_array_t *hash_table,
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t hash_table_offset,
     libcerror_error_t **error );

int libmsiecf_io_handle_read_record_scan(
     libcdata_array_t *item_table,
     libcdata_array_t *recovered_item_table,
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcdata_range_list_t *unallocated_block_list,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_IO_HANDLE_H ) */

