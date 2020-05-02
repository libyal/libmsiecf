/*
 * Item functions
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

#include "libmsiecf_definitions.h"
#include "libmsiecf_item.h"
#include "libmsiecf_io_handle.h"
#include "libmsiecf_leak_values.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcthreads.h"
#include "libmsiecf_redirected_values.h"
#include "libmsiecf_url_values.h"

/* Creates an item
 * Make sure the value item is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_item_initialize(
     libmsiecf_item_t **item,
     libmsiecf_item_descriptor_t *item_descriptor,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_item_initialize";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid item value already set.",
		 function );

		return( -1 );
	}
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
	internal_item = memory_allocate_structure(
	                 libmsiecf_internal_item_t );

	if( internal_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create internal item.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_item,
	     0,
	     sizeof( libmsiecf_internal_item_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear internal item.",
		 function );

		memory_free(
		 internal_item );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_item->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	internal_item->item_descriptor = item_descriptor;

	*item = (libmsiecf_item_t *) internal_item;

	return( 1 );

on_error:
	if( internal_item != NULL )
	{
		memory_free(
		 internal_item );
	}
	return( -1 );
}

/* Frees an item
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_item_free(
     libmsiecf_item_t **item,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_item_free";
	int result                               = 1;

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( *item != NULL )
	{
		internal_item = (libmsiecf_internal_item_t *) *item;
		*item         = NULL;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_item->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
                /* The item_descriptor reference is freed elsewhere
		 */
		if( internal_item->value != NULL )
		{
			if( internal_item->free_value != NULL )
			{
				if( internal_item->free_value(
				     &( internal_item->value ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free item value.",
					 function );

					result = -1;
				}
			}
		}
		memory_free(
		 internal_item );
	}
	return( result );
}

/* Retrieves the type
 * Determines the item type if neccessary
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_item_get_type(
     libmsiecf_item_t *item,
     uint8_t *item_type,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_item_get_type";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) item;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( item_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item type.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_item->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*item_type = internal_item->item_descriptor->type;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_item->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the flags
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_item_get_flags(
     libmsiecf_item_t *item,
     uint8_t *item_flags,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_item_get_flags";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) item;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( item_flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item flags.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_item->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*item_flags = internal_item->item_descriptor->flags;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_item->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_item_get_offset(
     libmsiecf_item_t *item,
     off64_t *offset,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_item_get_offset";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) item;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_item->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*offset = internal_item->item_descriptor->file_offset;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_item->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the offset range
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_item_get_offset_range(
     libmsiecf_item_t *item,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error )
{
	libmsiecf_internal_item_t *internal_item = NULL;
	static char *function                    = "libmsiecf_item_get_offset_range";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libmsiecf_internal_item_t *) item;

	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_item->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	*offset = internal_item->item_descriptor->file_offset;
	*size   = (size64_t) internal_item->item_descriptor->record_size;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_item->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Reads the item values
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_internal_item_read_values(
     libmsiecf_internal_item_t *internal_item,
     libmsiecf_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	const char *item_type_string = NULL;
	static char *function        = "libmsiecf_internal_item_read_values";
	int result                   = 0;

	if( internal_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( internal_item->item_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid item - missing item descriptor.",
		 function );

		return( -1 );
	}
	switch( internal_item->item_descriptor->type )
	{
		case LIBMSIECF_ITEM_TYPE_LEAK:
			item_type_string = "leak";

			result = libmsiecf_leak_values_initialize(
			          (libmsiecf_leak_values_t **) &( internal_item->value ),
			          error );

			internal_item->free_value = (int (*)(intptr_t **, libcerror_error_t **)) &libmsiecf_leak_values_free;

			break;

		case LIBMSIECF_ITEM_TYPE_REDIRECTED:
			item_type_string = "redirected";

			result = libmsiecf_redirected_values_initialize(
			          (libmsiecf_redirected_values_t **) &( internal_item->value ),
			          error );

			internal_item->free_value = (int (*)(intptr_t **, libcerror_error_t **)) &libmsiecf_redirected_values_free;

			break;

		case LIBMSIECF_ITEM_TYPE_URL:
			item_type_string = "url";

			result = libmsiecf_url_values_initialize(
			          (libmsiecf_url_values_t **) &( internal_item->value ),
			          error );

			internal_item->free_value = (int (*)(intptr_t **, libcerror_error_t **)) &libmsiecf_url_values_free;

			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported item type: %" PRIu8 ".",
			 function,
			 internal_item->item_descriptor->type );

			goto on_error;
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create %s values.",
		 function,
		 item_type_string );

		goto on_error;
	}
	switch( internal_item->item_descriptor->type )
	{
		case LIBMSIECF_ITEM_TYPE_LEAK:
			result = libmsiecf_leak_values_read_file_io_handle(
			          (libmsiecf_leak_values_t *) internal_item->value,
			          file_io_handle,
			          internal_item->item_descriptor->file_offset,
			          internal_item->item_descriptor->record_size,
			          io_handle->ascii_codepage,
			          internal_item->item_descriptor->flags,
			          error );
			break;

		case LIBMSIECF_ITEM_TYPE_REDIRECTED:
			result = libmsiecf_redirected_values_read_file_io_handle(
			          (libmsiecf_redirected_values_t *) internal_item->value,
			          file_io_handle,
			          internal_item->item_descriptor->file_offset,
			          internal_item->item_descriptor->record_size,
			          io_handle->ascii_codepage,
			          internal_item->item_descriptor->flags,
			          error );
			break;

		case LIBMSIECF_ITEM_TYPE_URL:
			result = libmsiecf_url_values_read_file_io_handle(
			          (libmsiecf_url_values_t *) internal_item->value,
			          io_handle,
			          file_io_handle,
			          internal_item->item_descriptor->file_offset,
			          internal_item->item_descriptor->record_size,
			          internal_item->item_descriptor->flags,
			          error );
			break;
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read %s values at offset: %" PRIi64 ".",
		 function,
		 item_type_string,
		 internal_item->item_descriptor->file_offset );

		goto on_error;
	}
	return( 1 );

on_error:
	if( internal_item->value != NULL )
	{
		if( internal_item->free_value != NULL )
		{
			internal_item->free_value(
			 &( internal_item->value ),
			 NULL );
		}
		internal_item->free_value = NULL;
	}
	return( -1 );
}

