/*
 * Python object definition of the libmsiecf file
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

#include "pymsiecf_codepage.h"
#include "pymsiecf_error.h"
#include "pymsiecf_file.h"
#include "pymsiecf_file_object_io_handle.h"
#include "pymsiecf_item.h"
#include "pymsiecf_items.h"
#include "pymsiecf_leak.h"
#include "pymsiecf_libbfio.h"
#include "pymsiecf_libcerror.h"
#include "pymsiecf_libclocale.h"
#include "pymsiecf_libcstring.h"
#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"
#include "pymsiecf_redirected.h"
#include "pymsiecf_unused.h"
#include "pymsiecf_url.h"

#if !defined( LIBMSIECF_HAVE_BFIO )
LIBMSIECF_EXTERN \
int libmsiecf_file_open_file_io_handle(
     libmsiecf_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libmsiecf_error_t **error );
#endif

PyMethodDef pymsiecf_file_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pymsiecf_file_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the file to abort the current activity" },

	/* Functions to access the file */

	{ "open",
	  (PyCFunction) pymsiecf_file_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a file" },

	{ "open_file_object",
	  (PyCFunction) pymsiecf_file_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a file using a file-like object" },

	{ "close",
	  (PyCFunction) pymsiecf_file_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a file" },

	{ "get_ascii_codepage",
	  (PyCFunction) pymsiecf_file_get_ascii_codepage,
	  METH_NOARGS,
	  "get_ascii_codepage() -> String\n"
	  "\n"
	  "Returns the codepage used for ASCII strings in the file" },

	{ "set_ascii_codepage",
	  (PyCFunction) pymsiecf_file_set_ascii_codepage,
	  METH_VARARGS | METH_KEYWORDS,
	  "set_ascii_codepage(codepage) -> None\n"
	  "\n"
	  "Set the codepage used for ASCII strings in the file\n"
	  "Expects the codepage to be a String containing a Python codec definition" },

	/* Functions to access the items */

	{ "format_version",
	  (PyCFunction) pymsiecf_file_get_format_version,
	  METH_NOARGS,
	  "get_format_version() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the format version" },

	{ "get_number_of_items",
	  (PyCFunction) pymsiecf_file_get_number_of_items,
	  METH_NOARGS,
	  "get_number_of_items() -> Integer\n"
	  "\n"
	  "Retrieves the number of items" },

	{ "get_item",
	  (PyCFunction) pymsiecf_file_get_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_item(item_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific item" },

	{ "get_number_of_recovered_items",
	  (PyCFunction) pymsiecf_file_get_number_of_recovered_items,
	  METH_NOARGS,
	  "get_number_of_recovered_items() -> Integer\n"
	  "\n"
	  "Retrieves the number of recovered items" },

	{ "get_recovered_item",
	  (PyCFunction) pymsiecf_file_get_recovered_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_recovered_item(item_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific recovered item" },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pymsiecf_file_object_get_set_definitions[] = {

	{ "ascii_codepage",
	  (getter) pymsiecf_file_get_ascii_codepage,
	  (setter) pymsiecf_file_set_ascii_codepage_setter,
	  "The codepage used for ASCII strings in the file",
	  NULL },

	{ "format_version",
	  (getter) pymsiecf_file_get_format_version,
	  (setter) 0,
	  "The format version",
	  NULL },

	{ "number_of_items",
	  (getter) pymsiecf_file_get_number_of_items,
	  (setter) 0,
	  "The number of items",
	  NULL },

	{ "items",
	  (getter) pymsiecf_file_get_items,
	  (setter) 0,
	  "The items",
	  NULL },

	{ "number_of_recovered_items",
	  (getter) pymsiecf_file_get_number_of_recovered_items,
	  (setter) 0,
	  "The number of items",
	  NULL },

	{ "recovered_items",
	  (getter) pymsiecf_file_get_recovered_items,
	  (setter) 0,
	  "The recovered items",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pymsiecf_file_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pymsiecf.file",
	/* tp_basicsize */
	sizeof( pymsiecf_file_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pymsiecf_file_free,
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
	"pymsiecf file object (wraps libmsiecf_file_t)",
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
	pymsiecf_file_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pymsiecf_file_object_get_set_definitions,
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
	(initproc) pymsiecf_file_init,
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

/* Creates a new file object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_new(
           void )
{
	pymsiecf_file_t *pymsiecf_file = NULL;
	static char *function          = "pymsiecf_file_new";

	pymsiecf_file = PyObject_New(
	              struct pymsiecf_file,
	              &pymsiecf_file_type_object );

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	if( pymsiecf_file_init(
	     pymsiecf_file ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pymsiecf_file );

on_error:
	if( pymsiecf_file != NULL )
	{
		Py_DecRef(
		 (PyObject *) pymsiecf_file );
	}
	return( NULL );
}

/* Creates a new file object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_new_open(
           PyObject *self PYMSIECF_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pymsiecf_file = NULL;

	PYMSIECF_UNREFERENCED_PARAMETER( self )

	pymsiecf_file = pymsiecf_file_new();

	pymsiecf_file_open(
	 (pymsiecf_file_t *) pymsiecf_file,
	 arguments,
	 keywords );

	return( pymsiecf_file );
}

/* Creates a new file object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_new_open_file_object(
           PyObject *self PYMSIECF_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pymsiecf_file = NULL;

	PYMSIECF_UNREFERENCED_PARAMETER( self )

	pymsiecf_file = pymsiecf_file_new();

	pymsiecf_file_open_file_object(
	 (pymsiecf_file_t *) pymsiecf_file,
	 arguments,
	 keywords );

	return( pymsiecf_file );
}

/* Intializes a file object
 * Returns 0 if successful or -1 on error
 */
int pymsiecf_file_init(
     pymsiecf_file_t *pymsiecf_file )
{
	static char *function    = "pymsiecf_file_init";
	libcerror_error_t *error = NULL;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	pymsiecf_file->file           = NULL;
	pymsiecf_file->file_io_handle = NULL;

	if( libmsiecf_file_initialize(
	     &( pymsiecf_file->file ),
	     &error ) != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a file object
 */
void pymsiecf_file_free(
      pymsiecf_file_t *pymsiecf_file )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_free";
	int result               = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return;
	}
	if( pymsiecf_file->ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file - missing ob_type.",
		 function );

		return;
	}
	if( pymsiecf_file->ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file - invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pymsiecf_file->file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file - missing libmsiecf file.",
		 function );

		return;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_free(
	          &( pymsiecf_file->file ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free libmsiecf file.",
		 function );

		libcerror_error_free(
		 &error );
	}
	pymsiecf_file->ob_type->tp_free(
	 (PyObject*) pymsiecf_file );
}

/* Signals the file to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_signal_abort(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_signal_abort";
	int result               = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_signal_abort(
	          pymsiecf_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )

/* Opens a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_open(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *exception_string    = NULL;
	PyObject *exception_traceback = NULL;
	PyObject *exception_type      = NULL;
	PyObject *exception_value     = NULL;
	PyObject *string_object       = NULL;
	libcerror_error_t *error      = NULL;
	static char *function         = "pymsiecf_file_open";
	static char *keyword_list[]   = { "filename", "mode", NULL };
	const wchar_t *filename_wide  = NULL;
	const char *filename_narrow   = NULL;
	char *error_string            = NULL;
	int result                    = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. We cannot use "u" here either since that does not allow us to pass non Unicode string objects and
	 * Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object ) == 0 )
	{
		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		PyErr_Fetch(
		 &exception_type,
		 &exception_value,
		 &exception_traceback );

		exception_string = PyObject_Repr(
		                    exception_value );

		error_string = PyString_AsString(
		                exception_string );

		if( error_string != NULL )
		{
			PyErr_Format(
		         PyExc_RuntimeError,
			 "%s: unable to determine if string object is of type unicode with error: %s.",
			 function,
			 error_string );
		}
		else
		{
			PyErr_Format(
		         PyExc_RuntimeError,
			 "%s: unable to determine if string object is of type unicode.",
			 function );
		}
		Py_DecRef(
		 exception_string );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libmsiecf_file_open_wide(
		          pymsiecf_file->file,
	                  filename_wide,
		          LIBMSIECF_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result == -1 )
		{
			pymsiecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			return( Py_True );
		}
		return( Py_False );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyString_Type );

	if( result == -1 )
	{
		PyErr_Fetch(
		 &exception_type,
		 &exception_value,
		 &exception_traceback );

		exception_string = PyObject_Repr(
				    exception_value );

		error_string = PyString_AsString(
				exception_string );

		if( error_string != NULL )
		{
			PyErr_Format(
		         PyExc_RuntimeError,
			 "%s: unable to determine if string object is of type string with error: %s.",
			 function,
			 error_string );
		}
		else
		{
			PyErr_Format(
		         PyExc_RuntimeError,
			 "%s: unable to determine if string object is of type string.",
			 function );
		}
		Py_DecRef(
		 exception_string );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

		filename_narrow = PyString_AsString(
				   string_object );

		Py_BEGIN_ALLOW_THREADS

		result = libmsiecf_file_open(
		          pymsiecf_file->file,
	                  filename_narrow,
		          LIBMSIECF_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result == -1 )
		{
			pymsiecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			return( Py_True );
		}
		return( Py_False );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type",
	 function );

	return( NULL );
}

#else

/* Opens a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_open(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	char *filename              = NULL;
	char *mode                  = NULL;
	static char *keyword_list[] = { "filename", "mode", NULL };
	static char *function       = "pymsiecf_file_open";
	int result                  = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * For systems that support UTF-8 this works for Unicode string objects as well.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s|s",
	     keyword_list,
	     &filename,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_open(
	          pymsiecf_file->file,
	          filename,
	          LIBMSIECF_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open file.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */

/* Opens a file using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_open_file_object(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	char *mode                  = NULL;
	static char *keyword_list[] = { "file_object", "mode", NULL };
	static char *function       = "pymsiecf_file_open_file_object";
	int result                  = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	if( pymsiecf_file_object_initialize(
	     &( pymsiecf_file->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_open_file_io_handle(
	          pymsiecf_file->file,
	          pymsiecf_file->file_io_handle,
	          LIBMSIECF_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open file.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pymsiecf_file->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pymsiecf_file->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Closes a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_close(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_close";
	int result               = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_close(
	          pymsiecf_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close file.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pymsiecf_file->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pymsiecf_file->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pymsiecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_ascii_codepage(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error    = NULL;
	PyObject *string_object     = NULL;
	const char *codepage_string = NULL;
	static char *function       = "pymsiecf_file_get_ascii_codepage";
	int ascii_codepage          = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( libmsiecf_file_get_ascii_codepage(
	     pymsiecf_file->file,
	     &ascii_codepage,
	     &error ) != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	codepage_string = pymsiecf_codepage_to_string(
	                   ascii_codepage );

	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported ASCII codepage: %d.",
		 function,
		 ascii_codepage );

		return( NULL );
	}
	string_object = PyString_FromString(
	                 codepage_string );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert codepage string into string object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns 1 if successful or -1 on error
 */
int pymsiecf_file_set_ascii_codepage_from_string(
     pymsiecf_file_t *pymsiecf_file,
     const char *codepage_string )
{
	libcerror_error_t *error      = NULL;
	static char *function         = "pymsiecf_file_set_ascii_codepage_from_string";
	size_t codepage_string_length = 0;
	uint32_t feature_flags        = 0;
	int ascii_codepage            = 0;
	int result                    = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid codepage string.",
		 function );

		return( -1 );
	}
	codepage_string_length = libcstring_narrow_string_length(
	                          codepage_string );

	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	if( libclocale_codepage_copy_from_string(
	     &ascii_codepage,
	     codepage_string,
	     codepage_string_length,
	     feature_flags,
	     &error ) != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_RuntimeError,
		 "%s: unable to determine ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_set_ascii_codepage(
	          pymsiecf_file->file,
	          ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to set ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 1 );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_set_ascii_codepage(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	static char *keyword_list[] = { "codepage", NULL };
	char *codepage_string       = NULL;
	int result                  = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &codepage_string ) == 0 )
	{
		return( NULL );
	}
	result = pymsiecf_file_set_ascii_codepage_from_string(
	          pymsiecf_file,
	          codepage_string );

	if( result != 1 )
	{
		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
int pymsiecf_file_set_ascii_codepage_setter(
     pymsiecf_file_t *pymsiecf_file,
     PyObject *value_object,
     void *closure PYMSIECF_ATTRIBUTE_UNUSED )
{
	char *codepage_string = NULL;
	int result            = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( closure )

	codepage_string = PyString_AsString(
	                   value_object );

	if( codepage_string == NULL )
	{
		return( -1 );
	}
	result = pymsiecf_file_set_ascii_codepage_from_string(
	          pymsiecf_file,
	          codepage_string );

	if( result != 1 )
	{
		return( -1 );
	}
	return( 0 );
}

/* Retrieves the format version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_format_version(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	char version_string[ 4 ];

	const char *errors    = NULL;
	static char *function = "pymsiecf_file_get_format_version";

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( pymsiecf_file->major_version > 9 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file - major version out of bounds.",
		 function );

		return( NULL );
	}
	if( pymsiecf_file->minor_version > 9 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file - minor version out of bounds.",
		 function );

		return( NULL );
	}
	version_string[ 0 ] = '0' + pymsiecf_file->major_version;
	version_string[ 1 ] = '.';
	version_string[ 2 ] = '0' + pymsiecf_file->minor_version;
	version_string[ 3 ] = 0;

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) 3,
	         errors ) );
}

/* Retrieves the number of items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_number_of_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_get_number_of_items";
	int number_of_items      = 0;
	int result               = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_get_number_of_items(
	          pymsiecf_file->file,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( PyInt_FromLong(
	         (long) number_of_items ) );
}

/* Retrieves a specific item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_item_by_index(
           pymsiecf_file_t *pymsiecf_file,
           int item_index )
{
	libcerror_error_t *error  = NULL;
	libmsiecf_item_t *item    = NULL;
	PyObject *item_object     = NULL;
	PyTypeObject *type_object = NULL;
	static char *function     = "pymsiecf_file_get_item_by_index";
	uint8_t item_type         = 0;
	int result                = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_get_item(
	          pymsiecf_file->file,
	          item_index,
	          &item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve item: %d.",
		 function,
		 item_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_item_get_type(
	          item,
	          &item_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve item: %d type.",
		 function,
		 item_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	switch( item_type )
	{
		case LIBMSIECF_ITEM_TYPE_LEAK:
			type_object = &pymsiecf_leak_type_object;
			break;

		case LIBMSIECF_ITEM_TYPE_REDIRECTED:
			type_object = &pymsiecf_redirected_type_object;
			break;

		case LIBMSIECF_ITEM_TYPE_URL:
			type_object = &pymsiecf_url_type_object;
			break;

		default:
			type_object = &pymsiecf_item_type_object;
			break;
	}
	item_object = pymsiecf_item_new(
	               type_object,
	               item,
	               pymsiecf_file );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( item != NULL )
	{
		libmsiecf_item_free(
		 &item,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_item(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	static char *keyword_list[] = { "item_index", NULL };
	int item_index              = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &item_index ) == 0 )
	{
		return( NULL );
	}
	item_object = pymsiecf_file_get_item_by_index(
	               pymsiecf_file,
	               item_index );

	return( item_object );
}

/* Retrieves a items sequence and iterator object for the items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *items_object   = NULL;
	static char *function    = "pymsiecf_file_get_items";
	int number_of_items      = 0;
	int result               = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_get_number_of_items(
	          pymsiecf_file->file,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	items_object = pymsiecf_items_new(
	                pymsiecf_file,
	                &pymsiecf_file_get_item_by_index,
	                number_of_items );

	if( items_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create items object.",
		 function );

		return( NULL );
	}
	return( items_object );
}

/* Retrieves the number of recovered items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_number_of_recovered_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_get_number_of_recovered_items";
	int number_of_items      = 0;
	int result               = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_get_number_of_recovered_items(
	          pymsiecf_file->file,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of recovered items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( PyInt_FromLong(
	         (long) number_of_items ) );
}

/* Retrieves a specific recovered item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_recovered_item_by_index(
           pymsiecf_file_t *pymsiecf_file,
           int item_index )
{
	libcerror_error_t *error  = NULL;
	libmsiecf_item_t *item    = NULL;
	PyObject *item_object     = NULL;
	PyTypeObject *type_object = NULL;
	static char *function     = "pymsiecf_file_get_recovered_item_by_index";
	uint8_t item_type         = 0;
	int result                = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_get_recovered_item(
	          pymsiecf_file->file,
	          item_index,
	          &item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve recovered item: %d.",
		 function,
		 item_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_item_get_type(
	          item,
	          &item_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve item: %d type.",
		 function,
		 item_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	switch( item_type )
	{
		case LIBMSIECF_ITEM_TYPE_LEAK:
			type_object = &pymsiecf_leak_type_object;
			break;

		case LIBMSIECF_ITEM_TYPE_REDIRECTED:
			type_object = &pymsiecf_redirected_type_object;
			break;

		case LIBMSIECF_ITEM_TYPE_URL:
			type_object = &pymsiecf_url_type_object;
			break;

		default:
			type_object = &pymsiecf_item_type_object;
			break;
	}
	item_object = pymsiecf_item_new(
	               type_object,
	               item,
	               pymsiecf_file );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create recovered item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( item != NULL )
	{
		libmsiecf_item_free(
		 &item,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific recovered item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_recovered_item(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	static char *keyword_list[] = { "item_index", NULL };
	int item_index              = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &item_index ) == 0 )
	{
		return( NULL );
	}
	item_object = pymsiecf_file_get_recovered_item_by_index(
	               pymsiecf_file,
	               item_index );

	return( item_object );
}

/* Retrieves a items sequence and iterator object for the recoverd items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_recovered_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *items_object   = NULL;
	static char *function    = "pymsiecf_file_get_recovered_items";
	int number_of_items      = 0;
	int result               = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_get_number_of_recovered_items(
	          pymsiecf_file->file,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of recovered items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	items_object = pymsiecf_items_new(
	                pymsiecf_file,
	                &pymsiecf_file_get_recovered_item_by_index,
	                number_of_items );

	if( items_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create items object.",
		 function );

		return( NULL );
	}
	return( items_object );
}

