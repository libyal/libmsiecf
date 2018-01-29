/*
 * Python bindings module for libmsiecf (pymsiecf)
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

#include <common.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pymsiecf.h"
#include "pymsiecf_cache_directories.h"
#include "pymsiecf_error.h"
#include "pymsiecf_file.h"
#include "pymsiecf_file_object_io_handle.h"
#include "pymsiecf_item.h"
#include "pymsiecf_item_flags.h"
#include "pymsiecf_item_types.h"
#include "pymsiecf_items.h"
#include "pymsiecf_leak.h"
#include "pymsiecf_libcerror.h"
#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"
#include "pymsiecf_redirected.h"
#include "pymsiecf_unused.h"
#include "pymsiecf_url.h"
#include "pymsiecf_url_types.h"

#if !defined( LIBMSIECF_HAVE_BFIO )
LIBMSIECF_EXTERN \
int libmsiecf_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libmsiecf_error_t **error );
#endif

/* The pymsiecf module methods
 */
PyMethodDef pymsiecf_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pymsiecf_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	{ "check_file_signature",
	  (PyCFunction) pymsiecf_check_file_signature,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature(filename) -> Boolean\n"
	  "\n"
	  "Checks if a file has a MSIE Cache File (index.dat) file signature." },

	{ "check_file_signature_file_object",
	  (PyCFunction) pymsiecf_check_file_signature_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature_file_object(file_object) -> Boolean\n"
	  "\n"
	  "Checks if a file has a MSIE Cache File (index.dat) file signature using a file-like object." },

	{ "open",
	  (PyCFunction) pymsiecf_file_new_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> Object\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pymsiecf_file_new_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> Object\n"
	  "\n"
	  "Opens a file using a file-like object." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pymsiecf/libmsiecf version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_get_version(
           PyObject *self PYMSIECF_ATTRIBUTE_UNUSED,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( self )
	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libmsiecf_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

/* Checks if the file has a MSIE Cache File (index.dat) file signature
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_check_file_signature(
           PyObject *self PYMSIECF_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	static char *function        = "pymsiecf_check_file_signature";
	static char *keyword_list[]  = { "filename", NULL };
	const char *filename_narrow  = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	PYMSIECF_UNREFERENCED_PARAMETER( self )

	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
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

		result = libmsiecf_check_file_signature_wide(
		          filename_wide,
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

		result = libmsiecf_check_file_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result == -1 )
		{
			pymsiecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check file signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
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

		result = libmsiecf_check_file_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		if( result == -1 )
		{
			pymsiecf_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check file signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Checks if the file has a MSIE Cache File (index.dat) file signature using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_check_file_signature_file_object(
           PyObject *self PYMSIECF_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error         = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	PyObject *file_object            = NULL;
	static char *function            = "pymsiecf_check_file_signature_file_object";
	static char *keyword_list[]      = { "file_object", NULL };
	int result                       = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
	     keyword_list,
	     &file_object ) == 0 )
	{
		return( NULL );
	}
	if( pymsiecf_file_object_initialize(
	     &file_io_handle,
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

	result = libmsiecf_check_file_signature_file_io_handle(
	          file_io_handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to check file signature.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &file_io_handle,
	     &error ) != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( result != 0 )
	{
		Py_IncRef(
		 (PyObject *) Py_True );

		return( Py_True );
	}
	Py_IncRef(
	 (PyObject *) Py_False );

	return( Py_False );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

#if PY_MAJOR_VERSION >= 3

/* The pymsiecf module definition
 */
PyModuleDef pymsiecf_module_definition = {
	PyModuleDef_HEAD_INIT,

	/* m_name */
	"pymsiecf",
	/* m_doc */
	"Python libmsiecf module (pymsiecf).",
	/* m_size */
	-1,
	/* m_methods */
	pymsiecf_module_methods,
	/* m_reload */
	NULL,
	/* m_traverse */
	NULL,
	/* m_clear */
	NULL,
	/* m_free */
	NULL,
};

#endif /* PY_MAJOR_VERSION >= 3 */

/* Initializes the pymsiecf module
 */
#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pymsiecf(
                void )
#else
PyMODINIT_FUNC initpymsiecf(
                void )
#endif
{
	PyObject *module                            = NULL;
	PyTypeObject *cache_directories_type_object = NULL;
	PyTypeObject *file_type_object              = NULL;
	PyTypeObject *item_type_object              = NULL;
	PyTypeObject *item_flags_type_object        = NULL;
	PyTypeObject *item_types_type_object        = NULL;
	PyTypeObject *items_type_object             = NULL;
	PyTypeObject *leak_type_object              = NULL;
	PyTypeObject *redirected_type_object        = NULL;
	PyTypeObject *url_type_object               = NULL;
	PyTypeObject *url_types_type_object         = NULL;
	PyGILState_STATE gil_state                  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libmsiecf_notify_set_stream(
	 stderr,
	 NULL );
	libmsiecf_notify_set_verbose(
	 1 );
#endif

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(
	          &pymsiecf_module_definition );
#else
	module = Py_InitModule3(
	          "pymsiecf",
	          pymsiecf_module_methods,
	          "Python libmsiecf module (pymsiecf)." );
#endif
	if( module == NULL )
	{
#if PY_MAJOR_VERSION >= 3
		return( NULL );
#else
		return;
#endif
	}
	PyEval_InitThreads();

	gil_state = PyGILState_Ensure();

	/* Setup the file type object
	 */
	pymsiecf_file_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pymsiecf_file_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_file_type_object );

	file_type_object = &pymsiecf_file_type_object;

	PyModule_AddObject(
	 module,
	 "file",
	 (PyObject *) file_type_object );

	/* Setup the cache directories type object
	 */
	pymsiecf_cache_directories_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pymsiecf_cache_directories_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_cache_directories_type_object );

	cache_directories_type_object = &pymsiecf_cache_directories_type_object;

	PyModule_AddObject(
	 module,
	 "_cache_directories",
	 (PyObject *) cache_directories_type_object );

	/* Setup the item type object
	 */
	pymsiecf_item_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pymsiecf_item_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_item_type_object );

	item_type_object = &pymsiecf_item_type_object;

	PyModule_AddObject(
	 module,
	 "item",
	 (PyObject *) item_type_object );

	/* Setup the items type object
	 */
	pymsiecf_items_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pymsiecf_items_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_items_type_object );

	items_type_object = &pymsiecf_items_type_object;

	PyModule_AddObject(
	 module,
	 "_items",
	 (PyObject *) items_type_object );

	/* Setup the leak type object
	 */
	pymsiecf_leak_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pymsiecf_leak_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_leak_type_object );

	leak_type_object = &pymsiecf_leak_type_object;

	PyModule_AddObject(
	 module,
	 "leak",
	 (PyObject *) leak_type_object );

	/* Setup the redirected type object
	 */
	pymsiecf_redirected_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pymsiecf_redirected_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_redirected_type_object );

	redirected_type_object = &pymsiecf_redirected_type_object;

	PyModule_AddObject(
	 module,
	 "redirected",
	 (PyObject *) redirected_type_object );

	/* Setup the URL type object
	 */
	pymsiecf_url_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pymsiecf_url_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_url_type_object );

	url_type_object = &pymsiecf_url_type_object;

	PyModule_AddObject(
	 module,
	 "url",
	 (PyObject *) url_type_object );

	/* Setup the item types type object
	 */
	pymsiecf_item_types_type_object.tp_new = PyType_GenericNew;

	if( pymsiecf_item_types_init_type(
	     &pymsiecf_item_types_type_object ) != 1 )
	{
		goto on_error;
	}
	if( PyType_Ready(
	     &pymsiecf_item_types_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_item_types_type_object );

	item_types_type_object = &pymsiecf_item_types_type_object;

	PyModule_AddObject(
	 module,
	 "item_types",
	 (PyObject *) item_types_type_object );

	/* Setup the item flags type object
	 */
	pymsiecf_item_flags_type_object.tp_new = PyType_GenericNew;

	if( pymsiecf_item_flags_init_type(
	     &pymsiecf_item_flags_type_object ) != 1 )
	{
		goto on_error;
	}
	if( PyType_Ready(
	     &pymsiecf_item_flags_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_item_flags_type_object );

	item_flags_type_object = &pymsiecf_item_flags_type_object;

	PyModule_AddObject(
	 module,
	 "item_flags",
	 (PyObject *) item_flags_type_object );

	/* Setup the URL types type object
	 */
	pymsiecf_url_types_type_object.tp_new = PyType_GenericNew;

	if( pymsiecf_url_types_init_type(
	     &pymsiecf_url_types_type_object ) != 1 )
	{
		goto on_error;
	}
	if( PyType_Ready(
	     &pymsiecf_url_types_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pymsiecf_url_types_type_object );

	url_types_type_object = &pymsiecf_url_types_type_object;

	PyModule_AddObject(
	 module,
	 "url_types",
	 (PyObject *) url_types_type_object );

	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( module );
#else
	return;
#endif

on_error:
	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( NULL );
#else
	return;
#endif
}

