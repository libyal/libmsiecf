/*
 * Allocation table functions
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

#if !defined( _LIBMSIECF_ALLOCATION_TABLE_H )
#define _LIBMSIECF_ALLOCATION_TABLE_H

#include <common.h>
#include <types.h>

#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcdata.h"
#include "libmsiecf_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libmsiecf_allocation_table_read(
     libcdata_range_list_t *unallocated_block_list,
     libbfio_handle_t *file_io_handle,
     off64_t allocation_table_offset,
     size64_t file_size,
     off64_t base_offset,
     uint16_t block_size,
     uint32_t number_of_blocks,
     uint32_t blocks_allocated,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_ALLOCATION_TABLE_H ) */

