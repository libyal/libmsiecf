/*
 * The LEAK record definition of a MSIE Cache File
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

#if !defined( _MSIECF_LEAK_RECORD_H )
#define _MSIECF_LEAK_RECORD_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct msiecf_leak_record_header msiecf_leak_record_header_t;

struct msiecf_leak_record_header
{
	/* Signature
	 * Consists of 4 bytes
	 * Contains: "LEAK"
	 */
	uint8_t signature[ 4 ];

	/* The number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* Unknown
	 * Consists of 24 bytes
	 * Contains uninitialized values
	 */
	uint8_t unknown1[ 24 ];

	/* Cached file size
	 * Consists of 4 bytes
	 */
	uint8_t cached_file_size[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 * Contains uninitialized values
	 */
	uint8_t unknown3[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 * Contains uninitialized values
	 */
	uint8_t unknown5[ 8 ];

	/* The cache directory index
	 * Consists of 1 byte
	 */
	uint8_t cache_directory_index;

	/* Unknown
	 * Consists of 3 bytes
	 * Contains uninitialized values
	 */
	uint8_t unknown7[ 3 ];

	/* Filename offset
	 * Consists of 4 bytes
	 */
	uint8_t filename_offset[ 4 ];

	/* Unknown
	 * Consists of 24 bytes
	 * Contains uninitialized values
	 */
	uint8_t unknown9[ 24 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown10[ 4 ];

	/* Unknown date and time
	 * Consists of 4 bytes
	 * Contains a FAT date time structure
	 */
	uint8_t unknown_time[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MSIECF_LEAK_RECORD_H ) */

