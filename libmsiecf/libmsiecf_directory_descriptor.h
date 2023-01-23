/*
 * Cache directory descriptor functions
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMSIECF_DIRECTORY_DESCRIPTOR_H )
#define _LIBMSIECF_DIRECTORY_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libmsiecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmsiecf_directory_descriptor libmsiecf_directory_descriptor_t;

struct libmsiecf_directory_descriptor
{
	/* The directory name
	 */
	uint8_t *name[ 9 ];
};

int libmsiecf_directory_descriptor_initialize(
     libmsiecf_directory_descriptor_t **directory_descriptor,
     libcerror_error_t **error );

int libmsiecf_directory_descriptor_free(
     libmsiecf_directory_descriptor_t **directory_descriptor,
     libcerror_error_t **error );

int libmsiecf_directory_descriptor_read_data(
     libmsiecf_directory_descriptor_t *directory_descriptor,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_DIRECTORY_DESCRIPTOR_H ) */

