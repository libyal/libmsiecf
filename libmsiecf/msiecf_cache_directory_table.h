/*
 * The cache directory table definition of a MSIE Cache File
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

#if !defined( _MSIECF_CACHE_DIRECTORY_TABLE_H )
#define _MSIECF_CACHE_DIRECTORY_TABLE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct msiecf_cache_directory_table_header msiecf_cache_directory_table_header_t;

struct msiecf_cache_directory_table_header
{
	/* The number of cache directory entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_cache_directories[ 4 ];
};

typedef struct msiecf_cache_directory_entry msiecf_cache_directory_entry_t;

struct msiecf_cache_directory_entry
{
	/* The number of cached files in the directory
	 * Consists of 4 bytes
	 */
	uint8_t number_of_cached_files[ 4 ];

	/* The directory name
	 * Consists of 8 bytes
	 */
	uint8_t name[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MSIECF_CACHE_DIRECTORY_TABLE_H ) */

