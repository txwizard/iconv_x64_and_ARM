#if !defined ( _NATIVECONSSOLEAPPAIDS_DEFINED )
#define _NATIVECONSSOLEAPPAIDS_DEFINED

/*
	============================================================================

	File Name:          NativeConssoleAppAids.h

	File Synopsis:      This C/C++ header file defines the functions exported by
						NativeConssoleAppAids.dll, along with a few symbolic
						constants used by it.

	Remarks:            These functions were defined and tested for the projects
						that I created to port three open source libraries, zlib,
						iconv, and libxml2, to the ARM processor.

	Date Created:       Tuesday, 19 March 2019

	License:            Copyright (C) 2019, David A. Gray. All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	*   Redistributions of source code must retain the above copyright notice,
	this list of conditions and the following disclaimer.

	*   Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in the
	documentation and/or other materials provided with the distribution.

	*   Neither the name of David A. Gray nor the names of his contributors may
	be used to endorse or promote products derived from this software without
	specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED. IN NO EVENT SHALL David A. Gray BE LIABLE FOR ANY DIRECT,
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	----------------------------------------------------------------------------
	Revision History
	----------------------------------------------------------------------------

	Date       By  Synopsis	RCDATA_MAX_BUFFER_P6C
	---------- --- -------------------------------------------------------------
	2019/03/21 DAG Header created and first used in VSProjectSettingsTester.exe

	2019/03/22 DAG WaitForCarbonUnit added, ProgramIDFromArgV implemented for
	               both ANSI and wide character (Unicode) strings, everything
				   else implemented for ANSI and Unicode strings and all
				   function arguments documented

	2019/03/23 DAG GetFileVersion now uses the Windows heap allocators directly,
	               while ProgramIDFromArgV returns through memcpy. The first
				   change eliminates a reliance on the CRT memory allocators,
				   which I seldom use, to avoid the overhead of having the CRT
				   library turn around and call the Windows heap allocators,
				   adding nothing of value. The second change eliminates wasted
				   machine instructions that load a value into the EAX register
				   that memcpy already put there.
	============================================================================
*/

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
	#pragma once
#endif  /*  #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

#if defined ( NATIVECONSSOLEAPPAIDS_EXPORTS )
	#define LIBSPEC_NATIVECONSSOLEAPPAIDS_API __declspec(dllexport) __stdcall
#else
	#define LIBSPEC_NATIVECONSSOLEAPPAIDS_API __declspec(dllimport) __stdcall
#endif	/* NATIVECONSSOLEAPPAIDS_EXPORTS */

typedef enum _STATUS_CODE_FORMAT2
{
	SCF2_HEXADECIMAL ,   // 0
	SCF2_DECIMAL ,       // 1
	SCF2_OCTAL           // 2
} STATUS_CODE_FORMAT2;

#define FB_HIDE_LENGTH					0x00000000

#define FB_SCF2_HEXADECIMAL             SCF2_HEXADECIMAL
#define FB_SCF2_DECIMAL                 SCF2_DECIMAL
#define FB_SCF2_OCTAL                   SCF2_OCTAL

typedef       STATUS_CODE_FORMAT2       FB_STATUS_CODE_FORMAT2;
typedef const STATUS_CODE_FORMAT2       CSTATUS_CODE_FORMAT2;
typedef const FB_STATUS_CODE_FORMAT2    CFB_STATUS_CODE_FORMAT2;

#if !defined ( _CONST_TYPEDEFS_WW_INCLUDED )
	typedef const DWORD					CDWORD;
	typedef const INT					CINT;
	typedef const HMODULE               CHMODULE;
	typedef unsigned int * const        CLPUINT;
	typedef const unsigned int          CUINT;
	typedef const unsigned int          RES_STRING_ID;
#endif	/* #if !defined ( _CONST_TYPEDEFS_WW_INCLUDED ) */

