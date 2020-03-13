/*
 * Export handle
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

#if !defined( _EXPORT_HANDLE_H )
#define _EXPORT_HANDLE_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "log_handle.h"
#include "msiecftools_libcerror.h"
#include "msiecftools_libmsiecf.h"

#if defined( __cplusplus )
extern "C" {
#endif

enum EXPORT_MODES
{
	EXPORT_MODE_ALL				= (int) 'a',
	EXPORT_MODE_ITEMS			= (int) 'i',
	EXPORT_MODE_RECOVERED			= (int) 'r'
};

typedef struct export_handle export_handle_t;

struct export_handle
{
	/* The export mode
	 */
	uint8_t export_mode;

	/* The libmsiecf input file
	 */
	libmsiecf_file_t *input_file;

	/* The ascii codepage
	 */
	int ascii_codepage;

	/* The format major version
	 */
	uint8_t major_version;

	/* The format minor version
	 */
	uint8_t minor_version;

	/* The notification output stream
	 */
	FILE *notify_stream;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int export_handle_initialize(
     export_handle_t **export_handle,
     libcerror_error_t **error );

int export_handle_free(
     export_handle_t **export_handle,
     libcerror_error_t **error );

int export_handle_signal_abort(
     export_handle_t *export_handle,
     libcerror_error_t **error );

int export_handle_set_export_mode(
     export_handle_t *export_handle,
     const system_character_t *string,
     libcerror_error_t **error );

int export_handle_set_ascii_codepage(
     export_handle_t *export_handle,
     const system_character_t *string,
     libcerror_error_t **error );

int export_handle_open(
     export_handle_t *export_handle,
     const system_character_t *filename,
     libcerror_error_t **error );

int export_handle_close(
     export_handle_t *export_handle,
     libcerror_error_t **error );

/* Item export functions
 */
int export_handle_export_item_leak(
     export_handle_t *export_handle,
     libmsiecf_item_t *item,
     log_handle_t *log_handle,
     libcerror_error_t **error );

int export_handle_export_item_redirected(
     export_handle_t *export_handle,
     libmsiecf_item_t *item,
     log_handle_t *log_handle,
     libcerror_error_t **error );

int export_handle_export_item_url(
     export_handle_t *export_handle,
     libmsiecf_item_t *item,
     log_handle_t *log_handle,
     libcerror_error_t **error );

int export_handle_export_item(
     export_handle_t *export_handle,
     libmsiecf_item_t *item,
     log_handle_t *log_handle,
     libcerror_error_t **error );

int export_handle_export_items(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error );

int export_handle_export_recovered_items(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error );

/* File export functions
 */
int export_handle_export_file(
     export_handle_t *export_handle,
     log_handle_t *log_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _EXPORT_HANDLE_H ) */

