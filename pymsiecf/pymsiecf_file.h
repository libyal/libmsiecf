/*
 * Python object wrapper of libmsiecf_file_t
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

#if !defined( _PYMSIECF_FILE_H )
#define _PYMSIECF_FILE_H

#include <common.h>
#include <types.h>

#include "pymsiecf_libbfio.h"
#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pymsiecf_file pymsiecf_file_t;

struct pymsiecf_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libmsiecf file
	 */
	libmsiecf_file_t *file;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pymsiecf_file_object_methods[];
extern PyTypeObject pymsiecf_file_type_object;

int pymsiecf_file_init(
     pymsiecf_file_t *pymsiecf_file );

void pymsiecf_file_free(
      pymsiecf_file_t *pymsiecf_file );

PyObject *pymsiecf_file_signal_abort(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

PyObject *pymsiecf_file_open(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymsiecf_file_open_file_object(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymsiecf_file_close(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

PyObject *pymsiecf_file_get_size(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

PyObject *pymsiecf_file_get_ascii_codepage(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

int pymsiecf_file_set_ascii_codepage_from_string(
     pymsiecf_file_t *pymsiecf_file,
     const char *codepage_string );

PyObject *pymsiecf_file_set_ascii_codepage(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords );

int pymsiecf_file_set_ascii_codepage_setter(
     pymsiecf_file_t *pymsiecf_file,
     PyObject *string_object,
     void *closure );

PyObject *pymsiecf_file_get_format_version(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

PyObject *pymsiecf_file_get_number_of_cache_directories(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

PyObject *pymsiecf_file_get_cache_directory_by_index(
           PyObject *pymsiecf_file,
           int cache_directory_index );

PyObject *pymsiecf_file_get_cache_directory(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymsiecf_file_get_cache_directories(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

PyObject *pymsiecf_file_get_number_of_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

PyObject *pymsiecf_file_get_item_by_index(
           PyObject *pymsiecf_file,
           int item_index );

PyObject *pymsiecf_file_get_item(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymsiecf_file_get_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

PyObject *pymsiecf_file_get_number_of_recovered_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

PyObject *pymsiecf_file_get_recovered_item_by_index(
           PyObject *pymsiecf_file,
           int item_index );

PyObject *pymsiecf_file_get_recovered_item(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pymsiecf_file_get_recovered_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYMSIECF_FILE_H ) */

