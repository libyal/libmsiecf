/*
 * File header functions
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

#if !defined( _LIBMSIECF_FILE_HEADER_H )
#define _LIBMSIECF_FILE_HEADER_H

#include <common.h>
#include <types.h>

#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmsiecf_file_header libmsiecf_file_header_t;

struct libmsiecf_file_header
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

	/* The hash table offset
	 */
	uint32_t hash_table_offset;

	/* The total number of blocks
	 */
	uint32_t number_of_blocks;

	/* The number of blocks that are allocated
	 */
	uint32_t blocks_allocated;
};

int libmsiecf_file_header_initialize(
     libmsiecf_file_header_t **file_header,
     libcerror_error_t **error );

int libmsiecf_file_header_free(
     libmsiecf_file_header_t **file_header,
     libcerror_error_t **error );

int libmsiecf_file_header_read_data(
     libmsiecf_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libmsiecf_file_header_read_file_io_handle(
     libmsiecf_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_FILE_HEADER_H ) */

