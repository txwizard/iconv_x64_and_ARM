/*
    ============================================================================

    File Name:          CRTTime.H

    Library:            CRTTime.dll

    Link Library:       CRTTime.lib

    Synopsis:           Declare functions that extend the standard CRT time
                        functions to cover their shortcomings.

    Remarks:            To the greatest extent practical, these functions not only
                        adhere to the interfaces of their counterparts in the CRT
                        library, but they leverage them to do most of the work.

                        The exception to that adherance is that their calling
                        convention is __stdcall, rather than __cdecl.

    Author:             David A. Gray, MBA

    License:            Copyright (C) 2019, David A. Gray. All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    *   Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    *   Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    *   Neither the name of Simple Soft Services, Inc. nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version Author Synopsis
    ---------- ------- ------ --------------------------------------------------
	2018/06/26 1.0.0.1 DAG    Initial release

	2019/03/25 1.0.0.2 DAG    Implement wrappers that return formatted local and
							  UTC current time strings via strftime.

	2019/03/31 1.0.0.3 DAG    Implement a separate default format string for UTC
	                          time, STRFTIME_DEFAULT_UTC_FORMAT, rename the
							  original STRFTIME_DEFAULT_LOCAL_FORMAT, and move
							  both into this library header, where they belong.

							  This version is the first to actually implemnt the
							  version of strftime that accepts a locale.
							  However, although the routines that impelement the
							  TZ_TOKEN_ABBREV_MODIFIER_* tokens exist, they are
							  as yet only stubs, and they aren't wired into the
							  main processing routines.
	============================================================================
*/

//  -----------------------------------------------------------------------------
//  Implement once-only inclusion for non-Microsoft compilers.
//  -----------------------------------------------------------------------------

#if !defined ( CRTTIME2_DEFINED )
#define        CRTTIME2_DEFINED

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

//  -----------------------------------------------------------------------------
//  Guarantee that the CRT Unicode preprocessor symbol is defined if the
//  corresponding Windows symbol is defined.
//  -----------------------------------------------------------------------------

#if defined ( UNICODE )
    #if !defined ( _UNICODE )
        #define _UNICODE
    #endif  /* #if !defined ( _UNICODE ) */
#endif  /* #if defined ( UNICODE ) */

//  -----------------------------------------------------------------------------
//  Define the calling convention for this library.
//  -----------------------------------------------------------------------------

#if defined ( CRTTIME_EXPORTS )
    #define LIBSPEC_CRTTIME2_API __declspec(dllexport) __stdcall
#else   /* TRUE block, #if defined ( CRTTIME2_EXPORTS ) */
    #define LIBSPEC_CRTTIME2_API __declspec(dllimport) __stdcall
#endif  /* #if !defined ( CRTTIME2_EXPORTS ) */

//  -----------------------------------------------------------------------------
//  CRT Library Header Files:
//  -----------------------------------------------------------------------------

#include <stdlib.h>
#include <tchar.h>
#include <time.h>

//  -----------------------------------------------------------------------------
//  Windows Header Files:
//  -----------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#include <windows.h>

#define STRFTIME_DEFAULT_LOCAL_FORMAT   TEXT ( "%Y/%m/%d %H:%M:%S %Z" )
#define STRFTIME_DEFAULT_UTC_FORMAT     TEXT ( "%Y/%m/%d %H:%M:%S UTC" )

//  -----------------------------------------------------------------------------
//  Document raw and modified versions of the new Time Zone Abbreviation tokens,
//  including the modifier prefix to insert just before the standard TZ tokens.
//
//  This library supports these tokens in addition to those defined in the ANSI
//  standard.
//  -----------------------------------------------------------------------------

#define CRTTIME_USER_ERROR_MASK			( APPLICATION_ERROR_MASK  | 0x4000 )
#define CRTTIME_ERR_OUT_OF_MEMORY       ( CRTTIME_USER_ERROR_MASK | 0x0001 )
#define CRTTIME_ERR_NULL_FORMAT_STRING	( CRTTIME_USER_ERROR_MASK | 0x0002 )

#define CRTTIME_FORMAT_STRING_ID_LIMIT	0x7FFF				// 32,767 Upper limit of IDs that are considered fair game for User-assigned IDs

#define CRTTIME_INVALID_FORMAT			NULL

#if !defined ( HEAP_ALL_FLAGS_OFF )
	#define HEAP_ALL_FLAGS_OFF			0x00000000L
#endif	/* #if !defined ( HEAP_ALL_FLAGS_OFF )	*/

