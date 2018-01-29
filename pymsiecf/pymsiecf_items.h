/*
 * Python object definition of the sequence and iterator object of items
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

#if !defined( _PYMSIECF_ITEMS_H )
#define _PYMSIECF_ITEMS_H

#include <common.h>
#include <types.h>

#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pymsiecf_items pymsiecf_items_t;

struct pymsiecf_items
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pymsiecf_items_type_object;

PyObject *pymsiecf_items_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pymsiecf_items_init(
     pymsiecf_items_t *items_object );

void pymsiecf_items_free(
      pymsiecf_items_t *items_object );

Py_ssize_t pymsiecf_items_len(
            pymsiecf_items_t *items_object );

PyObject *pymsiecf_items_getitem(
           pymsiecf_items_t *items_object,
           Py_ssize_t item_index );

PyObject *pymsiecf_items_iter(
           pymsiecf_items_t *items_object );

PyObject *pymsiecf_items_iternext(
           pymsiecf_items_t *items_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYMSIECF_ITEMS_H ) */

