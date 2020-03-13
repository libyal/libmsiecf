/*
 * Python object definition of the sequence and iterator object of cache directories
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

#if !defined( _PYMSIECF_CACHE_DIRECTORIES_H )
#define _PYMSIECF_CACHE_DIRECTORIES_H

#include <common.h>
#include <types.h>

#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pymsiecf_cache_directories pymsiecf_cache_directories_t;

struct pymsiecf_cache_directories
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get cache directory by index callback function
	 */
	PyObject* (*get_cache_directory_by_index)(
	             PyObject *parent_object,
	             int cache_directory_index );

	/* The (current) cache directory index
	 */
	int cache_directory_index;

	/* The number of cache directories
	 */
	int number_of_cache_directories;
};

extern PyTypeObject pymsiecf_cache_directories_type_object;

PyObject *pymsiecf_cache_directories_new(
           PyObject *parent_object,
           PyObject* (*get_cache_directory_by_index)(
                        PyObject *parent_object,
                        int cache_directory_index ),
           int number_of_cache_directories );

int pymsiecf_cache_directories_init(
     pymsiecf_cache_directories_t *pymsiecf_cache_directories );

void pymsiecf_cache_directories_free(
      pymsiecf_cache_directories_t *pymsiecf_cache_directories );

Py_ssize_t pymsiecf_cache_directories_len(
            pymsiecf_cache_directories_t *pymsiecf_cache_directories );

PyObject *pymsiecf_cache_directories_getitem(
           pymsiecf_cache_directories_t *pymsiecf_cache_directories,
           Py_ssize_t item_index );

PyObject *pymsiecf_cache_directories_iter(
           pymsiecf_cache_directories_t *pymsiecf_cache_directories );

PyObject *pymsiecf_cache_directories_iternext(
           pymsiecf_cache_directories_t *pymsiecf_cache_directories );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYMSIECF_CACHE_DIRECTORIES_H ) */

