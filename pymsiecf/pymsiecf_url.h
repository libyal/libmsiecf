/*
 * Python object wrapper of libmsiecf_item_t type LIBMSIECF_ITEM_TYPE_URL
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

#if !defined( _PYMSIECF_URL_H )
#define _PYMSIECF_URL_H

#include <common.h>
#include <types.h>

#include "pymsiecf_item.h"
#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern PyMethodDef pymsiecf_url_object_methods[];
extern PyTypeObject pymsiecf_url_type_object;

PyObject *pymsiecf_url_get_type(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_primary_time(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_primary_time_as_integer(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_secondary_time(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_secondary_time_as_integer(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_expiration_time(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_expiration_time_as_integer(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_last_checked_time(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_last_checked_time_as_integer(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_cached_file_size(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_cache_directory_index(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_number_of_hits(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_location(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_filename(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

PyObject *pymsiecf_url_get_data(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYMSIECF_URL_H ) */

