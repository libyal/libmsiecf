/*
 * Library to access the MSIE Cache File (index.dat) format.
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

#if !defined( _LIBMSIECF_H )
#define _LIBMSIECF_H

#include <libmsiecf/definitions.h>
#include <libmsiecf/codepage.h>
#include <libmsiecf/error.h>
#include <libmsiecf/extern.h>
#include <libmsiecf/features.h>
#include <libmsiecf/types.h>

#include <stdio.h>

#if defined( LIBMSIECF_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBMSIECF_EXTERN \
const char *libmsiecf_get_version(
             void );

/* Returns the access flags for reading
 */
LIBMSIECF_EXTERN \
int libmsiecf_get_access_flags_read(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_get_codepage(
     int *codepage,
     libmsiecf_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_set_codepage(
     int codepage,
     libmsiecf_error_t **error );

/* Determines if a file contains a MSIECF file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_check_file_signature(
     const char *filename,
     libmsiecf_error_t **error );

#if defined( LIBMSIECF_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a file contains a MSIECF file signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_check_file_signature_wide(
     const wchar_t *filename,
     libmsiecf_error_t **error );

#endif /* defined( LIBMSIECF_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBMSIECF_HAVE_BFIO )

/* Determines if a file contains a MSIECF file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libmsiecf_error_t **error );

#endif /* defined( LIBMSIECF_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBMSIECF_EXTERN \
void libmsiecf_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_notify_set_stream(
     FILE *stream,
     libmsiecf_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_notify_stream_open(
     const char *filename,
     libmsiecf_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_notify_stream_close(
     libmsiecf_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBMSIECF_EXTERN \
void libmsiecf_error_free(
      libmsiecf_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_error_fprint(
     libmsiecf_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * Returns the number of printed characters if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_error_sprint(
     libmsiecf_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_error_backtrace_fprint(
     libmsiecf_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * Returns the number of printed characters if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_error_backtrace_sprint(
     libmsiecf_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * File functions
 * ------------------------------------------------------------------------- */

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_initialize(
     libmsiecf_file_t **file,
     libmsiecf_error_t **error );

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_free(
     libmsiecf_file_t **file,
     libmsiecf_error_t **error );

/* Signals the libmsiecf file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_signal_abort(
     libmsiecf_file_t *file,
     libmsiecf_error_t **error );

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_open(
     libmsiecf_file_t *file,
     const char *filename,
     int access_flags,
     libmsiecf_error_t **error );

#if defined( LIBMSIECF_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_open_wide(
     libmsiecf_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libmsiecf_error_t **error );

#endif /* defined( LIBMSIECF_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBMSIECF_HAVE_BFIO )

/* Opens a MSIE File using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_open_file_io_handle(
     libmsiecf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libmsiecf_error_t **error );

#endif /* defined( LIBMSIECF_HAVE_BFIO ) */

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_close(
     libmsiecf_file_t *file,
     libmsiecf_error_t **error );

/* Retrieves the file size
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_size(
     libmsiecf_file_t *file,
     size64_t *size,
     libmsiecf_error_t **error );

/* Retrieves the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_ascii_codepage(
     libmsiecf_file_t *file,
     int *ascii_codepage,
     libmsiecf_error_t **error );

/* Sets the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_set_ascii_codepage(
     libmsiecf_file_t *file,
     int ascii_codepage,
     libmsiecf_error_t **error );

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_format_version(
     libmsiecf_file_t *file,
     uint8_t *major_version,
     uint8_t *minor_version,
     libmsiecf_error_t **error );

/* Retrieves the number of unallocated blocks
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_number_of_unallocated_blocks(
     libmsiecf_file_t *file,
     int *number_of_unallocated_blocks,
     libmsiecf_error_t **error );

/* Retrieves a specific unallocated block
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_unallocated_block(
     libmsiecf_file_t *file,
     int unallocated_block_index,
     off64_t *offset,
     size64_t *size,
     libmsiecf_error_t **error );

/* Retrieves the number of cache directories
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_number_of_cache_directories(
     libmsiecf_file_t *file,
     int *number_of_cache_directories,
     libmsiecf_error_t **error );

/* Retrieves the extended ASCII encoded name of a certain cache directory
 * The size should include the end of string character
 * The cache directory name consists of 8 characters + end of string character
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_cache_directory_name(
     libmsiecf_file_t *file,
     int cache_directory_index,
     char *string,
     size_t string_size,
     libmsiecf_error_t **error );

/* Retrieves the number of items
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_number_of_items(
     libmsiecf_file_t *file,
     int *number_of_items,
     libmsiecf_error_t **error );

/* Retrieves the item for the specific index
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_item_by_index(
     libmsiecf_file_t *file,
     int item_index,
     libmsiecf_item_t **item,
     libmsiecf_error_t **error );

/* Retrieves the number of recovered items
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_number_of_recovered_items(
     libmsiecf_file_t *file,
     int *number_of_recovered_items,
     libmsiecf_error_t **error );

/* Retrieves the recovered item for the specific index
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_file_get_recovered_item_by_index(
     libmsiecf_file_t *file,
     int recovered_item_index,
     libmsiecf_item_t **recovered_item,
     libmsiecf_error_t **error );

/* -------------------------------------------------------------------------
 * Item functions
 * ------------------------------------------------------------------------- */

/* Frees an item
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_item_free(
     libmsiecf_item_t **item,
     libmsiecf_error_t **error );

/* Retrieves the type
 * Determines the item type if neccessary
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_item_get_type(
     libmsiecf_item_t *item,
     uint8_t *item_type,
     libmsiecf_error_t **error );

/* Retrieves the flags
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_item_get_flags(
     libmsiecf_item_t *item,
     uint8_t *item_flags,
     libmsiecf_error_t **error );

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_item_get_offset(
     libmsiecf_item_t *item,
     off64_t *offset,
     libmsiecf_error_t **error );

/* Retrieves the offset range
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_item_get_offset_range(
     libmsiecf_item_t *item,
     off64_t *offset,
     size64_t *size,
     libmsiecf_error_t **error );

/* -------------------------------------------------------------------------
 * URL item functions
 * ------------------------------------------------------------------------- */

/* Retrieves the URL item type
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_type(
     libmsiecf_item_t *url,
     uint8_t *url_item_type,
     libmsiecf_error_t **error );

/* Retrieves the primary time
 * The returned time is a 64-bit version of a FILETIME value
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_primary_time(
     libmsiecf_item_t *url,
     uint64_t *filetime,
     libmsiecf_error_t **error );

/* Retrieves the secondary time
 * The returned time is a 64-bit version of a FILETIME value
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_secondary_time(
     libmsiecf_item_t *url,
     uint64_t *filetime,
     libmsiecf_error_t **error );

/* Retrieves the expiration time
 * The returned time is a 64-bit version of a FILETIME value in format version 4.7
 * The returned time is a 32-bit version of a FAT date time value in format version 5.2
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_expiration_time(
     libmsiecf_item_t *url,
     uint64_t *expiration_time,
     libmsiecf_error_t **error );

/* Retrieves the last checked time
 * The returned time is a 32-bit version of a FAT date time value
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_last_checked_time(
     libmsiecf_item_t *url,
     uint32_t *fat_date_time,
     libmsiecf_error_t **error );

/* Retrieves the cached file size
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_cached_file_size(
     libmsiecf_item_t *url,
     uint64_t *cached_file_size,
     libmsiecf_error_t **error );

/* Retrieves the cache directory index
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_cache_directory_index(
     libmsiecf_item_t *url,
     uint8_t *cache_directory_index,
     libmsiecf_error_t **error );

/* Retrieves the number of hits
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_number_of_hits(
     libmsiecf_item_t *url,
     uint32_t *number_of_hits,
     libmsiecf_error_t **error );

/* Retrieves the size of the location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_location_size(
     libmsiecf_item_t *url,
     size_t *string_size,
     libmsiecf_error_t **error );

/* Retrieves the location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_location(
     libmsiecf_item_t *url,
     char *string,
     size_t string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the UTF-8 encoded location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf8_location_size(
     libmsiecf_item_t *url,
     size_t *utf8_string_size,
     libmsiecf_error_t **error );

/* Retrieves the UTF-8 encoded location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf8_location(
     libmsiecf_item_t *url,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the UTF-16 encoded location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf16_location_size(
     libmsiecf_item_t *url,
     size_t *utf16_string_size,
     libmsiecf_error_t **error );

/* Retrieves the UTF-16 encoded location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf16_location(
     libmsiecf_item_t *url,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_filename_size(
     libmsiecf_item_t *url,
     size_t *string_size,
     libmsiecf_error_t **error );

/* Retrieves the filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_filename(
     libmsiecf_item_t *url,
     char *string,
     size_t string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf8_filename_size(
     libmsiecf_item_t *url,
     size_t *utf8_string_size,
     libmsiecf_error_t **error );

/* Retrieves the UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf8_filename(
     libmsiecf_item_t *url,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the UTF-16 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf16_filename_size(
     libmsiecf_item_t *url,
     size_t *utf16_string_size,
     libmsiecf_error_t **error );

/* Retrieves the UTF-16 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_utf16_filename(
     libmsiecf_item_t *url,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the data
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_data_size(
     libmsiecf_item_t *url,
     size_t *data_size,
     libmsiecf_error_t **error );

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_url_get_data(
     libmsiecf_item_t *url,
     uint8_t *data,
     size_t data_size,
     libmsiecf_error_t **error );

/* -------------------------------------------------------------------------
 * Redirected item functions
 * ------------------------------------------------------------------------- */

/* Retrieves the size of the location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_location_size(
     libmsiecf_item_t *redirected,
     size_t *string_size,
     libmsiecf_error_t **error );

/* Retrieves the location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_location(
     libmsiecf_item_t *redirected,
     char *string,
     size_t string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the UTF-8 encoded location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_utf8_location_size(
     libmsiecf_item_t *redirected,
     size_t *utf8_string_size,
     libmsiecf_error_t **error );

/* Retrieves the UTF-8 encoded location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_utf8_location(
     libmsiecf_item_t *redirected,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the UTF-16 encoded location
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_utf16_location_size(
     libmsiecf_item_t *redirected,
     size_t *utf16_string_size,
     libmsiecf_error_t **error );

/* Retrieves the UTF-16 encoded location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no location or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_redirected_get_utf16_location(
     libmsiecf_item_t *redirected,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libmsiecf_error_t **error );

/* -------------------------------------------------------------------------
 * Leak item functions
 * ------------------------------------------------------------------------- */

/* Retrieves the cached file size
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_leak_get_cached_file_size(
     libmsiecf_item_t *leak,
     uint64_t *cached_file_size,
     libmsiecf_error_t **error );

/* Retrieves the cache directory index
 * Returns 1 if successful or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_leak_get_cache_directory_index(
     libmsiecf_item_t *leak,
     uint8_t *cache_directory_index,
     libmsiecf_error_t **error );

/* Retrieves the size of the filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_leak_get_filename_size(
     libmsiecf_item_t *leak,
     size_t *string_size,
     libmsiecf_error_t **error );

/* Retrieves the filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_leak_get_filename(
     libmsiecf_item_t *leak,
     char *string,
     size_t string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_leak_get_utf8_filename_size(
     libmsiecf_item_t *leak,
     size_t *utf8_string_size,
     libmsiecf_error_t **error );

/* Retrieves the UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_leak_get_utf8_filename(
     libmsiecf_item_t *leak,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libmsiecf_error_t **error );

/* Retrieves the size of the UTF-16 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_leak_get_utf16_filename_size(
     libmsiecf_item_t *leak,
     size_t *utf16_string_size,
     libmsiecf_error_t **error );

/* Retrieves the UTF-16 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if no filename or -1 on error
 */
LIBMSIECF_EXTERN \
int libmsiecf_leak_get_utf16_filename(
     libmsiecf_item_t *leak,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libmsiecf_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_H ) */

