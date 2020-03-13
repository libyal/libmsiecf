/*
 * Property type functions
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

#if !defined( _LIBMSIECF_PROPERTY_TYPE_H )
#define _LIBMSIECF_PROPERTY_TYPE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_DEBUG_OUTPUT )

typedef struct libmsiecf_property_type libmsiecf_property_type_t;

struct libmsiecf_property_type
{
	/* The entry type
	 */
	uint32_t entry_type;

	/* The value type
	 */
	uint32_t value_type;

	/* The identifier
	 */
	const char *identifier;

	/* The description
	 */
	const char *description;
};

const char *libmsiecf_property_types_get_identifier(
             libmsiecf_property_type_t libmsiecf_property_types[],
             uint32_t entry_type,
             uint32_t value_type );

const char *libmsiecf_property_type_get_identifier(
             const uint8_t *class_identifier,
             uint32_t entry_type,
             uint32_t value_type );

const char *libmsiecf_property_types_get_description(
             libmsiecf_property_type_t libmsiecf_property_types[],
             uint32_t entry_type,
             uint32_t value_type );

const char *libmsiecf_property_type_get_description(
             const uint8_t *class_identifier,
             uint32_t entry_type,
             uint32_t value_type );

#endif

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_PROPERTY_TYPE_H ) */

