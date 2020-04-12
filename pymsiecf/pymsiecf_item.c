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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pymsiecf_error.h"
#include "pymsiecf_integer.h"
#include "pymsiecf_item.h"
#include "pymsiecf_libcerror.h"
#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"
#include "pymsiecf_unused.h"

PyMethodDef pymsiecf_item_object_methods[] = {

	{ "get_offset",
	  (PyCFunction) pymsiecf_item_get_offset,
	  METH_NOARGS,
	  "get_offset() -> Integer\n"
	  "\n"
	  "Retrieves the offset." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pymsiecf_item_object_get_set_definitions[] = {

	{ "offset",
	  (getter) pymsiecf_item_get_offset,
	  (setter) 0,
	  "The offset.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pymsiecf_item_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pymsiecf.item",
	/* tp_basicsize */
	sizeof( pymsiecf_item_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pymsiecf_item_free,
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
	"pymsiecf item object (wraps libmsiecf_item_t)",
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
	pymsiecf_item_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pymsiecf_item_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pymsiecf_item_init,
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

/* Creates a new item object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_item_new(
           PyTypeObject *type_object,
           libmsiecf_item_t *item,
           PyObject *parent_object )
{
	pymsiecf_item_t *pymsiecf_item = NULL;
	static char *function          = "pymsiecf_item_new";

	if( item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pymsiecf_item = PyObject_New(
	                 struct pymsiecf_item,
	                 type_object );

	if( pymsiecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize item.",
		 function );

		goto on_error;
	}
	pymsiecf_item->item          = item;
	pymsiecf_item->parent_object = parent_object;

	if( pymsiecf_item->parent_object != NULL )
	{
		Py_IncRef(
		 pymsiecf_item->parent_object );
	}
	return( (PyObject *) pymsiecf_item );

on_error:
	if( pymsiecf_item != NULL )
	{
		Py_DecRef(
		 (PyObject *) pymsiecf_item );
	}
	return( NULL );
}

/* Intializes an item object
 * Returns 0 if successful or -1 on error
 */
int pymsiecf_item_init(
     pymsiecf_item_t *pymsiecf_item )
{
	static char *function = "pymsiecf_item_init";

	if( pymsiecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	/* Make sure libmsiecf item is set to NULL
	 */
	pymsiecf_item->item = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of item not supported.",
	 function );

	return( -1 );
}

/* Frees an item object
 */
void pymsiecf_item_free(
      pymsiecf_item_t *pymsiecf_item )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pymsiecf_item_free";
	int result                  = 0;

	if( pymsiecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pymsiecf_item );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pymsiecf_item->item != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libmsiecf_item_free(
		          &( pymsiecf_item->item ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pymsiecf_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libmsiecf item.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pymsiecf_item->parent_object != NULL )
	{
		Py_DecRef(
		 pymsiecf_item->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pymsiecf_item );
}

/* Retrieves the offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_item_get_offset(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_item_get_offset";
	off64_t offset           = 0;
	int result               = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_item_get_offset(
	          pymsiecf_item->item,
	          &offset,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = pymsiecf_integer_signed_new_from_64bit(
	                  (int64_t) offset );

	return( integer_object );
}

