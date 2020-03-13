/*
 * Python object wrapper of libmsiecf_item_t
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

#if !defined( _PYMSIECF_ITEM_H )
#define _PYMSIECF_ITEM_H

#include <common.h>
#include <types.h>

#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pymsiecf_item pymsiecf_item_t;

struct pymsiecf_item
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libmsiecf item
	 */
	libmsiecf_item_t *item;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pymsiecf_item_object_methods[];
extern PyTypeObject pymsiecf_item_type_object;

PyObject *pymsiecf_item_new(
           PyTypeObject *type_object,
           libmsiecf_item_t *item,
           PyObject *parent_object );

int pymsiecf_item_init(
     pymsiecf_item_t *pymsiecf_item );

void pymsiecf_item_free(
      pymsiecf_item_t *pymsiecf_item );

PyObject *pymsiecf_item_get_offset(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYMSIECF_ITEM_H ) */

