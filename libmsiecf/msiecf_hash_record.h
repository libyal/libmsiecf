/*
 * The HASH record definition of a MSIE Cache File
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

#if !defined( _MSIECF_HASH_RECORD_H )
#define _MSIECF_HASH_RECORD_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct msiecf_hash_record_header msiecf_hash_record_header_t;

struct msiecf_hash_record_header
{
	/* Signature
	 * Consists of 4 bytes
	 * Contains: "HASH"
	 */
	uint8_t signature[ 4 ];

	/* The number of blocks
	 * Consists of 4 bytes
	 */
	uint8_t number_of_blocks[ 4 ];

	/* The next hash record offset
	 * Consists of 4 bytes
	 */
	uint8_t next_offset[ 4 ];

	/* The hash record sequence number
	 * Consists of 4 bytes
	 */
	uint8_t sequence_number[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _MSIECF_HASH_RECORD_H ) */

