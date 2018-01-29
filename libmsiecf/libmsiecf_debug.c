/*
 * Debug functions
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

#include <common.h>
#include <types.h>

#include "libmsiecf_debug.h"
#include "libmsiecf_definitions.h"
#include "libmsiecf_libbfio.h"
#include "libmsiecf_libcerror.h"
#include "libmsiecf_libcnotify.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the cache entry flags
 * Returns 1 if successful or -1 on error
 */
void libmsiecf_debug_print_cache_entry_flags(
      uint32_t cache_entry_flags )
{
	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_NORMAL ) != 0 )
	{
		libcnotify_printf(
		 "\tNormal cache entry (NORMAL_CACHE_ENTRY)\n" );
	}
	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_STABLE ) != 0 )
	{
		libcnotify_printf(
		 "\tStable cache entry (STABLE_CACHE_ENTRY)\n" );
	}
	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_STICKY ) != 0 )
	{
		libcnotify_printf(
		 "\tSticky cache entry (STICKY_CACHE_ENTRY)\n" );
	}
	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_EDITED ) != 0 )
	{
		libcnotify_printf(
		 "\tEdited cache entry (EDITED_CACHE_ENTRY)\n" );
	}
	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_TRACK_OFFLINE ) != 0 )
	{
		libcnotify_printf(
		 "\tTrack offline cache entry (TRACK_OFFLINE_CACHE_ENTRY)\n" );
	}
	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_TRACK_ONLINE ) != 0 )
	{
		libcnotify_printf(
		 "\tTrack online cache entry (TRACK_ONLINE_CACHE_ENTRY)\n" );
	}

	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_SPARSE ) != 0 )
	{
		libcnotify_printf(
		 "\tSparse cache entry (SPARSE_CACHE_ENTRY)\n" );
	}
	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_OCX ) != 0 )
	{
		libcnotify_printf(
		 "\tOLE Control Extension (OCX) cache entry (OCX_CACHE_ENTRY)\n" );
	}

	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_COOKIE ) != 0 )
	{
		libcnotify_printf(
		 "\tCookie cache entry (COOKIE_CACHE_ENTRY)\n" );
	}
	if( ( cache_entry_flags & LIBMSIECF_CACHE_ENTRY_FLAG_URLHISTORY ) != 0 )
	{
		libcnotify_printf(
		 "\tVisited link cache entry (URLHISTORY_CACHE_ENTRY)\n" );
	}
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int libmsiecf_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libmsiecf_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int number_of_offsets = 0;
	int offset_iterator   = 0;

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
	if( libbfio_handle_get_number_of_offsets_read(
	     file_io_handle,
	     &number_of_offsets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets read.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0;
	     offset_iterator < number_of_offsets;
	     offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 ( offset_iterator + 1 ) );

			return( -1 );
		}
		libcnotify_printf(
		 "%08" PRIi64 " ( 0x%08" PRIx64 " ) - %08" PRIi64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + size,
		 offset + size,
		 size );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif

