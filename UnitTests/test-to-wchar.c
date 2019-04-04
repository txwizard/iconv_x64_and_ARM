/* Copyright (C) 2009, 2011 Free Software Foundation, Inc.
   This file is part of the GNU LIBICONV Library.

   The GNU LIBICONV Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   The GNU LIBICONV Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU LIBICONV Library; see the file COPYING.LIB.
   If not, see <http://www.gnu.org/licenses/>.
*/

//	----------------------------------------------------------------------------
//	Revision History
//	----------------------------------------------------------------------------
//
//	Date       By Remark
//	---------- -- --------------------------------------------------------------
//	2019/04/03 DG Open with displays of the program name and version, followed
//                by a message indicating the platform for which it was built,
//                followed by the startup date and time (local followed by UTC).
//	----------------------------------------------------------------------------

#if defined ( UNICODE )
	#undef UNICODE
#endif	/* #if defined ( UNICODE ) */

#if defined ( _UNICODE )
	#undef _UNICODE
#endif	/* #if defined ( UNICODE ) */

#include "..\include\config.h"

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "..\include\iconv.h"

#ifdef _WIN32
	#include ".\CRTTime.H"
	#include ".\NativeConssoleAppAids.H"
#endif	/* #ifdef _WIN32 */


DWORD ReportWin32Error( LPCTSTR plpHint )
{
	DWORD rdwStatusCode = GetLastError( );
	fprintf( stderr ,
		     FB_FormatMessage( plpHint ,
			                   rdwStatusCode ,
			                   SCF2_HEXADECIMAL ) );
	return rdwStatusCode;
}	// DWORD ReportSystemError


/* This test checks that the conversion to wchar_t stops correctly when
   the input is incomplete.  Based on a bug report from
   Tristan Gingold <gingold@adacore.com>.
*/

int main( )
{
#ifdef _WIN32
	char *	lpszProgramName = ShowProgramInfo( );

	char *  lpFormattedStartTimeLocal = FormatNowLocal( STRFTIME_DEFAULT_LOCAL_FORMAT ,
		                                                NULL );

	if ( lpFormattedStartTimeLocal == NULL )
		return GetLastError( );

	LPTSTR  lpFormattedStartTimeUTC = FormatNowUTC( STRFTIME_DEFAULT_UTC_FORMAT ,
		                                            NULL );

	if ( lpFormattedStartTimeUTC == NULL )
		return GetLastError( );

	_tprintf( "Execution start time %s (%s)\n\n" ,
    		  lpFormattedStartTimeLocal ,
		      lpFormattedStartTimeUTC );

	if ( !HeapFree( GetProcessHeap( ) , 0 , lpFormattedStartTimeLocal ) )
		return ReportWin32Error( "A deallocation error arose while deallocating buffer lpFormattedStartTimeLocal." );

	if ( !HeapFree( GetProcessHeap( ) , 0 , lpFormattedStartTimeUTC ) )
		return ReportWin32Error( "A deallocation error arose while deallocating buffer lpFormattedStartTimeUTC." );
#endif	/* #ifdef _WIN32 */

	iconv_t cd = iconv_open( "wchar_t" ,
		"UTF-8" );

	if ( cd == ( iconv_t ) ( -1 ) )
	{
		/* Skip the test on platforms without wchar_t (Solaris 2.6, HP-UX 11.00).  */
		_tprintf( "The wchar_t is unknown on this platform.\n" );
	}
	else
	{
		char inbuf [ 2 ] = { 0xc2, 0xa0 };
		wchar_t outbuf [ 10 ];

		char *inptr = inbuf;
		size_t inbytesleft = 1;
		char *outptr = ( char * ) outbuf;
		size_t outbytesleft = sizeof( outbuf );

		size_t r = iconv( cd ,
			              ( ICONV_CONST char ** ) &inptr ,
			              &inbytesleft ,
			              &outptr ,
			              &outbytesleft );

		if ( !( r == ( size_t ) ( -1 ) && errno == EINVAL ) )
			abort( );
	}	// if ( cd == ( iconv_t ) ( -1 ) )

#ifdef _WIN32
	_tprintf( "\n%s succeeded.\n" ,
			  lpszProgramName );
#else
	_tprintf( "\n%s succeeded.\n" ,
		      __argv [ 0 ] );
#endif	/* #ifdef _WIN32 */

	return ERROR_SUCCESS;
}	// main