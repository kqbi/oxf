#ifndef OMOSCONFIG_H
#define OMOSCONFIG_H "$Id: omosconfig.h 1.11 2007/03/11 12:51:34 ilgiga Exp $"
//
//	file name   :	omosconfig.h
//
//	purpose:	 	Microsoft adaptor OS configuration file
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2002, 2018. All Rights Reserved.
//
//  Note to U.S. Government Users Restricted Rights:  
//  Use, duplication or disclosure restricted by GSA ADP Schedule 
//  Contract with IBM Corp.
//

//////////////////////////////////
// flags
//////////////////////////////////
#ifdef _WIN32_WCE
#define OM_NO_MC_SUPPORT
#define OM_OS_NO_EXCEPTIONS			// no exception support
#define OM_NO_OS_ASSERT				// no assert() support
#define OM_NO_OS_STDIO_INCLUDE		// no stdio.h (use windows.h)
#define OM_NO_OS_REPLACEMENT_NEW	// no global replacement new/delete operators
#define OM_NO_NOTHROW_NEW_SUPPORT	// WINCE doesn't support nothrow format of new/delete
#else // !_WIN32_WCE
#if !(defined OMOMATE && defined _DEBUG)
#define HAS_EXP_CATCHING_SIGNALS	// support exceptions
#endif // !(defined OMOMATE && defined _DEBUG)
#define USE_IOSTREAM	// use iostreams
#define OM_USE_MULTIMEDIA_TIMER
#endif // _WIN32_WCE

// user can define OM_USE_STATIC_MEMORY_POOL_INITIALIZATION and recompile framework  
// to initialize static memory pool in pre-main phase of run time execution. 
// It prevents racing between several threads, which try to use the same memory pool.
// This flag cannot be used if user defines own memory manager.

// #define OM_USE_STATIC_MEMORY_POOL_INITIALIZATION


#if (defined _WIN32_WCE || defined BORLAND)
#define OM_NO_LONG_LONG_SUPPORT		// no long long support in WinCE 4.2 and Borland
#endif // (defined _WIN32_WCE || defined BORLAND)

#ifdef unix // For Rhapsody on Solaris
#define OM_CATCH_SIGBUS
#define OM_CATCH_SIGFPE
#define OM_CATCH_SIGABRT
#define OM_CATCH_SIGILL
#define OM_STD_IFSTREAM_CREATION
#endif // unix

#define OM_SEARCH_ENV(name,searchpath,path) _searchenv(name, searchpath, path) 

#ifdef _MSC_VER

	// disable Microsoft compiler warning (debug information truncated)
	#pragma warning(disable: 4786)

	#if (_MSC_VER >= 1300) //Visual C++ .NET or later
		#ifndef _WIN32_WCE
			#ifndef OM_STL
				#define OM_STL
			#endif // OM_STL
		#endif // _WIN32_WCE
	#endif //_MSC_VER >= 1300
#endif //_MSC_VER

#ifdef RTX
#define HAS_NO_EXP
#endif // RTX

#ifdef WIN32
#define OM_ENABLE_DLL
#if (_MSC_VER < 1900) // VS2013 or older
  #define OM_NEW_OPERATOR_NEEDS_DUMMY_PARAM
#endif
#define OM_OS_NEED_EXPLICIT_DISABLE_COPY_CTOR
#define OM_NEED_GETENV
#define OM_WIN32_COMPILER_DISABLE_WARNING_4244
#define OM_WIN32_COMPILER_DISABLE_WARNING_4312
#define OM_OS_SHORT_STRSTREAM_FILE_NAME
#pragma warning ( disable : 4710 )
#endif

#ifdef BORLAND
#define OM_OS_NEED_EXPLICIT_ADDRESS_DUMP_OPERATOR
#define OM_OS_NEEDS_CONST_VOID_DUMP_OPERATOR
#endif // BORLAND

////////////////////////////////
// include files 
////////////////////////////////
#ifdef _WIN32_WCE
#include <windows.h>
#define atoll atol
#endif // _WIN32_WCE

#ifdef BORLAND
#include <windows.h>
#endif // BORLAND

#ifdef OMOMATE
#define OM_OS_SSTREAM_FILE_NAME
#define OM_USE_STL_STRING_STREAM
#pragma warning( push, 3 )
#include <fstream>
#include <sstream>
#pragma warning ( pop )
#include <afx.h>
typedef  DWORD64 gen_ptr;
#else
typedef  void * gen_ptr;
#endif

typedef  void * OMOSHandle;

#ifdef _WINDU_SOURCE
// Needed for smooth porting to UNIX under Bristol
#include <windu_platform.h>
#endif

#ifdef unix
#include <unistd.h>
#include <stdio.h>
#endif // unix

/////////////////////////////////
// Macros
/////////////////////////////////
#ifdef OMOMATE
#define OMString CString
#endif 

#ifdef unix
#define OMitoa(val,str,radix) sprintf(str,"%d",val)
#endif // unix

#ifdef BORLAND
#define OMitoa itoa
#endif // BORLAND

#ifndef OMitoa
#define OMitoa _itoa
#endif

typedef enum {OMPwrModeNone = 0}  OMPowerMode_t;

#define OM_NOTIFY_ERROR(call,func)

#endif // OMOSCONFIG_H

//$Log: omosconfig.h $
//Revision 1.11  2007/03/11 12:51:34  ilgiga
//Change copyright comment
//Revision 1.10  2007/03/01 16:23:30  ilgiga
//Telelogic instead of i-Logix
//Revision 1.9  2004/01/19 14:00:31  eldad
//OM_SEARCH_ENV
//Revision 1.8.1.2  2004/01/19 13:34:43  vova
//Revision 1.8  2003/10/08 14:33:55  vova
//Multiple definition of OM_WIN32_COMPILER_DISABLE_WARNING_4244 removed
//Revision 1.7  2003/01/20 15:18:48  avrahams
//bug fix 61035 - add more signals catchings for omtry
//Revision 1.6  2003/01/09 12:29:53  Eldad
//Fix b#61053
//Revision 1.5  2002/12/03 13:34:25  amos
//remove the block on loading of "OMTracer.cfg" in Borlad 5.5
//Revision 1.4  2002/12/02 17:49:46  gio
//Added for Borland BCC55 adapter:
//#define OM_NO_TRACER_FILE
//Revision 1.3  2002/11/27 12:18:02  gio
//Definitions for Borland bcc55 adapter:
//#define OM_OS_NEEDS_CONST_VOID_DUMP_OPERATOR
//Revision 1.2  2002/07/15 12:32:14  avrahams
//Set OM_STL when compiled by .NET
//Revision 1.1  2002/07/09 14:36:24  amos
//Initial revision
