/*
 * File functions
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
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include "libmsiecf_allocation_table.h"
#include "libmsiecf_cache_directory_table.h"
#include "libmsiecf_codepage.h"
#include "libmsiecf_debug.h"
#include "libmsiecf_definitions.h"
#include "libmsiecf_file_header.h"
#include "libmsiecf_io_handle.h"
#include "libmsiecf_item.h"
#include "libmsiecf_item_descriptor.h"
#include "libmsiecf_file.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcdata.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"
#include "libmsiecf_libcthreads.h"

#include "msiecf_file_header.h"

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_initialize(
     libmsiecf_file_t **file,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_initialize";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( *file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file value already set.",
		 function );

		return( -1 );
	}
	internal_file = memory_allocate_structure(
	                 libmsiecf_internal_file_t );

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_file,
	     0,
	     sizeof( libmsiecf_internal_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		memory_free(
		 internal_file );

		return( -1 );
	}
	if( libmsiecf_io_handle_initialize(
	     &( internal_file->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_file->read_write_lock ),
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
	*file = (libmsiecf_file_t *) internal_file;

	return( 1 );

on_error:
	if( internal_file != NULL )
	{
		if( internal_file->io_handle != NULL )
		{
			libmsiecf_io_handle_free(
			 &( internal_file->io_handle ),
			 NULL );
		}
		memory_free(
		 internal_file );
	}
	return( -1 );
}

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_free(
     libmsiecf_file_t **file,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_free";
	int result                               = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( *file != NULL )
	{
		internal_file = (libmsiecf_internal_file_t *) *file;

		if( internal_file->file_io_handle != NULL )
		{
			if( libmsiecf_file_close(
			     *file,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close file.",
				 function );

				result = -1;
			}
		}
		*file = NULL;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_file->read_write_lock ),
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
		if( libmsiecf_io_handle_free(
		     &( internal_file->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_file );
	}
	return( result );
}

/* Signals the libmsiecf file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_signal_abort(
     libmsiecf_file_t *file,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_signal_abort";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_file->io_handle->abort = 1;

	return( 1 );
}

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_open(
     libmsiecf_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle         = NULL;
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_open";
	size_t filename_length                   = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBMSIECF_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBMSIECF_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBMSIECF_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libmsiecf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %s.",
		 function,
		 filename );

		goto on_error;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		goto on_error;
	}
#endif
	internal_file->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		internal_file->file_io_handle_created_in_library = 0;

		goto on_error;
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_open_wide(
     libmsiecf_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle         = NULL;
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_open_wide";
	size_t filename_length                   = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBMSIECF_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBMSIECF_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBMSIECF_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libmsiecf_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %ls.",
		 function,
		 filename );

		goto on_error;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		goto on_error;
	}
#endif
	internal_file->file_io_handle_created_in_library = 1;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		internal_file->file_io_handle_created_in_library = 0;

		goto on_error;
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_open_file_io_handle(
     libmsiecf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_open_file_io_handle";
	uint8_t file_io_handle_opened_in_library = 0;
	int bfio_access_flags                    = 0;
	int file_io_handle_is_open               = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( internal_file->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - file IO handle already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBMSIECF_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBMSIECF_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBMSIECF_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBMSIECF_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( libmsiecf_internal_file_open_read(
	     internal_file,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		goto on_error;
	}
#endif
	internal_file->file_io_handle                   = file_io_handle;
	internal_file->file_io_handle_opened_in_library = file_io_handle_opened_in_library;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		internal_file->file_io_handle                   = NULL;
		internal_file->file_io_handle_opened_in_library = 0;

		goto on_error;
	}
#endif
	return( 1 );

on_error:
	if( file_io_handle_opened_in_library != 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
int libmsiecf_file_close(
     libmsiecf_file_t *file,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_close";
	int result                               = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_file->file_io_handle_created_in_library != 0 )
		{
			if( libmsiecf_debug_print_read_offsets(
			     internal_file->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );
			}
		}
	}
#endif
	if( internal_file->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_file->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_opened_in_library = 0;
	}
	if( internal_file->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_file->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_created_in_library = 0;
	}
	internal_file->file_io_handle = NULL;

	if( libmsiecf_io_handle_clear(
	     internal_file->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( internal_file->file_header != NULL )
	{
		if( libmsiecf_file_header_free(
		     &( internal_file->file_header ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file header.",
			 function );

			result = -1;
		}
	}
	if( internal_file->cache_directory_table != NULL )
	{
		if( libmsiecf_cache_directory_table_free(
		     &( internal_file->cache_directory_table ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free cache directory table.",
			 function );

			result = -1;
		}
	}
	if( internal_file->item_array != NULL )
	{
		if( libcdata_array_free(
		     &( internal_file->item_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libmsiecf_item_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free item array.",
			 function );

			result = -1;
		}
	}
	if( internal_file->recovered_item_array != NULL )
	{
		if( libcdata_array_free(
		     &( internal_file->recovered_item_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libmsiecf_item_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free recovered item array.",
			 function );

			result = -1;
		}
	}
	if( internal_file->unallocated_block_list != NULL )
	{
		if( libcdata_range_list_free(
		     &( internal_file->unallocated_block_list ),
		     NULL,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free unallocated block list.",
			 function );

			result = -1;
		}
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Opens a file for reading
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_internal_file_open_read(
     libmsiecf_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_internal_file_open_read";

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file->file_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - file header already set.",
		 function );

		return( -1 );
	}
	if( internal_file->cache_directory_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - cache directory table value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->item_array != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - item array already set.",
		 function );

		return( -1 );
	}
	if( internal_file->recovered_item_array != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - recovered item array already set.",
		 function );

		return( -1 );
	}
	if( internal_file->unallocated_block_list != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - unallocated block list already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading file header:\n" );
	}
#endif
	if( libmsiecf_file_header_initialize(
	     &( internal_file->file_header ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file handle.",
		 function );

		goto on_error;
	}
	if( libmsiecf_file_header_read_file_io_handle(
	     internal_file->file_header,
	     file_io_handle,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		goto on_error;
	}
	internal_file->io_handle->major_version = internal_file->file_header->major_version;
	internal_file->io_handle->minor_version = internal_file->file_header->minor_version;
	internal_file->io_handle->file_size     = internal_file->file_header->file_size;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading cache directory table:\n" );
	}
#endif
	if( libmsiecf_cache_directory_table_initialize(
	     &( internal_file->cache_directory_table ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create cache directory table.",
		 function );

		goto on_error;
	}
	if( libmsiecf_cache_directory_table_read_file_io_handle(
	     internal_file->cache_directory_table,
	     file_io_handle,
	     sizeof( msiecf_file_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read cache directory table.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading allocation table:\n" );
	}
#endif
	if( libcdata_range_list_initialize(
	     &( internal_file->unallocated_block_list ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create unallocated data block list.",
		 function );

		goto on_error;
	}
	if( libmsiecf_allocation_table_read(
	     internal_file->unallocated_block_list,
	     file_io_handle,
	     0x250,
	     internal_file->file_header->file_size,
	     0x4000,
	     internal_file->io_handle->block_size,
	     internal_file->file_header->number_of_blocks,
	     internal_file->file_header->blocks_allocated,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read allocation table.",
		 function );

		goto on_error;
	}
/* TODO
	if( ! ( ( ( io_handle->major_version == 4 )
	  &&      ( io_handle->minor_version == 7 ) )
	 ||     ( ( io_handle->major_version == 5 )
	  &&      ( io_handle->minor_version == 2 ) ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version.",
		 function );

		goto on_error;
	}
*/
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading hash table:\n" );
	}
