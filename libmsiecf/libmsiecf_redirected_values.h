/*
 * Redirected values functions
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

#if !defined( _LIBMSIECF_REDIRECTED_VALUES_H )
#define _LIBMSIECF_REDIRECTED_VALUES_H

#include <common.h>
#include <types.h>

#include "libmsiecf_io_handle.h"
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

int libmsiecf_redirected_values_read(
     libmsiecf_redirected_values_t *redirected_values,
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t redirected_offset,
     size32_t record_size,
     uint8_t item_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_REDIRECTED_VALUES_H ) */

