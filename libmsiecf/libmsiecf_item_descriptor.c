/*
 * Item descriptor functions
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

#include "libmsiecf_item_descriptor.h"
#include "libmsiecf_libcerror.h"

/* Creates an item descriptor
 * Make sure the value item_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_item_descriptor_initialize(
     libmsiecf_item_descriptor_t **item_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_item_descriptor_initialize";

	if( item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item descriptor.",
		 function );

		return( -1 );
	}
	if( *item_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid item descriptor value already set.",
		 function );

		return( -1 );
	}
	*item_descriptor = memory_allocate_structure(
	                    libmsiecf_item_descriptor_t );

	if( *item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create item descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *item_descriptor,
	     0,
	     sizeof( libmsiecf_item_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear item descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *item_descriptor != NULL )
	{
		memory_free(
		 *item_descriptor );

		*item_descriptor = NULL;
	}
	return( -1 );
}

/* Frees an item descriptor
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_item_descriptor_free(
     libmsiecf_item_descriptor_t **item_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_item_descriptor_free";

	if( item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item descriptor.",
		 function );

		return( -1 );
	}
	if( *item_descriptor != NULL )
	{
		memory_free(
		 *item_descriptor );

		*item_descriptor = NULL;
	}
	return( 1 );
}

