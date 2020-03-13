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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pymsiecf_cache_directories.h"
#include "pymsiecf_libcerror.h"
#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"

PySequenceMethods pymsiecf_cache_directories_sequence_methods = {
	/* sq_length */
	(lenfunc) pymsiecf_cache_directories_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pymsiecf_cache_directories_getitem,
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

PyTypeObject pymsiecf_cache_directories_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pymsiecf._cache_directories",
	/* tp_basicsize */
	sizeof( pymsiecf_cache_directories_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pymsiecf_cache_directories_free,
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
	&pymsiecf_cache_directories_sequence_methods,
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
	"pymsiecf internal sequence and iterator object of cache directories",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pymsiecf_cache_directories_iter,
	/* tp_iternext */
	(iternextfunc) pymsiecf_cache_directories_iternext,
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
	(initproc) pymsiecf_cache_directories_init,
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

/* Creates a new cache directories object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_cache_directories_new(
           PyObject *parent_object,
           PyObject* (*get_cache_directory_by_index)(
                        PyObject *parent_object,
                        int cache_directory_index ),
           int number_of_cache_directories )
{
	pymsiecf_cache_directories_t *pymsiecf_cache_directories = NULL;
	static char *function                                    = "pymsiecf_cache_directories_new";

	if( parent_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid parent object.",
		 function );

		return( NULL );
	}
	if( get_cache_directory_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get cache directory by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the cache directories values are initialized
	 */
	pymsiecf_cache_directories = PyObject_New(
	                              struct pymsiecf_cache_directories,
	                              &pymsiecf_cache_directories_type_object );

	if( pymsiecf_cache_directories == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize cache directories.",
		 function );

		goto on_error;
	}
	if( pymsiecf_cache_directories_init(
	     pymsiecf_cache_directories ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize cache directories.",
		 function );

		goto on_error;
	}
	pymsiecf_cache_directories->parent_object                = parent_object;
	pymsiecf_cache_directories->get_cache_directory_by_index = get_cache_directory_by_index;
	pymsiecf_cache_directories->number_of_cache_directories  = number_of_cache_directories;

	Py_IncRef(
	 (PyObject *) pymsiecf_cache_directories->parent_object );

	return( (PyObject *) pymsiecf_cache_directories );

on_error:
	if( pymsiecf_cache_directories != NULL )
	{
		Py_DecRef(
		 (PyObject *) pymsiecf_cache_directories );
	}
	return( NULL );
}

/* Intializes a cache directories object
 * Returns 0 if successful or -1 on error
 */
int pymsiecf_cache_directories_init(
     pymsiecf_cache_directories_t *pymsiecf_cache_directories )
{
	static char *function = "pymsiecf_cache_directories_init";

	if( pymsiecf_cache_directories == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories.",
		 function );

		return( -1 );
	}
	/* Make sure the cache directories values are initialized
	 */
	pymsiecf_cache_directories->parent_object                = NULL;
	pymsiecf_cache_directories->get_cache_directory_by_index = NULL;
	pymsiecf_cache_directories->cache_directory_index        = 0;
	pymsiecf_cache_directories->number_of_cache_directories  = 0;

	return( 0 );
}

/* Frees a cache directories object
 */
void pymsiecf_cache_directories_free(
      pymsiecf_cache_directories_t *pymsiecf_cache_directories )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pymsiecf_cache_directories_free";

	if( pymsiecf_cache_directories == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pymsiecf_cache_directories );

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
	if( pymsiecf_cache_directories->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pymsiecf_cache_directories->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pymsiecf_cache_directories );
}

/* The cache directories len() function
 */
Py_ssize_t pymsiecf_cache_directories_len(
            pymsiecf_cache_directories_t *pymsiecf_cache_directories )
{
	static char *function = "pymsiecf_cache_directories_len";

	if( pymsiecf_cache_directories == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pymsiecf_cache_directories->number_of_cache_directories );
}

/* The cache directories getitem() function
 */
PyObject *pymsiecf_cache_directories_getitem(
           pymsiecf_cache_directories_t *pymsiecf_cache_directories,
           Py_ssize_t item_index )
{
	PyObject *cache_directory_object = NULL;
	static char *function            = "pymsiecf_cache_directories_getitem";

	if( pymsiecf_cache_directories == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories.",
		 function );

		return( NULL );
	}
	if( pymsiecf_cache_directories->get_cache_directory_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories - missing get cache directory by index function.",
		 function );

		return( NULL );
	}
	if( pymsiecf_cache_directories->number_of_cache_directories < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories - invalid number of cache directories.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pymsiecf_cache_directories->number_of_cache_directories ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	cache_directory_object = pymsiecf_cache_directories->get_cache_directory_by_index(
	                          pymsiecf_cache_directories->parent_object,
	                          (int) item_index );

	return( cache_directory_object );
}

/* The cache directories iter() function
 */
PyObject *pymsiecf_cache_directories_iter(
           pymsiecf_cache_directories_t *pymsiecf_cache_directories )
{
	static char *function = "pymsiecf_cache_directories_iter";

	if( pymsiecf_cache_directories == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pymsiecf_cache_directories );

	return( (PyObject *) pymsiecf_cache_directories );
}

/* The cache directories iternext() function
 */
PyObject *pymsiecf_cache_directories_iternext(
           pymsiecf_cache_directories_t *pymsiecf_cache_directories )
{
	PyObject *cache_directory_object = NULL;
	static char *function            = "pymsiecf_cache_directories_iternext";

	if( pymsiecf_cache_directories == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories.",
		 function );

		return( NULL );
	}
	if( pymsiecf_cache_directories->get_cache_directory_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories - missing get cache directory by index function.",
		 function );

		return( NULL );
	}
	if( pymsiecf_cache_directories->cache_directory_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories - invalid cache directory index.",
		 function );

		return( NULL );
	}
	if( pymsiecf_cache_directories->number_of_cache_directories < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid cache directories - invalid number of cache directories.",
		 function );

		return( NULL );
	}
	if( pymsiecf_cache_directories->cache_directory_index >= pymsiecf_cache_directories->number_of_cache_directories )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	cache_directory_object = pymsiecf_cache_directories->get_cache_directory_by_index(
	                          pymsiecf_cache_directories->parent_object,
	                          pymsiecf_cache_directories->cache_directory_index );

	if( cache_directory_object != NULL )
	{
		pymsiecf_cache_directories->cache_directory_index++;
	}
	return( cache_directory_object );
}

