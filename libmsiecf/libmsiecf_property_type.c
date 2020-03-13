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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libmsiecf_property_type.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* The visited URL property types
 * Class identifier:
 */
libmsiecf_property_type_t libmsiecf_visited_url_properties[ ] = {
	{ 0x0010, 0x001e, "",	"Page title" },

	{ 0x0015, 0x001e, "",	"Favicon URI" },
	{ 0x0016, 0x001e, "",	"File URI" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* Retrieves a string containing the property type identifier
 */
const char *libmsiecf_property_types_get_identifier(
             libmsiecf_property_type_t libmsiecf_property_types[],
             uint32_t entry_type,
             uint32_t value_type )
{
	int iterator = 0;

	if( value_type == 0x001f )
	{
		value_type = 0x001e;
	}
	else if( value_type == 0x101f )
	{
		value_type = 0x101e;
	}
	while( ( libmsiecf_property_types[ iterator ] ).entry_type != (uint32_t) -1 )
	{
		if( ( ( libmsiecf_property_types[ iterator ] ).entry_type == entry_type )
		 && ( ( libmsiecf_property_types[ iterator ] ).value_type == value_type ) )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libmsiecf_property_types[ iterator ] ).identifier );
}

/* Retrieves a string containing the property type identifier
 */
const char *libmsiecf_property_type_get_identifier(
	     const uint8_t *class_identifier,
	     uint32_t entry_type,
	     uint32_t value_type )
{
	if( class_identifier == NULL )
	{
		return( libmsiecf_property_types_get_identifier(
			 libmsiecf_visited_url_properties,
			 entry_type,
			 value_type ) );
	}
	return( "_UNKNOWN_" );
}

/* Retrieves a string containing the property type description
 */
const char *libmsiecf_property_types_get_description(
             libmsiecf_property_type_t libmsiecf_property_types[],
             uint32_t entry_type,
             uint32_t value_type )
{
	int iterator = 0;

	if( value_type == 0x001f )
	{
		value_type = 0x001e;
	}
	else if( value_type == 0x101f )
	{
		value_type = 0x101e;
	}
	while( ( libmsiecf_property_types[ iterator ] ).entry_type != (uint32_t) -1 )
	{
		if( ( ( libmsiecf_property_types[ iterator ] ).entry_type == entry_type )
		 && ( ( libmsiecf_property_types[ iterator ] ).value_type == value_type ) )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libmsiecf_property_types[ iterator ] ).description );
}

/* Retrieves a string containing the property type description
 */
const char *libmsiecf_property_type_get_description(
             const uint8_t *class_identifier,
             uint32_t entry_type,
             uint32_t value_type )
{
	if( class_identifier == NULL )
	{
		return( libmsiecf_property_types_get_description(
			 libmsiecf_visited_url_properties,
			 entry_type,
			 value_type ) );
	}
	return( "Unknown" );
}

#endif