#define GFV_SUCCEEDED					0x00000000
#define GFV_GETFILEVERSIONINFOSIZE_FAIL	0x00000001
#define GFV_GETFILEVERSIONINFO_FAIL		0x00000002
#define GFV_VERQUERYVALUE_FAIL			0x00000003

#define IBF_USE_DEFAULT_HEAP            NULL

//	----------------------------------------------------------------------------
//	Define the CRTWaitForCarbonUnit data structure and a pointer to it for use
//	by calling routines to pass parameters to WaitForCarbounUnit.
//
//	2019/03/22 - DAG - Since pointers are 64-bit entities when the platform is a
//                     64 bit platform, such as x64, but are 32-bit entities on
//                     a classic Win32 (32-bit) platform, I moved lpszMessage
//                     from the top to the bottom of the list.
//	----------------------------------------------------------------------------

#pragma pack ( push , 1 )               // Make the structure as compact as possible.
typedef struct _CRTWaitForCarbonUnit
{
	DWORD   dwDuration;
	DWORD   dwFreqquency;
	int     intReturnCode;
	TCHAR * lpszMessage;
}   CRTWaitForCarbonUnit , FAR * LPCRTWaitForCarbonUnit;
#pragma pack ( pop )

#if defined ( __cplusplus )
extern "C" {
#endif  /* #if defined ( __cplusplus ) */
	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API FB_FindLineEndA
	(
		LPCTSTR              plpString ,
		CINT                 pintPosEnd
	);

	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API FB_FindLineEndW
	(
		LPCTSTR              plpString ,
		CINT                 pintPosEnd
	);


	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API FB_FormatMessageA
	(
		LPCTSTR              plpHint ,											// Pointer to string to give context to the displayed message
		CDWORD               pdwLastError ,										// Status code for which to format message, or NO_ERROR (zero) to cause GetLastError to be called
		CSTATUS_CODE_FORMAT2 penmCodeFormat										// Status code format selector (decimal, hexadecimal, or octal)
	);

	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API FB_FormatMessageW
	(
		LPCTSTR              plpHint ,											// Pointer to string to give context to the displayed message
		CDWORD               pdwLastError ,										// Status code for which to format message, or NO_ERROR (zero) to cause GetLastError to be called
		CSTATUS_CODE_FORMAT2 penmCodeFormat										// Status code format selector (decimal, hexadecimal, or octal)
	);


	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API FB_FormatMessage2A
	(
		RES_STRING_ID		 puintStringID ,									// Resource ID of string to give context to the displayed message
		CDWORD               pdwLastError ,										// Status code for which to format message, or NO_ERROR (zero) to cause GetLastError to be called
		CSTATUS_CODE_FORMAT2 penmCodeFormat										// Status code format selector (decimal, hexadecimal, or octal)
	);

	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API FB_FormatMessage2W
	(
		RES_STRING_ID		 puintStringID ,									// Resource ID of string to give context to the displayed message
		CDWORD               pdwLastError ,										// Status code for which to format message, or NO_ERROR (zero) to cause GetLastError to be called
		CSTATUS_CODE_FORMAT2 penmCodeFormat										// Status code format selector (decimal, hexadecimal, or octal)
	);


	DWORD LIBSPEC_NATIVECONSSOLEAPPAIDS_API FB_ProcessStatusCode
	(
		CDWORD pdwLastError														// Status code to establish, or NO_ERROR (zero) to cause GetLastError to be called
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      GetExeHameFromWindows
	//
	//  Abstract:           Get a pointer to a null terminated string that holds
	//                      the absolute (fully qualified) name of the first
	//                      program file that was loaded into the current
	//                      process.
	//
	//  In:                 This function takes no arguments.
	//
	//  Out:                If it succeeds, the return value is a pointer to the
	//                      desired null terminated Unicode program name string.
	//
	//  Remarks:            Since this routine supports only Unicode strings, it
	//                      has a return type of LPWSTR.
	//  ------------------------------------------------------------------------

	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API GetExeHameFromWindowsA ( );

	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API GetExeHameFromWindowsW ( );


	//  ------------------------------------------------------------------------
	//  Function Name:      GetFileVersion
	//
	//  Abstract:           Get a pointer to a null terminated string that holds
	//                      the numerical version number string stored in the
	//                      program file named in its first argument.
	//
	//  In:                 plpOutBuf				= Pointer to buffer to
	//                                                receive the formatted full
	//                                                version number string as
	//                                                up to pintOutBufSize - 1
	//                                                wide characters
	//
	//						pintOutBufSize			= Capacity of buffer 
	//                                                plpOutBuf, in wide 
	//                                                characters
	//
	//                      plpAbsoluteExeFileName	= Pointer to string that
	//                                                contains the absolute
	//                                                (fully qualified) name of
	//                                                the program file
	//
	//  Out:                If it succeeds, the return value is a pointer to the
	//                      desired null terminated Unicode numerical program 
	//						version sring.
	//
	//  Remarks:            Since this routine runs in a character mode host, it
	//						writes its result on the console output string, and
	//						returns a status code, which is expected to be zero.
	//  ------------------------------------------------------------------------

	int     LIBSPEC_NATIVECONSSOLEAPPAIDS_API GetFileVersionA
	(
		LPTSTR			plpOutBuf ,							// Pointer to buffer to receive formatted full version number string as up to pintOutBufSize - 1 wide characters
		CINT			pintOutBufSize ,					// Capacity of buffer plpOutBuf in wide characters
		LPCTSTR         plpAbsoluteExeFileName				// Pointer to string containing the absolute (fully qualified) name of the program file
	);

	int     LIBSPEC_NATIVECONSSOLEAPPAIDS_API GetFileVersionW
	(
		LPTSTR			plpOutBuf ,							// Pointer to buffer to receive formatted full version number string as up to pintOutBufSize - 1 wide characters
		CINT			pintOutBufSize ,					// Capacity of buffer plpOutBuf in wide characters
		LPCTSTR         plpAbsoluteExeFileName				// Pointer to string containing the absolute (fully qualified) name of the program file
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      GetANSIStringPointer (ANSI, narrow characters)
	//						GetUnicodeStringPointer (Unicode, wide characters)
	//
	//  Abstract:           Get a pointer to a null terminated string resource
	//                      for use, in situ, by any routine that deals in such
	//                      strings.
	//
	//						IMPORTANT:	Since GetANSIStringPointer must use an
	//									output buffer, and it is common for two
	//									or more strings to be used together,
	//									such as a format string and a token
	//									replacement string being fed into printf
	//									or one of its kin, it allocates a buffer
	//									from the default process heap. Unless
	//									your code discards it, your program will
	//									leak 4098 bytes of memory per abandoned
	//									buffer.
	//
	//  In:                 phSourceModule	= either the instance handle of the
	//                                        the module from which the string
	//                                        was expected to be read, or NULL,
	//                                        indicating that the source is the
	//                                        first PE file that was loaded into
	//                                        the current process.
	//
	//                      puintStringID	= the unsigned integer resource
	//                                        (string) ID that was sought.
	//
	//                      plpuintLength	= the location where the length of
	//                                        of the returned string should be 
	//                                        written, if the calling routine
	//                                        needs it. Otherwise, the pointer
	//                                        may be NULL.
	//
	//  Out:                If it succeeds, the return value is a pointer to the
	//                      desired null terminated Unicode string resource. If
	//                      the desired string cannot be found in the specified
	//                      module, the return value is NULL, and a call to
	//                      GetLastError should give some hint about why the
	//                      call failed.
	//
	//  Remarks:            Since this routine supports only Unicode strings, it
	//                      has a return type of LPWSTR.
	//
	//                      The documented return value of LoadString excludes
	//                      the trailing null from the reported string length.
	//                      However, when nBufferMax = RCDATA_INPLACE_POINTER,
	//                      it is included. Hence, for consistency, this routine
	//                      deducts one from the return value when reporting the
	//                      length of the string.
	//  ------------------------------------------------------------------------

	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API GetANSIStringPointer
	(
		CHMODULE        phSourceModule ,					// HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
		RES_STRING_ID	puintStringID ,						// Resource ID of string to load
		CLPUINT         plpuintLength						// Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
	);

	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API GetUnicodeStringPointer
	(
		CHMODULE        phSourceModule ,					// HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
		RES_STRING_ID	puintStringID ,						// Resource ID of string to load
		CLPUINT         plpuintLength						// Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
	);


	//  ========================================================================
	//
	//  Function Name:  IsBufFerFromHeap
	//
	//  Synopsis:       Determine whether a pointer belongs to a specified heap.
	//
	//  Status:         Beginning with version 1, 9, 0, 4, this function is no
	//                  longer used internally, and external use is deprecated.
	//                  Please see the Remarks for an explanation of why this is
	//					so.
	//
	//  In:             plpvBuf     = Pointer to buffer to test.
	//
	//                  phHeap      = Handle to heap to be examined. If phHeap
	//                                is NULL, get a handle to the process heap,
	//                                and evaluate it.
	//
	//  Out:            TRUE if buffer plpvBuf belongs to heap phHeap.
	//                  FALSE if buffer plpvBuf belongs to heap phHeap.
	//
	//                  To be on the safe side, return FALSE if any exception
	//                  occurs. See Remarks.
	//
	//                  If IsBufFromHeap_WW returns FALSE, call GetLastError(),
	//                  report the error directly or through FormatMessage(),
	//                  and terminate.
	//
	//  Remarks:        DEPRECATED: The original intent of this function was to
	//                              validate a heap pointer before treating it
	//                              as such. The behavior of the heap routines
	//                              in Windows 7 makes this abad idea, because
	//                              it runs the risk of raising avoidable
	//                              breakpoint exceptions, even in retail builds
	//                              of the calling code. Since HeapAlloc and
	//                              HeapReAlloc fail with a trappable exception,
	//                              it seems more prudent to go ahead and call
	//                              them, and forgo the pointer sanity check.
	//
	//                  Call this function before you attempt to treat any
	//                  pointer as a heap pointer (e. g., to free the associated
	//                  memory, or reallocate the associated buffer.
	//
	//                  IMPORTANT:  Unless plpvBuf is the address of a memory
	//                              block that was allocated from the default
	//                              process heap, this routine generate the
	//                              following message, when the routine runs in
	//                              a debugger.
	//
	//                                      User breakpoint called from code
	//
	//                              This message cannot be suppressed. However,
	//                              when you acknowledge the message box, your
	//                              code continues to execute normally, but the
	//                              exception is noted in the Debug output
	//                              window.
	//
	//                              Outside a debugger, there is no outward sign
	//                              of this first-chance exception, and the code
	//                              behaves as expected and intended, UNLESS the
	//                              code runs on Windows 7 and newer, which is
	//                              why its use is deprecated, and it has been
	//                              written out of the other routines in this
	//                              library that used it.
	//  ============================================================================

	BOOL LIBSPEC_NATIVECONSSOLEAPPAIDS_API IsBufFerFromHeap
	(
		HANDLE phHeap ,
		LPVOID plpvBuf
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      ProgramIDFromArgV
	//
	//  Abstract:           Get a pointer to a null terminated string resource
	//                      for use, in situ, by any routine that deals in such
	//                      strings.
	//
	//  In:                 plpszArg0    	= pointer to argv [0], which always
	//                                        contains the name of the program
	//                                        that started the process
	//
	//  Out:                If it succeeds, the return value is a pointer to a
	//                      null terminated Unicode string that conatins the
	//                      base name of the program, with both its path and its
	//                      extension removed.
	//
	//  Remarks:            Since this routine supports only Unicode strings, it
	//                      has a return type of LPWSTR.
	//  ------------------------------------------------------------------------

	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API ProgramIDFromArgVA
	(
		LPCTSTR			plpszArg0							// Pointer to argv [0], which always contains the name of the program that started the process
	);

	LPTSTR LIBSPEC_NATIVECONSSOLEAPPAIDS_API ProgramIDFromArgVW
	(
		LPCTSTR			plpszArg0							// Pointer to argv [0], which always contains the name of the program that started the process
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      ReportSystemError
	//
	//  Abstract:           Use FormatMessage to translate the system status code
	//						returned by a system (Windows API) routine into a
	//						message for consumption by carbon units.
	//
	//  In:                 pintFinalReturnCode	= the value to pass through and
	//                                            report to Windows as the final
	//                                            status code of the program
	//
	//  Out:                This function always returns its input value.
	//
	//  Remarks:            Since this routine runs in a character mode host, it
	//						writes its result on the console output string, and
	//						returns a status code, which is expected to be zero.
	//  ------------------------------------------------------------------------

	int     LIBSPEC_NATIVECONSSOLEAPPAIDS_API ReportSystemErrorA
	(
		CINT            pintFinalReturnCode ,
		RES_STRING_ID   puintResStringId
	);

	int     LIBSPEC_NATIVECONSSOLEAPPAIDS_API ReportSystemErrorW
	(
		CINT            pintFinalReturnCode ,
		RES_STRING_ID   puintResStringId
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      ShowPlatform
	//
	//  Abstract:           Display the platform (Win32, Win64, ARM, or ARM64 if
	//						the information is supplied through a preprocessor
	//						symbol.
	//
	//  In:                 plpszFormatString	= template (format control)
	//                                            string to use to display the
	//											  platform if it is known
	//
	//  Out:                This function reports via the caller's console
	//						output stream, and has no return value.
	//
	//  Remarks:            Since plpszFormatString is expected to point to the
	//						buffer allocated by GetANSIStringPointer to hold the
	//						message template, this routine 
	//						This routine performs at most one call to wprintf.
	//						If all of the expected preprocessor symbols are
	//						undefined, it displays a message to that effect.
	//  ------------------------------------------------------------------------

	void    LIBSPEC_NATIVECONSSOLEAPPAIDS_API ShowPlatformA
	(
		LPCTSTR			plpszFormatString
	);

	void    LIBSPEC_NATIVECONSSOLEAPPAIDS_API ShowPlatformW
	(
		LPCTSTR			plpszFormatString
	);


	//  ------------------------------------------------------------------------
	//  Function Name:      ShowProgramInfo
	//
	//  Abstract:           Get a pinter to a null terminated string resource
	//                      for use, in situ, by any routine that deals in such
	//                      strings.
	//
	//  Out:                If it succeeds, the return value is a pointer to a
	//						string that contains the program name. Otherwise, it
	//						returns a NULL pointer to indicate failure.
	//
	//  Remarks:            Since this routine runs in a character mode host, it
	//						writes its result on the console output string, and
	//						returns a status code, which is expected to be zero.
	//  ------------------------------------------------------------------------

	LPTSTR     LIBSPEC_NATIVECONSSOLEAPPAIDS_API ShowProgramInfoA ( );

	LPTSTR     LIBSPEC_NATIVECONSSOLEAPPAIDS_API ShowProgramInfoW ( );


	//  ------------------------------------------------------------------------
	//  Function Name:      WaitForCarbounUnit
	//
	//  Abstract:           Display a prompt, then suspend execution of the
	//						calling routine until a carbon unit (a human being)
	//						presses the RETURN (Enter) key on the keyboard.
	//
	//  In:                 plpCRTWaitForCarbonUnit	= const pointer to the
	//                                                CRTWaitForCarbonUnit data
	//												  structure that provides
	//												  its operating parameters
	//
	//  Out:                If it succeeds, the return value is zero. Otherwise,
	//						it returns a system status code, which may be fed to
	//						the FormatMessage Windows API routine, directly or
	//						through sibling routine FB_FormatMessage.
	//
	//  Remarks:            Since this routine supports ANSI and wide character
	//						prompt strings, it has two implementations which are
	//						otherwise identical.
	//
	//                      The following table describes the values of the four
	//						CRTWaitForCarbonUnit members, of which three are
	//						inputs, while the fourth is a copy of the output.
	//
	//                          ------------------------------------------------
	//                          Type    Name          Usage and Default
	//							------- ------------- --------------------------
	//							TCHAR * lpszMessage   pointer to prompt string,
	//												  for which a default, 
	//												  "Please press the Return 
	//												  (ENTER) key to exit the
	//												  program." is used when
	//                                                lpszMessage is NULL
	//
	//							DWORD   dwDuration    time, in milliseconds, for
	//                                                which to emit the beep
	//                                                that accompanies the
	//                                                prompt, which defaults to
	//                                                750 milliseconds if zero
	//
	//							DWORD   dwFreqquency  frequency, in hertz, of
	//                                                the beep that is emitted
	//                                                to alert an operator to
	//                                                the prompt, which defaults
	//												  to 880 hertz if zero
	//
	//							int     intReturnCode copy of the return code in
	//                                                case the calling routine
	//                                                discarded the return value
	//  ------------------------------------------------------------------------

	int        LIBSPEC_NATIVECONSSOLEAPPAIDS_API WaitForCarbounUnitA
	(
		const LPCRTWaitForCarbonUnit plpCRTWaitForCarbonUnit
	);
	int        LIBSPEC_NATIVECONSSOLEAPPAIDS_API WaitForCarbounUnitW
	(
		const LPCRTWaitForCarbonUnit plpCRTWaitForCarbonUnit
	);
#if defined ( __cplusplus )
}   /* ... extern "C" */
#endif  /* #if defined ( __cplusplus )    */

//	----------------------------------------------------------------------------
//	Map the ANSI and Unicode (wide character) routines to common names by which 
//	they may be called in the context of either encoding.
//	----------------------------------------------------------------------------

#if defined ( UNICODE )
	#define FB_FindLineEnd			FB_FindLineEndW
	#define FB_FormatMessage		FB_FormatMessageW
	#define FB_FormatMessage2		FB_FormatMessage2W
	#define GetExeHameFromWindows	GetExeHameFromWindowsW
	#define GetFileVersion			GetFileVersionW
	#define GetStringPointer		GetUnicodeStringPointer
	#define ProgramIDFromArgV		ProgramIDFromArgVW
	#define ReportSystemError		ReportSystemErrorW
	#define ShowPlatform			ShowPlatformW
	#define ShowProgramInfo			ShowProgramInfoW
	#define WaitForCarbounUnit		WaitForCarbounUnitW
#else
	#define FB_FindLineEnd			FB_FindLineEndA
	#define FB_FormatMessage		FB_FormatMessageA
	#define FB_FormatMessage2		FB_FormatMessage2A
	#define GetExeHameFromWindows	GetExeHameFromWindowsA
	#define GetFileVersion			GetFileVersionA
	#define GetStringPointer		GetANSIStringPointer
	#define ProgramIDFromArgV		ProgramIDFromArgVA
	#define ReportSystemError		ReportSystemErrorA
	#define ShowPlatform			ShowPlatformA
	#define ShowProgramInfo			ShowProgramInfoA
	#define WaitForCarbounUnit		WaitForCarbounUnitA
#endif	/* #if defined ( UNICODE ) */
#endif	/* _NATIVECONSSOLEAPPAIDS_DEFINED */