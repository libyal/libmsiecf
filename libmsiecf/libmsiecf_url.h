/*
 * URL item functions
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

#if !defined( _LIBMSIECF_URL_H )
#define _LIBMSIECF_URL_H

#include <common.h>
#include <types.h>

#include "libmsiecf_extern.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBMSIECF_EXTERN \
int libmsiecf_url_get_type(
     libmsiecf_item_t *url,
     uint8_t *url_item_type,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_primary_time(
     libmsiecf_item_t *url,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_secondary_time(
     libmsiecf_item_t *url,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_expiration_time(
     libmsiecf_item_t *url,
     uint64_t *expiration_time,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_last_checked_time(
     libmsiecf_item_t *url,
     uint32_t *fat_date_time,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_cached_file_size(
     libmsiecf_item_t *url,
     uint64_t *cached_file_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_cache_directory_index(
     libmsiecf_item_t *url,
     uint8_t *cache_directory_index,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_number_of_hits(
     libmsiecf_item_t *url,
     uint32_t *number_of_hits,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_location_size(
     libmsiecf_item_t *url,
     size_t *string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_location(
     libmsiecf_item_t *url,
     char *string,
     size_t string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf8_location_size(
     libmsiecf_item_t *url,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf8_location(
     libmsiecf_item_t *url,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf16_location_size(
     libmsiecf_item_t *url,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf16_location(
     libmsiecf_item_t *url,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_filename_size(
     libmsiecf_item_t *url,
     size_t *string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_filename(
     libmsiecf_item_t *url,
     char *string,
     size_t string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf8_filename_size(
     libmsiecf_item_t *url,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf8_filename(
     libmsiecf_item_t *url,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf16_filename_size(
     libmsiecf_item_t *url,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf16_filename(
     libmsiecf_item_t *url,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_data_size(
     libmsiecf_item_t *url,
     size_t *data_size,
     libcerror_error_t **error );

LIBMSIECF_EXTERN \
int libmsiecf_url_get_data(
     libmsiecf_item_t *url,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_URL_H ) */

