/*
 * The internal type definitions
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

#if !defined( _LIBMSIECF_INTERNAL_TYPES_H )
#define _LIBMSIECF_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBMSIECF for local use of libmsiecf
 * The definitions in <libmsiecf/types.h> are copied here
 * for local use of libmsiecf
 */
#if defined( HAVE_LOCAL_LIBMSIECF )

/* The following type definitions hide internal data structures
 */
#if defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI )
typedef struct libmsiecf_file {}	libmsiecf_file_t;
typedef struct libmsiecf_item {}	libmsiecf_item_t;

#else
typedef intptr_t libmsiecf_file_t;
typedef intptr_t libmsiecf_item_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBMSIECF ) */

#endif /* !defined( _LIBMSIECF_INTERNAL_TYPES_H ) */

