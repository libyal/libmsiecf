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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pymsiecf_datetime.h"
#include "pymsiecf_error.h"
#include "pymsiecf_file.h"
#include "pymsiecf_integer.h"
#include "pymsiecf_item.h"
#include "pymsiecf_libcerror.h"
#include "pymsiecf_libmsiecf.h"
#include "pymsiecf_python.h"
#include "pymsiecf_unused.h"
#include "pymsiecf_url.h"

PyMethodDef pymsiecf_url_object_methods[] = {

	/* Functions to access the URL values */

	{ "get_type",
	  (PyCFunction) pymsiecf_url_get_type,
	  METH_NOARGS,
	  "get_type() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the type." },

	{ "get_primary_time",
	  (PyCFunction) pymsiecf_url_get_primary_time,
	  METH_NOARGS,
	  "get_primary_time() -> Datetime or None\n"
	  "\n"
	  "Retrieves the primary time." },

	{ "get_primary_time_as_integer",
	  (PyCFunction) pymsiecf_url_get_primary_time_as_integer,
	  METH_NOARGS,
	  "get_primary_time_as_integer() -> Integer or None\n"
	  "\n"
	  "Retrieves the primary time as a 64-bit integer containing a FILETIME value." },

	{ "get_secondary_time",
	  (PyCFunction) pymsiecf_url_get_secondary_time,
	  METH_NOARGS,
	  "get_secondary_time() -> Datetime or None\n"
	  "\n"
	  "Retrieves the secondary time." },

	{ "get_secondary_time_as_integer",
	  (PyCFunction) pymsiecf_url_get_secondary_time_as_integer,
	  METH_NOARGS,
	  "get_secondary_time_as_integer() -> Integer or None\n"
	  "\n"
	  "Retrieves the secondary time as a 64-bit integer containing a FILETIME value." },

	{ "get_expiration_time",
	  (PyCFunction) pymsiecf_url_get_expiration_time,
	  METH_NOARGS,
	  "get_expiration_time() -> Datetime or None\n"
	  "\n"
	  "Returns the expiration date and time." },

	{ "get_expiration_time_as_integer",
	  (PyCFunction) pymsiecf_url_get_expiration_time_as_integer,
	  METH_NOARGS,
	  "get_expiration_time_as_integer() -> Integer or None\n"
	  "\n"
	  "Returns the expiration date and time as:\n"
	  "\ta 64-bit integer containing a FILETIME value (format version 4.7)\n"
	  "\ta 32-bit integer containing a FAT date time value (format version 5.2)" },

	{ "get_last_checked_time",
	  (PyCFunction) pymsiecf_url_get_last_checked_time,
	  METH_NOARGS,
	  "get_last_checked_time() -> Datetime or None\n"
	  "\n"
	  "Returns the last checked date and time." },

	{ "get_last_checked_time_as_integer",
	  (PyCFunction) pymsiecf_url_get_last_checked_time_as_integer,
	  METH_NOARGS,
	  "get_last_checked_time_as_integer() -> Integer or None\n"
	  "\n"
	  "Returns the last checked date and time as a 32-bit integer containing a FAT date time value." },

	{ "get_cached_file_size",
	  (PyCFunction) pymsiecf_url_get_cached_file_size,
	  METH_NOARGS,
	  "get_cached_file_size() -> Integer or None\n"
	  "\n"
	  "Retrieves the cached file size." },

	{ "get_cache_directory_index",
	  (PyCFunction) pymsiecf_url_get_cache_directory_index,
	  METH_NOARGS,
	  "get_cache_directory_index() -> Integer or None\n"
	  "\n"
	  "Retrieves the cache directory index." },

	{ "get_number_of_hits",
	  (PyCFunction) pymsiecf_url_get_number_of_hits,
	  METH_NOARGS,
	  "get_number_of_hits() -> Integer or None\n"
	  "\n"
	  "Retrieves the number of hits." },

	{ "get_location",
	  (PyCFunction) pymsiecf_url_get_location,
	  METH_NOARGS,
	  "get_location() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the location." },

	{ "get_filename",
	  (PyCFunction) pymsiecf_url_get_filename,
	  METH_NOARGS,
	  "get_filename() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the filename." },

	{ "get_data",
	  (PyCFunction) pymsiecf_url_get_data,
	  METH_NOARGS,
	  "get_data() -> Bytes or None\n"
	  "\n"
	  "Retrieves the data." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pymsiecf_url_object_get_set_definitions[] = {

	{ "type",
	  (getter) pymsiecf_url_get_type,
	  (setter) 0,
	  "The type.",
	  NULL },

	{ "primary_time",
	  (getter) pymsiecf_url_get_primary_time,
	  (setter) 0,
	  "The primary time.",
	  NULL },

	{ "secondary_time",
	  (getter) pymsiecf_url_get_secondary_time,
	  (setter) 0,
	  "The secondary time.",
	  NULL },

	{ "expiration_time",
	  (getter) pymsiecf_url_get_expiration_time,
	  (setter) 0,
	  "The expiration time.",
	  NULL },

	{ "last_checked_time",
	  (getter) pymsiecf_url_get_last_checked_time,
	  (setter) 0,
	  "The last checked time.",
	  NULL },

	{ "cached_file_size",
	  (getter) pymsiecf_url_get_cached_file_size,
	  (setter) 0,
	  "The cached file size.",
	  NULL },

	{ "cache_directory_index",
	  (getter) pymsiecf_url_get_cache_directory_index,
	  (setter) 0,
	  "The cache directory index.",
	  NULL },

	{ "number_of_hits",
	  (getter) pymsiecf_url_get_number_of_hits,
	  (setter) 0,
	  "The number of hits.",
	  NULL },

	{ "location",
	  (getter) pymsiecf_url_get_location,
	  (setter) 0,
	  "The location.",
	  NULL },

	{ "filename",
	  (getter) pymsiecf_url_get_filename,
	  (setter) 0,
	  "The filename.",
	  NULL },

	{ "data",
	  (getter) pymsiecf_url_get_data,
	  (setter) 0,
	  "The data.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pymsiecf_url_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pymsiecf.url",
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
	"pymsiecf URL object (wraps libmsiecf_item_t type LIBMSIECF_ITEM_TYPE_URL)",
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
	pymsiecf_url_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pymsiecf_url_object_get_set_definitions,
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

/* Retrieves the type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_type(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error  = NULL;
	const char *errors        = NULL;
	const char *type_string   = 0;
	static char *function     = "pymsiecf_url_get_type";
	size_t type_string_length = 0;
	uint8_t type              = 0;
	int result                = 0;

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

	result = libmsiecf_url_get_type(
	          pymsiecf_item->item,
	          &type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( type )
	{
		case LIBMSIECF_URL_ITEM_TYPE_CACHE:
			type_string        = "cache";
			type_string_length = 5;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_COMPATIBILITY:
			type_string        = "compatibility";
			type_string_length = 13;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_COOKIE:
			type_string        = "cookie";
			type_string_length = 6;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_DOM_STORE:
			type_string        = "DOM-store";
			type_string_length = 9;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_DOWNLOAD:
			type_string        = "download";
			type_string_length = 8;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_HISTORY:
			type_string        = "history";
			type_string_length = 7;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_HISTORY_DAILY:
			type_string        = "history-daily";
			type_string_length = 13;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_HISTORY_WEEKLY:
			type_string        = "history-weekly";
			type_string_length = 14;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_INPRIVATE_FILTERING:
			type_string        = "inprivate-filtering";
			type_string_length = 19;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_RSS_FEED:
			type_string        = "RSS-feed";
			type_string_length = 8;
			break;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_TLD:
			type_string        = "TLD";
			type_string_length = 3;
			break;

		case LIBMSIECF_URL_ITEM_TYPE_USER_DATA:
			type_string        = "user-data";
			type_string_length = 9;
			break;

		default:
			break;
	}
	if( type_string == NULL )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         type_string,
	         (Py_ssize_t) type_string_length,
	         errors ) );
}

/* Retrieves the primary date and time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_primary_time(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pymsiecf_url_get_primary_time";
	uint64_t filetime          = 0;
	int result                 = 0;

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

	result = libmsiecf_url_get_primary_time(
	          pymsiecf_item->item,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve primary time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pymsiecf_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the primary date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_primary_time_as_integer(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pymsiecf_url_get_primary_time_as_integer";
	uint64_t filetime        = 0;
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

	result = libmsiecf_url_get_primary_time(
	          pymsiecf_item->item,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve primary time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pymsiecf_integer_unsigned_new_from_64bit(
	                  filetime );

	return( integer_object );
}

/* Retrieves the secondary date and time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_secondary_time(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pymsiecf_url_get_secondary_time";
	uint64_t filetime          = 0;
	int result                 = 0;

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

	result = libmsiecf_url_get_secondary_time(
	          pymsiecf_item->item,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve secondary time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pymsiecf_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the secondary date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_secondary_time_as_integer(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pymsiecf_url_get_secondary_time_as_integer";
	uint64_t filetime        = 0;
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

	result = libmsiecf_url_get_secondary_time(
	          pymsiecf_item->item,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve secondary time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pymsiecf_integer_unsigned_new_from_64bit(
	                  filetime );

	return( integer_object );
}

/* Retrieves the expiration date and time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_expiration_time(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	PyObject *date_time_object     = NULL;
	libcerror_error_t *error       = NULL;
	pymsiecf_file_t *pymsiecf_file = NULL;
	static char *function          = "pymsiecf_url_get_expiration_time";
	uint64_t timestamp             = 0;
	uint8_t major_version          = 0;
	uint8_t minor_version          = 0;
	int result                     = 0;

	PYMSIECF_UNREFERENCED_PARAMETER( arguments )

	if( pymsiecf_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	if( pymsiecf_item->parent_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid URL - missing parent object.",
		 function );

		return( NULL );
	}
	pymsiecf_file  = (pymsiecf_file_t *) ( (pymsiecf_item_t *) pymsiecf_item )->parent_object;

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
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_url_get_expiration_time(
	          pymsiecf_item->item,
	          &timestamp,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve expiration time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( ( major_version == 4 )
	 && ( minor_version == 7 ) )
	{
		date_time_object = pymsiecf_datetime_new_from_filetime(
		                    timestamp );
	}
	else
	{
		date_time_object = pymsiecf_datetime_new_from_fat_date_time(
		                    (uint32_t) timestamp );
	}
	return( date_time_object );
}

/* Retrieves the expiration date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_expiration_time_as_integer(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pymsiecf_url_get_expiration_time_as_integer";
	uint64_t timestamp       = 0;
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

	result = libmsiecf_url_get_expiration_time(
	          pymsiecf_item->item,
	          &timestamp,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve expiration time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pymsiecf_integer_unsigned_new_from_64bit(
	                  timestamp );

	return( integer_object );
}

/* Retrieves the last checked date and time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_last_checked_time(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pymsiecf_item_get_last_checked_time";
	uint32_t fat_date_time     = 0;
	int result                 = 0;

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

	result = libmsiecf_url_get_last_checked_time(
	          pymsiecf_item->item,
	          &fat_date_time,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve last checked time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pymsiecf_datetime_new_from_fat_date_time(
	                    fat_date_time );

	return( date_time_object );
}

/* Retrieves the last checked date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_last_checked_time_as_integer(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pymsiecf_url_get_last_checked_time_as_integer";
	uint32_t fat_date_time   = 0;
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

	result = libmsiecf_url_get_last_checked_time(
	          pymsiecf_item->item,
	          &fat_date_time,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve last checked time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pymsiecf_integer_unsigned_new_from_64bit(
	                  (uint64_t) fat_date_time );

	return( integer_object );
}

/* Retrieves the cached file size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_cached_file_size(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error  = NULL;
	PyObject *integer_object  = NULL;
	static char *function     = "pymsiecf_url_get_cached_file_size";
	uint64_t cached_file_size = 0;
	int result                = 0;

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

	result = libmsiecf_url_get_cached_file_size(
	          pymsiecf_item->item,
	          &cached_file_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve cached file size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pymsiecf_integer_unsigned_new_from_64bit(
	                  cached_file_size );

	return( integer_object );
}

/* Retrieves the cache directory index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_cache_directory_index(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error     = NULL;
	PyObject *integer_object     = NULL;
	static char *function        = "pymsiecf_url_get_cache_directory_index";
	int8_t cache_directory_index = 0;
	int result                   = 0;

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

	result = libmsiecf_url_get_cache_directory_index(
	          pymsiecf_item->item,
	          (uint8_t *) &cache_directory_index,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve cache directory index.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) cache_directory_index );
#else
	integer_object = PyInt_FromLong(
	                  (long) cache_directory_index );
#endif
	return( integer_object );
}

/* Retrieves the number of hits
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_number_of_hits(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pymsiecf_url_get_number_of_hits";
	uint32_t number_of_hits  = 0;
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

	result = libmsiecf_url_get_number_of_hits(
	          pymsiecf_item->item,
	          &number_of_hits,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of hits.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_hits );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_hits );
#endif
	return( integer_object );
}

/* Retrieves the location
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_location(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	const char *errors       = NULL;
	uint8_t *location        = NULL;
	static char *function    = "pymsiecf_url_get_location";
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

	result = libmsiecf_url_get_utf8_location_size(
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

	result = libmsiecf_url_get_utf8_location(
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

/* Retrieves the filename
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_filename(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	const char *errors       = NULL;
	uint8_t *filename        = NULL;
	static char *function    = "pymsiecf_url_get_filename";
	size_t filename_size     = 0;
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

	result = libmsiecf_url_get_utf8_filename_size(
	          pymsiecf_item->item,
	          &filename_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve filename size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( filename_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	filename = (uint8_t *) PyMem_Malloc(
	                        sizeof( uint8_t ) * filename_size );

	if( filename == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create filename.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_url_get_utf8_filename(
		  pymsiecf_item->item,
		  filename,
		  filename_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve filename.",
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
			 (char *) filename,
			 (Py_ssize_t) filename_size - 1,
			 errors );

	PyMem_Free(
	 filename );

	return( string_object );

on_error:
	if( filename != NULL )
	{
		PyMem_Free(
		 filename );
	}
	return( NULL );
}

/* Retrieves the data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pymsiecf_url_get_data(
           pymsiecf_item_t *pymsiecf_item,
           PyObject *arguments PYMSIECF_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	uint8_t *data            = NULL;
	static char *function    = "pymsiecf_url_get_data";
	size_t data_size         = 0;
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

	result = libmsiecf_url_get_data_size(
	          pymsiecf_item->item,
	          &data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( data_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	data = (uint8_t *) PyMem_Malloc(
	                    sizeof( uint8_t ) * data_size );

	if( data == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libmsiecf_url_get_data(
		  pymsiecf_item->item,
		  data,
		  data_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pymsiecf_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
			 (char *) data,
			 (Py_ssize_t) data_size );
#else
	string_object = PyString_FromStringAndSize(
			 (char *) data,
			 (Py_ssize_t) data_size );
#endif
	PyMem_Free(
	 data );

	return( string_object );

on_error:
	if( data != NULL )
	{
		PyMem_Free(
		 data );
	}
	return( NULL );
}

