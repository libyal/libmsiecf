/*
 * Python object wrapper of libmsiecf_file_t
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pymsiecf_cache_directories.h"
#include "pymsiecf_codepage.h"
#include "pymsiecf_error.h"
#include "pymsiecf_file.h"
#include "pymsiecf_file_object_io_handle.h"
#include "pymsiecf_integer.h"
#include "pymsiecf_item.h"
#include "pymsiecf_items.h"
#include "pymsiecf_leak.h"
#include "pymsiecf_libbfio.h"
#include "pymsiecf_libcerror.h"
#include "pymsiecf_libclocale.h"
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

#endif /* !defined( LIBMSIECF_HAVE_BFIO ) */

PyMethodDef pymsiecf_file_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pymsiecf_file_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the file to abort the current activity." },

	{ "open",
	  (PyCFunction) pymsiecf_file_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pymsiecf_file_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a file using a file-like object." },

	{ "close",
	  (PyCFunction) pymsiecf_file_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a file." },

	{ "get_size",
	  (PyCFunction) pymsiecf_file_get_size,
	  METH_NOARGS,
	  "get_size() -> Integer or None\n"
	  "\n"
	  "Retrieves the size." },

	{ "get_ascii_codepage",
	  (PyCFunction) pymsiecf_file_get_ascii_codepage,
	  METH_NOARGS,
	  "get_ascii_codepage() -> String\n"
	  "\n"
	  "Retrieves the codepage for ASCII strings used in the file." },

	{ "set_ascii_codepage",
	  (PyCFunction) pymsiecf_file_set_ascii_codepage,
	  METH_VARARGS | METH_KEYWORDS,
	  "set_ascii_codepage(codepage) -> None\n"
	  "\n"
	  "Sets the codepage for ASCII strings used in the file.\n"
	  "Expects the codepage to be a string containing a Python codec definition." },

	{ "get_format_version",
	  (PyCFunction) pymsiecf_file_get_format_version,
	  METH_NOARGS,
	  "get_format_version() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the format version." },

	{ "get_number_of_cache_directories",
	  (PyCFunction) pymsiecf_file_get_number_of_cache_directories,
	  METH_NOARGS,
	  "get_number_of_cache_directories() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of cache directories." },

	{ "get_cache_directory",
	  (PyCFunction) pymsiecf_file_get_cache_directory,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_cache_directory(cache_directory_index) -> String or None\n"
	  "\n"
	  "Retrieves the cache directory specified by the index." },

	{ "get_number_of_items",
	  (PyCFunction) pymsiecf_file_get_number_of_items,
	  METH_NOARGS,
	  "get_number_of_items() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of items." },

	{ "get_item",
	  (PyCFunction) pymsiecf_file_get_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_item(item_index) -> Object or None\n"
	  "\n"
	  "Retrieves the item specified by the index." },

	{ "get_number_of_recovered_items",
	  (PyCFunction) pymsiecf_file_get_number_of_recovered_items,
	  METH_NOARGS,
	  "get_number_of_recovered_items() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of recovered items." },

	{ "get_recovered_item",
	  (PyCFunction) pymsiecf_file_get_recovered_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_recovered_item(recovered_item_index) -> Object or None\n"
	  "\n"
	  "Retrieves the recovered item specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pymsiecf_file_object_get_set_definitions[] = {

	{ "size",
	  (getter) pymsiecf_file_get_size,
	  (setter) 0,
	  "The size.",
	  NULL },

	{ "ascii_codepage",
	  (getter) pymsiecf_file_get_ascii_codepage,
	  (setter) pymsiecf_file_set_ascii_codepage_setter,
	  "The codepage used for ASCII strings in the file.",
	  NULL },

	{ "format_version",
	  (getter) pymsiecf_file_get_format_version,
	  (setter) 0,
	  "The format version.",
	  NULL },

	{ "number_of_cache_directories",
	  (getter) pymsiecf_file_get_number_of_cache_directories,
	  (setter) 0,
	  "The number of cache directories.",
	  NULL },

	{ "cache_directories",
	  (getter) pymsiecf_file_get_cache_directories,
	  (setter) 0,
	  "The cache directories.",
	  NULL },

	{ "number_of_items",
	  (getter) pymsiecf_file_get_number_of_items,
	  (setter) 0,
	  "The number of items.",
	  NULL },

	{ "items",
	  (getter) pymsiecf_file_get_items,
	  (setter) 0,
	  "The items.",
	  NULL },

	{ "number_of_recovered_items",
	  (getter) pymsiecf_file_get_number_of_recovered_items,
	  (setter) 0,
	  "The number of recovered items.",
	  NULL },

	{ "recovered_items",
	  (getter) pymsiecf_file_get_recovered_items,
	  (setter) 0,
	  "The recovered items.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pymsiecf_file_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

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

/* Intializes a file object
 * Returns 0 if successful or -1 on error
 */
int pymsiecf_file_init(
     pymsiecf_file_t *pymsiecf_file )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_init";

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	/* Make sure libmsiecf file is set to NULL
	 */
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
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pymsiecf_file_free";
	int result                  = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pymsiecf_file );

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
	if( pymsiecf_file->file != NULL )
	{
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
	}
	ob_type->tp_free(
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

/* Opens a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_open(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	const char *filename_narrow  = NULL;
	static char *function        = "pymsiecf_file_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

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
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
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
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pymsiecf_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libmsiecf_file_open_wide(
		          pymsiecf_file->file,
		          filename_wide,
		          LIBMSIECF_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pymsiecf_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
		                   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libmsiecf_file_open(
		          pymsiecf_file->file,
		          filename_narrow,
		          LIBMSIECF_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
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
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pymsiecf_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   string_object );
#else
		filename_narrow = PyString_AsString(
		                   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libmsiecf_file_open(
		          pymsiecf_file->file,
		          filename_narrow,
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
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

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
	static char *function       = "pymsiecf_file_open_file_object";
	static char *keyword_list[] = { "file_object", "mode", NULL };
	char *mode                  = NULL;
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
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "read" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing read attribute.",
		 function );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "seek" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing seek attribute.",
		 function );

		return( NULL );
	}
	if( pymsiecf_file->file_io_handle != NULL )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid file - file IO handle already set.",
		 function );

		goto on_error;
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

/* Retrieves the size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_size(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_get_size";
	size64_t size            = 0;
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

	result = libmsiecf_file_get_size(
	          pymsiecf_file->file,
	          &size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pymsiecf_integer_unsigned_new_from_64bit(
	                  (uint64_t) size );

	return( integer_object );
}

/* Retrieves the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_ascii_codepage(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	const char *codepage_string = NULL;
	static char *function       = "pymsiecf_file_get_ascii_codepage";
	int ascii_codepage          = 0;
	int result                  = 0;

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

	result = libmsiecf_file_get_ascii_codepage(
	          pymsiecf_file->file,
	          &ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
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
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromString(
	                 codepage_string );
#else
	string_object = PyString_FromString(
	                 codepage_string );
#endif
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
	codepage_string_length = narrow_string_length(
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
	char *codepage_string       = NULL;
	static char *keyword_list[] = { "codepage", NULL };
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
     PyObject *string_object,
     void *closure PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *utf8_string_object = NULL;
	char *codepage_string        = NULL;
	static char *function        = "pymsiecf_file_set_ascii_codepage_setter";
	int result                   = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( closure )

	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pymsiecf_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type unicode.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		/* The codepage string should only contain ASCII characters.
		 */
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pymsiecf_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert unicode string to UTF-8.",
			 function );

			return( -1 );
		}
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
		                   utf8_string_object );
#else
		codepage_string = PyString_AsString(
		                   utf8_string_object );
#endif
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
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pymsiecf_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
		                   string_object );
