/*
 * Python object definition of the libmsiecf URL item types
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

#if !defined( _PYMSIECF_URL_TYPES_H )
#define _PYMSIECF_URL_TYPES_H

#include <common.h>
#include <types.h>

#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pymsiecf_url_types pymsiecf_url_types_t;

struct pymsiecf_url_types
{
	/* Python object initialization
	 */
	PyObject_HEAD
};

extern PyTypeObject pymsiecf_url_types_type_object;

int pymsiecf_url_types_init_type(
     PyTypeObject *type_object );

PyObject *pymsiecf_url_types_new(
           void );

int pymsiecf_url_types_init(
     pymsiecf_url_types_t *pymsiecf_url_types );

void pymsiecf_url_types_free(
      pymsiecf_url_types_t *pymsiecf_url_types );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYMSIECF_URL_TYPES_H ) */

