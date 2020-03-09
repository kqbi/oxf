//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: BasicTypes
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


#ifndef rawtypes_H
#define rawtypes_H

//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency omiotypes
#include "omiotypes.h"
//## dependency OMValueCompare
#ifdef OM_STL
#include "OMValueCompare.h"
#endif

//## dependency SelectiveInclude
#include "OXFSelectiveInclude.h"
//## dependency Types
#include "OXFTypes.h"
//## package Design::oxf::Services::Types::BasicTypes


//#[ ignore
// Basic framework implementation types definition.
//#]

// Undefined type for modeling, based on integer.
//## type Untyped
typedef int Untyped;

// This type has 32 bit or 64 bit length depending on processor architecture
//#[ type Rhp_uintptr_t
typedef size_t Rhp_uintptr_t;

//#]

// OMAPPLICATION indicates that the framework is used by a client application.
// OMOMATE indicates that the framework is used by Rhapsody.
//#[ type OMAPPLICATION
#ifndef OMOMATE
// application
#ifndef OMAPPLICATION
#define OMAPPLICATION
#endif
#else
// check that there is no multiple definition
#ifdef OMAPPLICATION
// Protect against both flags 'on'
#error "'OMOMATE' and 'OMAPPLICATION' cannot be defined together"
#endif // OMAPPLICATION
#endif // OMOMATE
//#]

// Backward compatibility for spelling fix
//#[ type UseNullBlockContainter
#ifdef UseNullBlockContainter
#ifndef OMUseNullBlockContainer
#define OMUseNullBlockContainer
#endif // OMUseNullBlockContainer
#endif // UseNullBlockContainter
//#]

// Selective include to OMString
//#[ type IncludeOMString
#ifdef OMAPPLICATION
#include "omstring.h"
#endif // OMAPPLICATION
//#]

// Language independent boolean type supported by Rhapsody.
//## type RhpBoolean
typedef bool RhpBoolean;

// Language independent character type supported by Rhapsody.
//## type RhpCharacter
typedef char RhpCharacter;

// Language independent address type supported by Rhapsody.
//## type RhpAddress
typedef void * RhpAddress;

// Language independent integer type supported by Rhapsody.
//## type RhpInteger
typedef int RhpInteger;

// Language independent positive integer type supported by Rhapsody.
//## type RhpPositive
typedef unsigned int RhpPositive;

// Language independent real number type supported by Rhapsody.
//## type RhpReal
typedef double RhpReal;

// Language independent string type supported by Rhapsody.
//## type RhpString
typedef OMString RhpString;

// Language independent natural number type supported by Rhapsody.
//## type RhpUnlimitedNatural
typedef long RhpUnlimitedNatural;

// Language independent VOID type supported by Rhapsody.
//## type RhpVoid
typedef void RhpVoid;

// OMBoolean false value
//#[ type FALSE
#ifndef OM_DISABLE_TRUE_FALSE_DEFINITIONS
#ifndef FALSE
#define FALSE false
#endif // FALSE
#endif // OM_DISABLE_TRUE_FALSE_DEFINITIONS
//#]

// OMBoolean true value
//#[ type TRUE
#ifndef OM_DISABLE_TRUE_FALSE_DEFINITIONS
#ifndef TRUE
#define TRUE true
#endif // TRUE
#endif // OM_DISABLE_TRUE_FALSE_DEFINITIONS
//#]

// OMitoa declaration
//#[ type OMitoa
#ifndef OMitoa
extern void OMitoa(Rhp_int32_t val, Rhp_char_pt str, Rhp_int32_t base = 10);
#endif // OMitoa 
//#]

// Boolean type
//## type OMBoolean
typedef RhpBoolean OMBoolean;

// Compilation dependent addition of the inline keyword in the definition of template classes operations
//#[ type TMPL_INL
#ifdef NEED_INLINE_IN_TEMPLATE
#define TMPL_INL inline
#else
#define TMPL_INL
#endif // NEED_INLINE_IN_TEMPLATE
//#]

// OMHandles - the "names" of various model objects.
//## type OMHandle
typedef char OMHandle;

// default memory alignment
//#[ type OMRAW_MEMORY_ALIGNMENT
#ifndef OMRAW_MEMORY_ALIGNMENT
#define OMRAW_MEMORY_ALIGNMENT 8
#endif // OMRAW_MEMORY_ALIGNMENT
//#]

