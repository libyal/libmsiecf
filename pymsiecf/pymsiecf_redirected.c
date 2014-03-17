/*
 * Python object definition of the libmsiecf redirected item
 *
 * Copyright (C) 2009-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pymsiecf_error.h"
#include "pymsiecf_item.h"
#include "pymsiecf_libcerror.h"
#include "pymsiecf_libcstring.h"
#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"
#include "pymsiecf_redirected.h"
#include "pymsiecf_unused.h"

PyMethodDef pymsiecf_redirected_object_methods[] = {

	/* Functions to access the redirected values */

	{ "get_location",
	  (PyCFunction) pymsiecf_redirected_get_location,
	  METH_NOARGS,
	  "get_location() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the location." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pymsiecf_redirected_object_get_set_definitions[] = {

	{ "location",
	  (getter) pymsiecf_redirected_get_location,
	  (setter) 0,
	  "The location.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pymsiecf_redirected_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pymsiecf.redirected",
	/* tp_basicsize */
	sizeof( pymsiecf_item_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	0,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
        /* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pymsiecf redirected object (wraps libmsiecf_item_t type LIBMSIECF_ITEM_TYPE_REDIRECTED)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pymsiecf_redirected_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pymsiecf_redirected_object_get_set_definitions,
	/* tp_base */
	&pymsiecf_item_type_object,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	0,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Retrieves the location
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_redirected_get_location(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	const char *errors       = NULL;
	uint8_t *location        = NULL;
	static char *function    = "pymsiecf_redirected_get_location";
	size_t location_size     = 0;
	int result               = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_redirected_get_utf8_location_size(
	          pymsiecf_item->item,
	          &location_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve location size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( location_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	location = (uint8_t *) PyMem_Malloc(
	                        sizeof( uint8_t ) * location_size );

	if( location == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create location.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_redirected_get_utf8_location(
		  pymsiecf_item->item,
		  location,
		  location_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve location.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) location,
			 (Py_ssize_t) location_size - 1,
			 errors );

	PyMem_Free(
	 location );

	return( string_object );

on_error:
	if( location != NULL )
	{
		PyMem_Free(
		 location );
	}
	return( NULL );
}

