/*
 * Codepage definitions for libmsiecf
 *
 * Copyright (C) 2009-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMSIECF_CODEPAGE_H )
#define _LIBMSIECF_CODEPAGE_H

#include <libmsiecf/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBMSIECF_CODEPAGES
{
	LIBMSIECF_CODEPAGE_ASCII			= 20127,

	LIBMSIECF_CODEPAGE_ISO_8859_1			= 28591,
	LIBMSIECF_CODEPAGE_ISO_8859_2			= 28592,
	LIBMSIECF_CODEPAGE_ISO_8859_3			= 28593,
	LIBMSIECF_CODEPAGE_ISO_8859_4			= 28594,
	LIBMSIECF_CODEPAGE_ISO_8859_5			= 28595,
	LIBMSIECF_CODEPAGE_ISO_8859_6			= 28596,
	LIBMSIECF_CODEPAGE_ISO_8859_7			= 28597,
	LIBMSIECF_CODEPAGE_ISO_8859_8			= 28598,
	LIBMSIECF_CODEPAGE_ISO_8859_9			= 28599,
	LIBMSIECF_CODEPAGE_ISO_8859_10			= 28600,
	LIBMSIECF_CODEPAGE_ISO_8859_11			= 28601,
	LIBMSIECF_CODEPAGE_ISO_8859_13			= 28603,
	LIBMSIECF_CODEPAGE_ISO_8859_14			= 28604,
	LIBMSIECF_CODEPAGE_ISO_8859_15			= 28605,
	LIBMSIECF_CODEPAGE_ISO_8859_16			= 28606,

	LIBMSIECF_CODEPAGE_KOI8_R			= 20866,
	LIBMSIECF_CODEPAGE_KOI8_U			= 21866,

	LIBMSIECF_CODEPAGE_WINDOWS_874			= 874,
	LIBMSIECF_CODEPAGE_WINDOWS_932			= 932,
	LIBMSIECF_CODEPAGE_WINDOWS_936			= 936,
	LIBMSIECF_CODEPAGE_WINDOWS_949			= 949,
	LIBMSIECF_CODEPAGE_WINDOWS_950			= 950,
	LIBMSIECF_CODEPAGE_WINDOWS_1250			= 1250,
	LIBMSIECF_CODEPAGE_WINDOWS_1251			= 1251,
	LIBMSIECF_CODEPAGE_WINDOWS_1252			= 1252,
	LIBMSIECF_CODEPAGE_WINDOWS_1253			= 1253,
	LIBMSIECF_CODEPAGE_WINDOWS_1254			= 1254,
	LIBMSIECF_CODEPAGE_WINDOWS_1255			= 1255,
	LIBMSIECF_CODEPAGE_WINDOWS_1256			= 1256,
	LIBMSIECF_CODEPAGE_WINDOWS_1257			= 1257,
	LIBMSIECF_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBMSIECF_CODEPAGE_US_ASCII			LIBMSIECF_CODEPAGE_ASCII

#define LIBMSIECF_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBMSIECF_CODEPAGE_ISO_8859_1
#define LIBMSIECF_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBMSIECF_CODEPAGE_ISO_8859_2
#define LIBMSIECF_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBMSIECF_CODEPAGE_ISO_8859_3
#define LIBMSIECF_CODEPAGE_ISO_NORTH_EUROPEAN		LIBMSIECF_CODEPAGE_ISO_8859_4
#define LIBMSIECF_CODEPAGE_ISO_CYRILLIC			LIBMSIECF_CODEPAGE_ISO_8859_5
#define LIBMSIECF_CODEPAGE_ISO_ARABIC			LIBMSIECF_CODEPAGE_ISO_8859_6
#define LIBMSIECF_CODEPAGE_ISO_GREEK			LIBMSIECF_CODEPAGE_ISO_8859_7
#define LIBMSIECF_CODEPAGE_ISO_HEBREW			LIBMSIECF_CODEPAGE_ISO_8859_8
#define LIBMSIECF_CODEPAGE_ISO_TURKISH			LIBMSIECF_CODEPAGE_ISO_8859_9
#define LIBMSIECF_CODEPAGE_ISO_NORDIC			LIBMSIECF_CODEPAGE_ISO_8859_10
#define LIBMSIECF_CODEPAGE_ISO_THAI			LIBMSIECF_CODEPAGE_ISO_8859_11
#define LIBMSIECF_CODEPAGE_ISO_BALTIC			LIBMSIECF_CODEPAGE_ISO_8859_13
#define LIBMSIECF_CODEPAGE_ISO_CELTIC			LIBMSIECF_CODEPAGE_ISO_8859_14

#define LIBMSIECF_CODEPAGE_ISO_LATIN_1			LIBMSIECF_CODEPAGE_ISO_8859_1
#define LIBMSIECF_CODEPAGE_ISO_LATIN_2			LIBMSIECF_CODEPAGE_ISO_8859_2
#define LIBMSIECF_CODEPAGE_ISO_LATIN_3			LIBMSIECF_CODEPAGE_ISO_8859_3
#define LIBMSIECF_CODEPAGE_ISO_LATIN_4			LIBMSIECF_CODEPAGE_ISO_8859_4
#define LIBMSIECF_CODEPAGE_ISO_LATIN_5			LIBMSIECF_CODEPAGE_ISO_8859_9
#define LIBMSIECF_CODEPAGE_ISO_LATIN_6			LIBMSIECF_CODEPAGE_ISO_8859_10
#define LIBMSIECF_CODEPAGE_ISO_LATIN_7			LIBMSIECF_CODEPAGE_ISO_8859_13
#define LIBMSIECF_CODEPAGE_ISO_LATIN_8			LIBMSIECF_CODEPAGE_ISO_8859_14
#define LIBMSIECF_CODEPAGE_ISO_LATIN_9			LIBMSIECF_CODEPAGE_ISO_8859_15
#define LIBMSIECF_CODEPAGE_ISO_LATIN_10			LIBMSIECF_CODEPAGE_ISO_8859_16

#define LIBMSIECF_CODEPAGE_KOI8_RUSSIAN			LIBMSIECF_CODEPAGE_KOI8_R
#define LIBMSIECF_CODEPAGE_KOI8_UKRAINIAN		LIBMSIECF_CODEPAGE_KOI8_U

#define LIBMSIECF_CODEPAGE_WINDOWS_THAI			LIBMSIECF_CODEPAGE_WINDOWS_874
#define LIBMSIECF_CODEPAGE_WINDOWS_JAPANESE		LIBMSIECF_CODEPAGE_WINDOWS_932
#define LIBMSIECF_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBMSIECF_CODEPAGE_WINDOWS_936
#define LIBMSIECF_CODEPAGE_WINDOWS_KOREAN		LIBMSIECF_CODEPAGE_WINDOWS_949
#define LIBMSIECF_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBMSIECF_CODEPAGE_WINDOWS_950
#define LIBMSIECF_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBMSIECF_CODEPAGE_WINDOWS_1250
#define LIBMSIECF_CODEPAGE_WINDOWS_CYRILLIC		LIBMSIECF_CODEPAGE_WINDOWS_1251
#define LIBMSIECF_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBMSIECF_CODEPAGE_WINDOWS_1252
#define LIBMSIECF_CODEPAGE_WINDOWS_GREEK		LIBMSIECF_CODEPAGE_WINDOWS_1253
#define LIBMSIECF_CODEPAGE_WINDOWS_TURKISH		LIBMSIECF_CODEPAGE_WINDOWS_1254
#define LIBMSIECF_CODEPAGE_WINDOWS_HEBREW		LIBMSIECF_CODEPAGE_WINDOWS_1255
#define LIBMSIECF_CODEPAGE_WINDOWS_ARABIC		LIBMSIECF_CODEPAGE_WINDOWS_1256
#define LIBMSIECF_CODEPAGE_WINDOWS_BALTIC		LIBMSIECF_CODEPAGE_WINDOWS_1257
#define LIBMSIECF_CODEPAGE_WINDOWS_VIETNAMESE		LIBMSIECF_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMSIECF_CODEPAGE_H ) */

