/*
 * Python object definition of the libmsiecf item types
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

#if !defined( _PYMSIECF_ITEM_TYPES_H )
#define _PYMSIECF_ITEM_TYPES_H

#include <common.h>
#include <types.h>

#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pymsiecf_item_types pymsiecf_item_types_t;

struct pymsiecf_item_types
{
	/* Python object initialization
	 */
	PyObject_HEAD
};

extern PyTypeObject pymsiecf_item_types_type_object;

int pymsiecf_item_types_init_type(
     PyTypeObject *type_object );

PyObject *pymsiecf_item_types_new(
           void );

int pymsiecf_item_types_init(
     pymsiecf_item_types_t *definitions_object );

void pymsiecf_item_types_free(
      pymsiecf_item_types_t *definitions_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYMSIECF_ITEM_TYPES_H ) */

