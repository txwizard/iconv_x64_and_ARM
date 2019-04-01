// StringEncoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#undef UNICODE
#undef _UNICODE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "AppHelpers.h"

#include "..\include\iconv.h"

int main ( int argc , char * argv [ ] )
{
	int rintRC = 0;

	if ( ( rintRC = ShowProgramInfo ( argv [ 0 ] ) ) )
	{
		printf ( "StringEncoder aborted" );
		return rintRC;
	}	// if ( ( rc = ShowProgramInfo ( argv [ 0 ] ) ) )

	char	achrTestString [ ]	= "This is a test. This is only a test.";
	char	dest_str [ 100 ];

	char *	gbk_str				= achrTestString;
	char *	out					= dest_str;
	size_t	inbytes				= strlen ( gbk_str );
	size_t	outbytes			= sizeof dest_str;
	iconv_t	conv				= iconv_open ( "ISO-8859-1//TRANSLIT" , "UTF-8" );

	if ( conv == ( iconv_t ) -1 )
	{
		perror ( "iconv_open" );
		return 1;
	}	// if ( conv == ( iconv_t ) -1 )

	if ( iconv ( conv , ( ICONV_CONST char* *)  &gbk_str , &inbytes , &out , &outbytes ) == ( size_t ) -1 )
	{
		perror ( "iconv" );
		return 1;
	}	// if ( iconv ( conv , &gbk_str , &inbytes , &out , &outbytes ) == ( size_t ) -1 )

	dest_str [ sizeof dest_str - outbytes ] = 0;
	printf ( dest_str );

	return rintRC;
}	// int wmain