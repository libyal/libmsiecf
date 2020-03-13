/*
 * The URL record definition of a MSIE Cache File
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

#if !defined( _MSIECF_URL_RECORD_H )
#define _MSIECF_URL_RECORD_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct msiecf_url_record_header_v47 msiecf_url_record_header_v47_t;

struct msiecf_url_record_header_v47
{
	/* Signature
	 * Consists of 4 bytes
	 * Contains: "URL "
	 */
	uint8_t signature[ 4 ];

	/* The number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* The secondary filetime value
	 * Consists of 8 bytes
	 * Contains a filetime structure
	 */
	uint8_t secondary_filetime[ 8 ];

	/* The primary filetime value
	 * Consists of 8 bytes
	 * Contains a filetime structure
	 */
	uint8_t primary_filetime[ 8 ];

	/* The date and time when the cached entry expires
	 * Consists of 8 bytes
	 * Contains a filetime structure
	 */
	uint8_t expiration_time[ 8 ];

	/* Cached file size
	 * Consists of 4 bytes
	 */
	uint8_t cached_file_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* The non-releasable time delta
	 * Consists of 4 bytes
	 * Contains a value in seconds
	 */
	uint8_t non_releasable_time_delta[ 4 ];

	/* Unknown offset
	 * Consists of 4 bytes
	 */
	uint8_t unknown_offset[ 4 ];

	/* location string offset
	 * Consists of 4 bytes
	 * Contains 0x0068
	 */
	uint8_t location_offset[ 4 ];

	/* The cache directory index
	 * Consists of 1 byte
	 */
	uint8_t cache_directory_index;

	/* Unknown
	 * Consists of 3 bytes
	 * Contains 0x00 0x10 0x10
	 */
	uint8_t unknown6[ 3 ];

	/* Filename offset
	 * Consists of 4 bytes
	 */
	uint8_t filename_offset[ 4 ];

	/* Cache entry flags
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_flags[ 4 ];

	/* The data offset
	 * Consists of 4 bytes
	 */
	uint8_t data_offset[ 4 ];

	/* The data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8[ 4 ];

	/* The last checked date and time
	 * Consists of 4 bytes
	 * Contains a FAT date time structure
	 */
	uint8_t last_checked_time[ 4 ];

	/* The number of hits
	 * Consists of 4 bytes
	 */
	uint8_t number_of_hits[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 4 ];

	/* unknown date and time
	 * Consists of 4 bytes
	 * Contains a FAT date time structure
	 */
	uint8_t unknown_time[ 4 ];
};

typedef struct msiecf_url_record_header_v52 msiecf_url_record_header_v52_t;

struct msiecf_url_record_header_v52
{
	/* Signature
	 * Consists of 4 bytes
	 * Contains: "URL "
	 */
	uint8_t signature[ 4 ];

	/* The number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* The secondary filetime value
	 * Consists of 8 bytes
	 * Contains a filetime structure
	 */
	uint8_t secondary_filetime[ 8 ];

	/* The primary filetime value
	 * Consists of 8 bytes
	 * Contains a filetime structure
	 */
	uint8_t primary_filetime[ 8 ];

	/* The date and time when the cached entry expires
	 * Consists of 4 bytes
	 * Contains a FAT date time structure
	 */
	uint8_t expiration_time[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Cached file size
	 * Consists of 4 bytes
	 */
	uint8_t cached_file_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* The non-releasable time delta
	 * Consists of 4 bytes
	 * Contains a value in seconds
	 */
	uint8_t non_releasable_time_delta[ 4 ];

	/* Unknown offset
	 * Consists of 4 bytes
	 */
	uint8_t unknown_offset[ 4 ];

	/* location string offset
	 * Consists of 4 bytes
	 * Contains 0x0068
	 */
	uint8_t location_offset[ 4 ];

	/* The cache directory index
	 * Consists of 1 byte
	 */
	uint8_t cache_directory_index;

	/* Unknown
	 * Consists of 3 bytes
	 * Contains 0x00 0x10 0x10
	 */
	uint8_t unknown6[ 3 ];

	/* Filename offset
	 * Consists of 4 bytes
	 */
	uint8_t filename_offset[ 4 ];

	/* Cache entry flags
	 * Consists of 4 bytes
	 */
	uint8_t cache_entry_flags[ 4 ];

	/* The data offset
	 * Consists of 4 bytes
	 */
	uint8_t data_offset[ 4 ];

	/* The data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8[ 4 ];

	/* The last checked date and time
	 * Consists of 4 bytes
	 * Contains a FAT date time structure
	 */
	uint8_t last_checked_time[ 4 ];

	/* The number of hits
	 * Consists of 4 bytes
	 */
	uint8_t number_of_hits[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 4 ];

	/* unknown date and time
	 * Consists of 4 bytes
	 * Contains a FAT date time structure
	 */
	uint8_t unknown_time[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MSIECF_URL_RECORD_H ) */

