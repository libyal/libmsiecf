/*
 * Redirected item functions
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

#if !defined( _LIBMSIECF_REDIRECTED_H )
#define _LIBMSIECF_REDIRECTED_H

#include <common.h>
#include <types.h>

#include "libmsiecf_extern.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_location_size(
     libmsiecf_item_t *redirected,
     size_t *string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_location(
     libmsiecf_item_t *redirected,
     char *string,
     size_t string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_utf8_location_size(
     libmsiecf_item_t *redirected,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_utf8_location(
     libmsiecf_item_t *redirected,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_utf16_location_size(
     libmsiecf_item_t *redirected,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_utf16_location(
     libmsiecf_item_t *redirected,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_REDIRECTED_H ) */

