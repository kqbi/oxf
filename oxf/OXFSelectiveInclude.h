//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: SelectiveInclude
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.


#ifndef OXFSelectiveInclude_H
#define OXFSelectiveInclude_H

//## package Design::oxf::Services::SelectiveInclude


//#[ ignore
// Compilation dependent include statements
//#]

// Compilation dependent include settings for animation support
//#[ type ANIM_INCLUDE
#ifdef ANIM_USE_IOSTREAM
#ifndef OM_FORCE_IOSTREAM
#define OM_FORCE_IOSTREAM
#endif // !OM_FORCE_IOSTREAM
#elif (defined ANIM_USE_STDIO)
#ifdef OM_FORCE_IOSTREAM
#undef OM_FORCE_IOSTREAM
#endif // OM_FORCE_IOSTREAM
#ifndef OM_FROCE_STDIO
#define OM_FROCE_STDIO
#endif // !OM_FROCE_STDIO
#endif // ANIM_USE_IOSTREAM
//#]

// Forcing usage of iostream
// Has higher priority than OM_FORCE_STDIO
//#[ type OM_FORCE_IOSTREAM
#ifdef OM_FORCE_IOSTREAM
// force iostream settings by disable of stdio settings
// and defining USE_IOSTREAM
#ifdef OM_FROCE_STDIO
#undef OM_FROCE_STDIO
#endif // OM_FROCE_STDIO

#ifdef OM_FORCE_STDIO
#undef OM_FORCE_STDIO
#endif // OM_FORCE_STDIO

#ifndef USE_IOSTREAM
#define USE_IOSTREAM
#endif // !USE_IOSTREAM
#endif //OM_FORCE_IOSTREAM
//#]

// Forcing usage of stdio
//#[ type OM_FORCE_STDIO
#if (defined OM_FROCE_STDIO || defined OM_FORCE_STDIO)
// OM_FROCE_STDIO is kept for backward compatibility
#ifdef USE_IOSTREAM
#undef USE_IOSTREAM
#endif // USE_IOSTREAM
#ifndef USE_STDIO
#define USE_STDIO
#endif // USE_STDIO
#endif // if (defined OM_FROCE_STDIO || defined OM_FORCE_STDIO)
//#]

// if BOTH USE_IOSTREAM and USE_STDIO are defined
// use iostreams
//#[ type favor_iostream
#if (defined(USE_IOSTREAM) && defined(USE_STDIO))
#undef USE_STDIO
#endif // (defined(USE_IOSTREAM) && defined(USE_STDIO))
//#]

// Compilation dependent include to iostream
//#[ type IOSTREAM_INCLUDE
#ifdef USE_IOSTREAM
#if (defined(OM_STL) && !defined(OM_NO_STD_STRING))
#include <iostream>
#else
#include <iostream.h>
#endif // (defined(OM_STL) && !defined(OM_NO_STD_STRING))
#endif // USE_IOSTREAM
//#]

// Compilation dependent include to cstdlib
//#[ type STDLIB_INCLUDE
#ifndef NO_STDLIB
#if (defined(OM_STL) && !defined(OM_NO_STD_STRING))
#include <cstdlib>
#else
#include <stdlib.h>
#endif // (defined(OM_STL) && !defined(OM_NO_STD_STRING))
#endif // NO_STDLIB
//#]

// Compilation dependent include to cstdio
//#[ type STDIO_INCLUDE
#ifndef OM_NO_OS_STDIO_INCLUDE
#ifdef OM_STL
#include <cstdio>
#else
#include <stdio.h>
#endif // OM_STL
#endif // OM_NO_OS_STDIO_INCLUDE
//#]

// Compilation dependent include to cctype
//#[ type CTYPE_INCLUDE
#ifdef OM_STL
#include <cctype>
#else
#include <ctype.h>
#endif // OM_STL
//#]

// Compilation dependent include to cstring
//#[ type STRING_INCLUDE
#if (defined(OM_STL) && !defined(OM_NO_STD_STRING))
#include <cstring>
#else
#include <string.h>
#endif // (defined(OM_STL) && !defined(OM_NO_STD_STRING))
//#]

#endif



