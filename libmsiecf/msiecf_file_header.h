/*
 * The file header definition of a MSIE Cache File
 *
 * Copyright (C) 2009-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _MSIECF_FILE_HEADER_H )
#define _MSIECF_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct msiecf_file_header msiecf_file_header_t;

struct msiecf_file_header
{
	/* Signature
	 * Consists of 28 bytes
	 * Contains: "Client UrlCache MMF Version #.#\x00"
	 * The # characters contain the version number
	 */
	uint8_t signature[ 28 ];

	/* File size
	 * Consists of 4 bytes
	 */
	uint8_t file_size[ 4 ];

	/* Hash table offset
	 * Consists of 4 bytes
	 */
	uint8_t hash_table_offset[ 4 ];

	/* Number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* Number of allocated blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_allocated_blocks[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* (Quota) limit of the size of the cache container
	 * Consists of 4 bytes
	 * Contains the number of bytes
	 */
	uint8_t cache_size_limit[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* (Current) size of the cache container
	 * Consists of 4 bytes
	 * Contains the number of bytes
	 */
	uint8_t cache_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Size of the cache container used by non-releasable files
	 * Consists of 4 bytes
	 * Contains the number of bytes
	 */
	uint8_t non_releasable_cache_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MSIECF_FILE_HEADER_H ) */