#define TZ_TOKEN_ABBREV_MODIFIER_N_1    "^Z"
#define TZ_TOKEN_ABBREV_MODIFIER_N_2    "^#Z"
#define TZ_TOKEN_ABBREV_MODIFIER_N_3    "^Z^"
#define TZ_TOKEN_ABBREV_MODIFIER_N_4    "^#Z^"

#define TZ_ABBREV_TOKEN_N_1             "%t"
#define TZ_ABBREV_TOKEN_N_2             "%T"
#define TZ_ABBREV_TOKEN_N_3             "%#t"
#define TZ_ABBREV_TOKEN_N_4             "%#T"

#define TZ_TOKEN_ABBREV_MODIFIER_W_1    L"^Z"
#define TZ_TOKEN_ABBREV_MODIFIER_W_2    L"^#Z"
#define TZ_TOKEN_ABBREV_MODIFIER_W_3    L"^Z^"
#define TZ_TOKEN_ABBREV_MODIFIER_W_4    L"^#Z^"

#define TZ_ABBREV_TOKEN_W_1             L"%t"
#define TZ_ABBREV_TOKEN_W_2             L"%T"
#define TZ_ABBREV_TOKEN_W_3             L"%#t"
#define TZ_ABBREV_TOKEN_W_4             L"%#T"

//  -----------------------------------------------------------------------------
//  Declare functions exported by this library.
//  -----------------------------------------------------------------------------

#if defined ( __cplusplus )
extern "C" {
#endif /* #if defined ( __cplusplus ) */

	LPTSTR LIBSPEC_CRTTIME2_API FormatNowLocalA ( void * pFormat , const HMODULE phDllhModule );
	LPTSTR LIBSPEC_CRTTIME2_API FormatNowLocalW ( void * pFormat , const HMODULE phDllhModule );
	LPTSTR LIBSPEC_CRTTIME2_API FormatNowUTCA   ( void * pFormat , const HMODULE phDllhModule );
	LPTSTR LIBSPEC_CRTTIME2_API FormatNowUTCA   ( void * pFormat , const HMODULE phDllhModule );

	size_t LIBSPEC_CRTTIME2_API strftime2 (
		PTCHAR            strDest ,
		size_t            maxsize ,
		const PTCHAR      format ,
		const struct tm * timeptr
	);

	size_t LIBSPEC_CRTTIME2_API strftime2_l (
		PTCHAR            strDest ,
		size_t            maxsize ,
		const PTCHAR      format ,
		const struct tm * timeptr ,
		const _locale_t   locale
	);

	size_t LIBSPEC_CRTTIME2_API wcsftime2 (
	    PTCHAR            strDest ,
	    size_t            maxsize ,
	    const PTCHAR      format ,
	    const struct tm * timeptr
	);

	size_t LIBSPEC_CRTTIME2_API wcsftime2_l (
	    PTCHAR            strDest ,
	    size_t            maxsize ,
	    const PTCHAR      format ,
	    const struct tm * timeptr ,
	    const _locale_t   locale
	);

	PTCHAR LIBSPEC_CRTTIME2_API CRTTimeErrMsgA
	(
		const int pintErrorCode
	);

	PTCHAR LIBSPEC_CRTTIME2_API CRTTimeErrMsgW
	(
		const int pintErrorCode
	);
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */

//  -----------------------------------------------------------------------------
//  Generic-Text Routine Mappings:
//  -----------------------------------------------------------------------------

#if defined ( _UNICODE )
	#define FormatNowLocal	FormatNowLocalW
	#define FormatNowUTC	FormatNowUTCW
	#define _tcsftime2      wcsftime2
    #define _tcsftime2_l    wcsftime2_l
    #define _CRTTimeErrMsg  CRTTimeErrMsgW
#elif defined ( _MBCS )
	#define FormatNowLocal	FormatNowLocalA
	#define FormatNowUTC	FormatNowUTCA
    #define _tcsftime2      strftime2
    #define _tcsftime2_l    strftime2_l
    #define _CRTTimeErrMsg  CRTTimeErrMsgA
#else
	#define FormatNowLocal	FormatNowLocalA
	#define FormatNowUTC	FormatNowUTCA
    #define _tcsftime2      strftime2
    #define _tcsftime2_l    strftime2_l
    #define _CRTTimeErrMsg  CRTTimeErrMsgA
#endif  /* #if defined ( _UNICODE ) */
#endif  /* #if !defined ( CRTTIME2_DEFINED ) */