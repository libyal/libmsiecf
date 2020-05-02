/*
 * Redirected values functions
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

#if !defined( _LIBMSIECF_REDIRECTED_VALUES_H )
#define _LIBMSIECF_REDIRECTED_VALUES_H

#include <common.h>
#include <types.h>

#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libfvalue.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmsiecf_redirected_values libmsiecf_redirected_values_t;

struct libmsiecf_redirected_values
{
	/* The location value
	 */
	libfvalue_value_t *location;
};

int libmsiecf_redirected_values_initialize(
     libmsiecf_redirected_values_t **redirected_values,
     libcerror_error_t **error );

int libmsiecf_redirected_values_free(
     libmsiecf_redirected_values_t **redirected_values,
     libcerror_error_t **error );

int libmsiecf_redirected_values_read_data(
     libmsiecf_redirected_values_t *redirected_values,
     const uint8_t *data,
     size_t data_size,
     int ascii_codepage,
     uint8_t item_flags,
     libcerror_error_t **error );

int libmsiecf_redirected_values_read_file_io_handle(
     libmsiecf_redirected_values_t *redirected_values,
     libbfio_handle_t *file_io_handle,
     off64_t record_offset,
     size32_t record_size,
     int ascii_codepage,
     uint8_t item_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_REDIRECTED_VALUES_H ) */

