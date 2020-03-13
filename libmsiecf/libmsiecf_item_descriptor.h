/*
 * Item descriptor functions
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

#if !defined( _LIBMSIECF_ITEM_DESCRIPTOR_H )
#define _LIBMSIECF_ITEM_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libmsiecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmsiecf_item_descriptor libmsiecf_item_descriptor_t;

struct libmsiecf_item_descriptor
{
	/* The item type
	 */
	uint8_t type;

	/* The item record file offset
	 */
	off64_t file_offset;

	/* The item record size
	 */
	size32_t record_size;

	/* Item descriptor flags
	 */
	uint8_t flags;
};

int libmsiecf_item_descriptor_initialize(
     libmsiecf_item_descriptor_t **item_descriptor,
     libcerror_error_t **error );

int libmsiecf_item_descriptor_free(
     libmsiecf_item_descriptor_t **item_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_ITEM_DESCRIPTOR_H ) */

