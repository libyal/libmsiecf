/*
 * URL values functions
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

#if !defined( _LIBMSIECF_URL_VALUES_H )
#define _LIBMSIECF_URL_VALUES_H

#include <common.h>
#include <types.h>

#include "libmsiecf_io_handle.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libfvalue.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmsiecf_url_values libmsiecf_url_values_t;

struct libmsiecf_url_values
{
	/* The (URL record) type
	 */
	uint8_t type;

	/* The primary date and time
	 * Contains a 64-bit version of a filetime
	 */
	uint64_t primary_time;

	/* The secondary date and time
	 * Contains a 64-bit version of a filetime
	 */
	uint64_t secondary_time;

	/* The expiration date and time
	 * Contains a 32-bit version of a filetime in format version 4.7
	 * Contains a 32-bit version of a FAT date time in format version 5.2
	 */
	uint64_t expiration_time;

	/* The last checked date and time
	 * Contains a 32-bit version of a FAT date time
	 */
	uint32_t last_checked_time;

	/* The cached file size
	 */
	uint32_t cached_file_size;

	/* The number of hits
	 */
	uint32_t number_of_hits;

	/* The cache directory index
	 */
	uint8_t cache_directory_index;

	/* The location string value
	 */
	libfvalue_value_t *location;

	/* The filename string value
	 */
	libfvalue_value_t *filename;

	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;
};

int libmsiecf_url_values_initialize(
     libmsiecf_url_values_t **url_values,
     libcerror_error_t **error );

int libmsiecf_url_values_free(
     libmsiecf_url_values_t **url_values,
     libcerror_error_t **error );

int libmsiecf_url_values_read_data(
     libmsiecf_url_values_t *url_values,
     libmsiecf_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     uint8_t item_flags,
     libcerror_error_t **error );

int libmsiecf_url_values_read_file_io_handle(
     libmsiecf_url_values_t *url_values,
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t url_record_offset,
     size32_t record_size,
     uint8_t item_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_URL_VALUES_H ) */

