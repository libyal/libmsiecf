/*
 * Cache directory table functions
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

#if !defined( _LIBMSIECF_CACHE_DIRECTORY_TABLE_H )
#define _LIBMSIECF_CACHE_DIRECTORY_TABLE_H

#include <common.h>
#include <types.h>

#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcdata.h"
#include "libmsiecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmsiecf_cache_directory_table libmsiecf_cache_directory_table_t;

struct libmsiecf_cache_directory_table
{
	/* The directory descriptor array
	 */
	libcdata_array_t *directory_descriptor_array;
};

int libmsiecf_cache_directory_table_initialize(
     libmsiecf_cache_directory_table_t **cache_directory_table,
     libcerror_error_t **error );

int libmsiecf_cache_directory_table_free(
     libmsiecf_cache_directory_table_t **cache_directory_table,
     libcerror_error_t **error );

int libmsiecf_cache_directory_table_read_data(
     libmsiecf_cache_directory_table_t *cache_directory_table,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libmsiecf_cache_directory_table_read_file_io_handle(
     libmsiecf_cache_directory_table_t *cache_directory_table,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libmsiecf_cache_directory_table_get_number_of_cache_directories(
     libmsiecf_cache_directory_table_t *cache_directory_table,
     int *number_of_cache_directories,
     libcerror_error_t **error );

int libmsiecf_cache_directory_table_get_directory_name_by_index(
     libmsiecf_cache_directory_table_t *cache_directory_table,
     int cache_directory_index,
     char *string,
     size_t string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_CACHE_DIRECTORY_TABLE_H ) */