#else
		codepage_string = PyString_AsString(
		                   string_object );
#endif
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
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( -1 );
}

/* Retrieves the format version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_format_version(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	char utf8_string[ 4 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pymsiecf_file_get_format_version";
	uint8_t major_version    = 0;
	uint8_t minor_version    = 0;
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

	result = libmsiecf_file_get_format_version(
	          pymsiecf_file->file,
	          &major_version,
	          &minor_version,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve format version.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( major_version > 9 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: major version out of bounds.",
		 function );

		return( NULL );
	}
	if( minor_version > 9 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: minor version out of bounds.",
		 function );

		return( NULL );
	}
	utf8_string[ 0 ] = '0' + (char) major_version;
	utf8_string[ 1 ] = '.';
	utf8_string[ 2 ] = '0' + (char) minor_version;
	utf8_string[ 3 ] = 0;

	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) 3,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Retrieves the number of cache directories
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_number_of_cache_directories(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object        = NULL;
	libcerror_error_t *error        = NULL;
	static char *function           = "pymsiecf_file_get_number_of_cache_directories";
	int number_of_cache_directories = 0;
	int result                      = 0;

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

	result = libmsiecf_file_get_number_of_cache_directories(
	          pymsiecf_file->file,
	          &number_of_cache_directories,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of cache directories.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_cache_directories );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_cache_directories );
#endif
	return( integer_object );
}

/* Retrieves a specific cache directory by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_cache_directory_by_index(
           PyObject *pymsiecf_file,
           int cache_directory_index )
{
	char string[ 9 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_get_cache_directory_by_index";
	int result               = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_get_cache_directory_name(
	          ( (pymsiecf_file_t *) pymsiecf_file )->file,
	          cache_directory_index,
	          string,
	          9,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve cache directory name: %d.",
		 function,
		 cache_directory_index );

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
	/* Assumed that the directory name contains only basic ASCII characters
	 */
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromString(
	                 string );
#else
	string_object = PyString_FromString(
	                 string );
