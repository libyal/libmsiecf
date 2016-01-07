/*
 * Python object definition of the items sequence and iterator
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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

#include "pymsiecf_file.h"
#include "pymsiecf_libcerror.h"
#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"
#include "pymsiecf_items.h"

PySequenceMethods pymsiecf_items_sequence_methods = {
	/* sq_length */
	(lenfunc) pymsiecf_items_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pymsiecf_items_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pymsiecf_items_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pymsiecf._items",
	/* tp_basicsize */
	sizeof( pymsiecf_items_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pymsiecf_items_free,
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
	&pymsiecf_items_sequence_methods,
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
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"internal pymsiecf items sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pymsiecf_items_iter,
	/* tp_iternext */
	(iternextfunc) pymsiecf_items_iternext,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
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
	(initproc) pymsiecf_items_init,
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

/* Creates a new items object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_items_new(
           pymsiecf_file_t *file_object,
           PyObject* (*get_item_by_index)(
                        pymsiecf_file_t *file_object,
                        int item_index ),
           int number_of_items )
{
	pymsiecf_items_t *pymsiecf_items = NULL;
	static char *function            = "pymsiecf_items_new";

	if( file_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file object.",
		 function );

		return( NULL );
	}
	if( get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get item by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the items values are initialized
	 */
	pymsiecf_items = PyObject_New(
	                  struct pymsiecf_items,
	                  &pymsiecf_items_type_object );

	if( pymsiecf_items == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize items.",
		 function );

		goto on_error;
	}
	if( pymsiecf_items_init(
	     pymsiecf_items ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize items.",
		 function );

		goto on_error;
	}
	pymsiecf_items->file_object       = file_object;
	pymsiecf_items->get_item_by_index = get_item_by_index;
	pymsiecf_items->number_of_items   = number_of_items;

	Py_IncRef(
	 (PyObject *) pymsiecf_items->file_object );

	return( (PyObject *) pymsiecf_items );

on_error:
	if( pymsiecf_items != NULL )
	{
		Py_DecRef(
		 (PyObject *) pymsiecf_items );
	}
	return( NULL );
}

/* Intializes an items object
 * Returns 0 if successful or -1 on error
 */
int pymsiecf_items_init(
     pymsiecf_items_t *pymsiecf_items )
{
	static char *function = "pymsiecf_items_init";

	if( pymsiecf_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( -1 );
	}
	/* Make sure the items values are initialized
	 */
	pymsiecf_items->file_object       = NULL;
	pymsiecf_items->get_item_by_index = NULL;
	pymsiecf_items->item_index        = 0;
	pymsiecf_items->number_of_items   = 0;

	return( 0 );
}

/* Frees an items object
 */
void pymsiecf_items_free(
      pymsiecf_items_t *pymsiecf_items )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pymsiecf_items_free";

	if( pymsiecf_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pymsiecf_items );

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
	if( pymsiecf_items->file_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pymsiecf_items->file_object );
	}
	ob_type->tp_free(
	 (PyObject*) pymsiecf_items );
}

/* The items len() function
 */
Py_ssize_t pymsiecf_items_len(
            pymsiecf_items_t *pymsiecf_items )
{
	static char *function = "pymsiecf_items_len";

	if( pymsiecf_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pymsiecf_items->number_of_items );
}

/* The items getitem() function
 */
PyObject *pymsiecf_items_getitem(
           pymsiecf_items_t *pymsiecf_items,
           Py_ssize_t item_index )
{
	PyObject *item_object = NULL;
	static char *function = "pymsiecf_items_getitem";

	if( pymsiecf_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( NULL );
	}
	if( pymsiecf_items->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( pymsiecf_items->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - invalid number of items.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pymsiecf_items->number_of_items ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	item_object = pymsiecf_items->get_item_by_index(
	               pymsiecf_items->file_object,
	               (int) item_index );

	return( item_object );
}

/* The items iter() function
 */
PyObject *pymsiecf_items_iter(
           pymsiecf_items_t *pymsiecf_items )
{
	static char *function = "pymsiecf_items_iter";

	if( pymsiecf_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pymsiecf_items );

	return( (PyObject *) pymsiecf_items );
}

/* The items iternext() function
 */
PyObject *pymsiecf_items_iternext(
           pymsiecf_items_t *pymsiecf_items )
{
	PyObject *item_object = NULL;
	static char *function = "pymsiecf_items_iternext";

	if( pymsiecf_items == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items.",
		 function );

		return( NULL );
	}
	if( pymsiecf_items->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( pymsiecf_items->item_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - invalid item index.",
		 function );

		return( NULL );
	}
	if( pymsiecf_items->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid items - invalid number of items.",
		 function );

		return( NULL );
	}
	if( pymsiecf_items->item_index >= pymsiecf_items->number_of_items )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	item_object = pymsiecf_items->get_item_by_index(
	               pymsiecf_items->file_object,
	               pymsiecf_items->item_index );

	if( item_object != NULL )
	{
		pymsiecf_items->item_index++;
	}
	return( item_object );
}

