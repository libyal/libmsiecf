/*
 * Item functions
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

#if !defined( _LIBMSIECF_ITEM_H )
#define _LIBMSIECF_ITEM_H

#include <common.h>
#include <types.h>

#include "libmsiecf_extern.h"
#include "libmsiecf_item_descriptor.h"
#include "libmsiecf_io_handle.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmsiecf_internal_item libmsiecf_internal_item_t;

struct libmsiecf_internal_item
{
	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The internal file
	 */
	libmsiecf_io_handle_t *io_handle;

	/* The item descriptor
	 */
        libmsiecf_item_descriptor_t *item_descriptor;

	/* The item value
	 */
        intptr_t *value;

	/* The item free value function
	 */
	int (*free_value)(
	       intptr_t **value,
	       libcerror_error_t **error );
};

int libmsiecf_item_initialize(
     libmsiecf_item_t **item,
     libbfio_handle_t *file_io_handle,
     libmsiecf_io_handle_t *io_handle,
     libmsiecf_item_descriptor_t *item_descriptor,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_item_free(
     libmsiecf_item_t **item,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_item_get_type(
     libmsiecf_item_t *item,
     uint8_t *item_type,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_item_get_flags(
     libmsiecf_item_t *item,
     uint8_t *item_flags,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_item_get_offset(
     libmsiecf_item_t *item,
     off64_t *offset,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_item_get_offset_range(
     libmsiecf_item_t *item,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error );

int libmsiecf_item_read_values(
     libmsiecf_internal_item_t *internal_item,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_ITEM_H ) */