#endif
	if( libcdata_array_initialize(
	     &( internal_file->item_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create item array.",
		 function );

		goto on_error;
	}
	if( libmsiecf_io_handle_read_hash_table(
	     internal_file->item_array,
	     internal_file->io_handle,
	     file_io_handle,
	     internal_file->file_header->hash_table_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read hash table.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Scanning for records:\n" );
	}
#endif
	if( libcdata_array_initialize(
	     &( internal_file->recovered_item_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create recovered item array.",
		 function );

		goto on_error;
	}
	if( libmsiecf_io_handle_read_record_scan(
	     internal_file->item_array,
	     internal_file->recovered_item_array,
	     internal_file->io_handle,
	     file_io_handle,
	     internal_file->file_header->hash_table_offset,
	     internal_file->unallocated_block_list,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to perform record scan.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( internal_file->recovered_item_array != NULL )
	{
		libcdata_array_free(
		 &( internal_file->recovered_item_array ),
		 (int (*)(intptr_t **, libcerror_error_t **)) &libmsiecf_item_descriptor_free,
		 NULL );
	}
	if( internal_file->item_array != NULL )
	{
		libcdata_array_free(
		 &( internal_file->item_array ),
		 (int (*)(intptr_t **, libcerror_error_t **)) &libmsiecf_item_descriptor_free,
		 NULL );
	}
	if( internal_file->unallocated_block_list != NULL )
	{
		libcdata_range_list_free(
		 &( internal_file->unallocated_block_list ),
		 NULL,
		 NULL );
	}
	if( internal_file->cache_directory_table != NULL )
	{
		libmsiecf_cache_directory_table_free(
		 &( internal_file->cache_directory_table ),
		 NULL );
	}
	if( internal_file->file_header != NULL )
	{
		libmsiecf_file_header_free(
		 &( internal_file->file_header ),
		 NULL );
	}
	return( -1 );
}

/* Retrieves the file size
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_size(
     libmsiecf_file_t *file,
     size64_t *size,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_get_size";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( internal_file->file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file header.",
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
	     internal_file->read_write_lock,
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
	*size = internal_file->file_header->file_size;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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

/* Retrieves the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_ascii_codepage(
     libmsiecf_file_t *file,
     int *ascii_codepage,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_get_ascii_codepage";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ascii_codepage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid ASCII codepage.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	*ascii_codepage = internal_file->io_handle->ascii_codepage;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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

/* Sets the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_set_ascii_codepage(
     libmsiecf_file_t *file,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_set_ascii_codepage";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( ascii_codepage != LIBMSIECF_CODEPAGE_ASCII )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_874 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_932 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_936 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_949 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_950 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_1250 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_1251 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_1252 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_1253 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_1254 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_1255 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_1256 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_1257 )
	 && ( ascii_codepage != LIBMSIECF_CODEPAGE_WINDOWS_1258 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported ASCII codepage.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	internal_file->io_handle->ascii_codepage = ascii_codepage;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_file->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_format_version(
     libmsiecf_file_t *file,
     uint8_t *major_version,
     uint8_t *minor_version,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_get_format_version";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( internal_file->file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file header.",
		 function );

		return( -1 );
	}
	if( major_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid major version.",
		 function );

		return( -1 );
	}
	if( minor_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid minor version.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	*major_version = internal_file->file_header->major_version;
	*minor_version = internal_file->file_header->minor_version;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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

/* Retrieves the number of unallocated blocks
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_number_of_unallocated_blocks(
     libmsiecf_file_t *file,
     int *number_of_unallocated_blocks,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_get_number_of_unallocated_blocks";
	int result                               = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	result = libcdata_range_list_get_number_of_elements(
	          internal_file->unallocated_block_list,
	          number_of_unallocated_blocks,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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
	return( result );
}

/* Retrieves a specific unallocated block
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_unallocated_block(
     libmsiecf_file_t *file,
     int unallocated_block_index,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	intptr_t *value                          = NULL;
	static char *function                    = "libmsiecf_file_get_unallocated_block";
	int result                               = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	result = libcdata_range_list_get_range_by_index(
	          internal_file->unallocated_block_list,
	          unallocated_block_index,
	          (uint64_t *) offset,
	          (uint64_t *) size,
	          &value,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve unallocated block range: %d.",
		 function,
		 unallocated_block_index );

		result = -1;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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
	return( result );
}

/* Retrieves the number of cache directories
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_number_of_cache_directories(
     libmsiecf_file_t *file,
     int *number_of_cache_directories,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_get_number_of_cache_directories";
	int result                               = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	result = libmsiecf_cache_directory_table_get_number_of_cache_directories(
	          internal_file->cache_directory_table,
	          number_of_cache_directories,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from directory array.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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
	return( result );
}

/* Retrieves the extended ASCII encoded name of a certain cache directory
 * The size should include the end of string character
 * The cache directory name consists of 8 characters + end of string character
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_cache_directory_name(
     libmsiecf_file_t *file,
     int cache_directory_index,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_get_cache_directory_name";
	int result                               = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	result = libmsiecf_cache_directory_table_get_directory_name_by_index(
	          internal_file->cache_directory_table,
	          cache_directory_index,
	          string,
	          string_size,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve cache directory: %d name.",
		 function,
		 cache_directory_index );

		result = -1;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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
	return( result );
}

/* Retrieves the number of items
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_number_of_items(
     libmsiecf_file_t *file,
     int *number_of_items,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_get_number_of_items";
	int result                               = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	result = libcdata_array_get_number_of_entries(
	          internal_file->item_array,
	          number_of_items,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from item array.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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
	return( result );
}

/* Retrieves the item for the specific index
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_item_by_index(
     libmsiecf_file_t *file,
     int item_index,
     libmsiecf_item_t **item,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file     = NULL;
	libmsiecf_item_descriptor_t *item_descriptor = NULL;
	static char *function                        = "libmsiecf_file_get_item_by_index";
	int result                               = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( internal_file->item_array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing item array.",
		 function );

		return( -1 );
	}
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
		 "%s: item already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	if( libcdata_array_get_entry_by_index(
	     internal_file->item_array,
	     item_index,
	     (intptr_t **) &item_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item descriptor.",
		 function );

		result = -1;
	}
	else if( libmsiecf_item_initialize(
	          item,
	          item_descriptor,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create item.",
		 function );

		result = -1;
	}
/* TODO make more error tollerant for corrupt items */
	else if( libmsiecf_internal_item_read_values(
	          (libmsiecf_internal_item_t *) *item,
	          internal_file->io_handle,
	          internal_file->file_io_handle,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read item values.",
		 function );

		libmsiecf_item_free(
		 item,
		 NULL );

		result = -1;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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
	return( result );
}

/* Retrieves the number of recovered items
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_number_of_recovered_items(
     libmsiecf_file_t *file,
     int *number_of_recovered_items,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file = NULL;
	static char *function                    = "libmsiecf_file_get_number_of_recovered_items";
	int result                               = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	result = libcdata_array_get_number_of_entries(
	          internal_file->recovered_item_array,
	          number_of_recovered_items,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements from recovered item array.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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
	return( result );
}

/* Retrieves the recovered item for the specific index
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_file_get_recovered_item_by_index(
     libmsiecf_file_t *file,
     int recovered_item_index,
     libmsiecf_item_t **recovered_item,
     libcerror_error_t **error )
{
	libmsiecf_internal_file_t *internal_file     = NULL;
	libmsiecf_item_descriptor_t *item_descriptor = NULL;
	static char *function                        = "libmsiecf_file_get_recovered_item_by_index";
	int result                               = 1;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (libmsiecf_internal_file_t *) file;

	if( internal_file->recovered_item_array == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing recovered item array.",
		 function );

		return( -1 );
	}
	if( recovered_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid recovered item.",
		 function );

		return( -1 );
	}
	if( *recovered_item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: recovered item already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_file->read_write_lock,
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
	if( libcdata_array_get_entry_by_index(
	     internal_file->recovered_item_array,
	     recovered_item_index,
	     (intptr_t **) &item_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve recovered item descriptor.",
		 function );

		result = -1;
	}
	else if( libmsiecf_item_initialize(
	          recovered_item,
	          item_descriptor,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create recovered item.",
		 function );

		result = -1;
	}
/* TODO make more error tollerant for corrupt items */
	else if( libmsiecf_internal_item_read_values(
	          (libmsiecf_internal_item_t *) *recovered_item,
	          internal_file->io_handle,
	          internal_file->file_io_handle,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read recovered item values.",
		 function );

		libmsiecf_item_free(
		 recovered_item,
		 NULL );

		result = -1;
	}
#if defined( HAVE_LIBMSIECF_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_file->read_write_lock,
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
	return( result );
}