// dynamic memory allocation exists (new/delete)
//#[ type USE_DYNAMIC_MEMORY_ALLOCATION
#ifndef OM_NO_DYNAMIC_MEMORY_ALLOCATION
#define USE_DYNAMIC_MEMORY_ALLOCATION
#endif // OM_NO_DYNAMIC_MEMORY_ALLOCATION
//#]

// A reactive object default active context
//#[ type OMDefaultThread
#define OMDefaultThread NULL
//#]

// set the _OMINSTRUMENT flag
//#[ type _OMINSTRUMENT
#if (defined OMTRACER || defined OMANIMATOR)
#ifndef _OMINSTRUMENT
#define _OMINSTRUMENT
#endif // _OMINSTRUMENT
#endif // (defined OMTRACER || defined OMANIMATOR)
//#]

// AOM Argument declaration
//#[ type aomArg
#ifdef _OMINSTRUMENT
#define aomArg(arg) arg
#else
#define aomArg(arg)
#endif // _OMINSTRUMENT
//#]

// Define omtypename to allow environment dependent usage of the typename keyword
//#[ type omtypename
#ifndef OM_NO_TYPENAME_SUPPORT
#define omtypename typename
#else
// avoid the typename keyword
#define omtypename
#endif // OM_NO_TYPENAME_SUPPORT
//#]

// This macro definition is needed for backward compatibility
//#[ type OM_NEED_THROW_IN_NEW_OPERATOR
#ifdef OM_NEED_THORW_IN_NEW_OPERATOR
#define OM_NEED_THROW_IN_NEW_OPERATOR
#endif // OM_NEED_THORW_IN_NEW_OPERATOR

//#]

// Definition of OM_NO_THROW that is translated to throw() when OM_NEED_THROW_IN_NEW_OPERATOR is defined and to nothing otherwise.
//#[ type OM_NO_THROW
#ifdef OM_NEED_THROW_IN_NEW_OPERATOR
#define OM_NO_THROW throw()
#else
#define OM_NO_THROW
#endif // OM_NEED_THROW_IN_NEW_OPERATOR
//#]

//#[ type OM_DECLARE_COMPOSITE_OFFSET
#define OM_DECLARE_COMPOSITE_OFFSET Rhp_char_t aomOffsetDataMember;
//#]

// OM_RETURN declaration
//#[ type OM_RETURN
#ifndef _OMINSTRUMENT
#define OM_RETURN(expr) return(expr)
#endif // _OMINSTRUMENT
//#]

// OM_RETURN_VOID declaration
//#[ type OM_RETURN_VOID
#ifndef _OMINSTRUMENT
#define OM_RETURN_VOID 	return
#endif // _OMINSTRUMENT
//#]

// CALL declaration
//#[ type CALL
#ifndef _OMINSTRUMENT
#define CALL(val, expr) (val) = (expr)
#endif // _OMINSTRUMENT
//#]

// CALL_INST declaration
//#[ type CALL_INST
#ifndef _OMINSTRUMENT
#define CALL_INST(val, expr) (val) = (expr)
#endif // _OMINSTRUMENT
//#]

// CALL_SER declaration
//#[ type CALL_SER
#ifndef _OMINSTRUMENT
#define CALL_SER(val, expr, OM_SER_RET)  (val) = (expr)
#endif // _OMINSTRUMENT
//#]

//#[ type OM_NO_TEMPLATES_USAGE
// #define OM_NO_TEMPLATES_USAGE

#ifdef OM_NO_TEMPLATES_USAGE
#ifndef OM_NO_FRAMEWORK_MEMORY_MANAGER
#define OM_NO_FRAMEWORK_MEMORY_MANAGER
#endif
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type Rhp_long64_t
#ifdef OMOMATE	
	typedef DWORD64 Rhp_long64_t;
#else
#ifdef WIN32
	typedef unsigned __int64 Rhp_long64_t;
#else
	typedef unsigned long long Rhp_long64_t;
#endif
#endif

//#]

// Time measurement
//## type OxfTimeUnit
typedef unsigned long OxfTimeUnit;

// A TimeUnit compatibility name
//## type timeUnit
typedef OxfTimeUnit timeUnit;

#endif