#endif
	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to convert cache directory name string into string object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Retrieves a specific cache directory
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_cache_directory(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object     = NULL;
	static char *keyword_list[] = { "cache_directory_index", NULL };
	int cache_directory_index   = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &cache_directory_index ) == 0 )
	{
		return( NULL );
	}
	string_object = pymsiecf_file_get_cache_directory_by_index(
	                 (PyObject *) pymsiecf_file,
	                 cache_directory_index );

	return( string_object );
}

/* Retrieves a sequence and iterator object for the cache directories
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_cache_directories(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object       = NULL;
	libcerror_error_t *error        = NULL;
	static char *function           = "pymsiecf_file_get_cache_directories";
	int number_of_cache_directories = 0;
	int result                      = 0;

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

	result = libmsiecf_file_get_number_of_cache_directories(
	          pymsiecf_file->file,
	          &number_of_cache_directories,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of cache directories.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pymsiecf_cache_directories_new(
	                   (PyObject *) pymsiecf_file,
	                   &pymsiecf_file_get_cache_directory_by_index,
	                   number_of_cache_directories );

	if( sequence_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

/* Retrieves the number of items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_number_of_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_get_number_of_items";
	int number_of_items      = 0;
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
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_items );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_items );
#endif
	return( integer_object );
}

/* Retrieves the item type object
 * Returns a Python type object if successful or NULL on error
 */
PyTypeObject *pymsiecf_file_get_item_type_object(
               libmsiecf_item_t *item )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_get_item_by_index";
	uint8_t item_type        = 0;
	int result               = 0;

	if( item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
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
		 "%s: unable to retrieve item type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( item_type )
	{
		case LIBMSIECF_ITEM_TYPE_LEAK:
			return( &pymsiecf_leak_type_object );

		case LIBMSIECF_ITEM_TYPE_REDIRECTED:
			return( &pymsiecf_redirected_type_object );

		case LIBMSIECF_ITEM_TYPE_URL:
			return( &pymsiecf_url_type_object );

		default:
			break;
	}
	return( &pymsiecf_item_type_object );
}

/* Retrieves a specific item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_item_by_index(
           PyObject *pymsiecf_file,
           int item_index )
{
	PyObject *item_object     = NULL;
	PyTypeObject *type_object = NULL;
	libcerror_error_t *error  = NULL;
	libmsiecf_item_t *item    = NULL;
	static char *function     = "pymsiecf_file_get_item_by_index";
	int result                = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_get_item_by_index(
	          ( (pymsiecf_file_t *) pymsiecf_file )->file,
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
	type_object = pymsiecf_file_get_item_type_object(
	               item );

	if( type_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to retrieve item type object.",
		 function );

		goto on_error;
	}
	item_object = pymsiecf_item_new(
	               type_object,
	               item,
	               (PyObject *) pymsiecf_file );

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
	               (PyObject *) pymsiecf_file,
	               item_index );

	return( item_object );
}

/* Retrieves a sequence and iterator object for the items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pymsiecf_file_get_items";
	int number_of_items       = 0;
	int result                = 0;

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
	sequence_object = pymsiecf_items_new(
	                   (PyObject *) pymsiecf_file,
	                   &pymsiecf_file_get_item_by_index,
	                   number_of_items );

	if( sequence_object == NULL )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

/* Retrieves the number of recovered items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_number_of_recovered_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pymsiecf_file_get_number_of_recovered_items";
	int number_of_items      = 0;
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
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_items );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_items );
#endif
	return( integer_object );
}

/* Retrieves a specific recovered item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_recovered_item_by_index(
           PyObject *pymsiecf_file,
           int item_index )
{
	PyObject *item_object     = NULL;
	PyTypeObject *type_object = NULL;
	libcerror_error_t *error  = NULL;
	libmsiecf_item_t *item    = NULL;
	static char *function     = "pymsiecf_file_get_recovered_item_by_index";
	int result                = 0;

	if( pymsiecf_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_file_get_recovered_item_by_index(
	          ( (pymsiecf_file_t *) pymsiecf_file )->file,
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
	type_object = pymsiecf_file_get_item_type_object(
	               item );

	if( type_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to retrieve item type object.",
		 function );

		goto on_error;
	}
	item_object = pymsiecf_item_new(
	               type_object,
	               item,
	               (PyObject *) pymsiecf_file );

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
	               (PyObject *) pymsiecf_file,
	               item_index );

	return( item_object );
}

/* Retrieves a sequence and iterator object for the recovered items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_file_get_recovered_items(
           pymsiecf_file_t *pymsiecf_file,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pymsiecf_file_get_recovered_items";
	int number_of_items       = 0;
	int result                = 0;

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
	sequence_object = pymsiecf_items_new(
	                   (PyObject *) pymsiecf_file,
	                   &pymsiecf_file_get_recovered_item_by_index,
	                   number_of_items );

	if( sequence_object == NULL )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

