//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: MemoryManagerMacros
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


#ifndef OXFMemoryManagerMacros_H
#define OXFMemoryManagerMacros_H

//## dependency BasicTypes
#include "rawtypes.h"
//## package Design::oxf::Services::Macros::MemoryManagerMacros


//#[ ignore
// Memory manager related macros
//#]

// Support OS without global placement new/delete operators
//#[ type REPLACEMENT_NEW
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
#ifdef OM_NO_OS_REPLACEMENT_NEW
inline void * operator new(size_t, void * ptr) { return ptr; }
inline void operator delete(void *, void *) {return; }
#else
#ifdef OM_STL
#include <new>
#else
#ifdef OM_USE_THE_NEW_HEADER
#include <new>
#else
#include <new.h>
#endif // OM_USE_THE_NEW_HEADER
#endif // OM_STL
#endif // OM_NO_OS_REPLACEMENT_NEW
#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

// Support OS without support in ANSI assert()
//#[ type OS_ASSERT
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
#ifdef OM_DISABLE_ASSERT
// Support disabling of assert().
// Done to avoid LINT warnings due to Microsoft implementation.
#ifdef assert
#undef assert
#endif // assert
#define assert(condition)
#else // !OM_DISABLE_ASSERT
#ifdef OM_NO_OS_ASSERT
#ifndef assert
#define assert(condition) if (!(condition)) { exit(-1); }
#endif // assert
#else
#include <assert.h>
#endif // OM_NO_OS_ASSERT
#endif // OM_DISABLE_ASSERT
#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

// Add dummy size parameter to the new operator - compiler dependent code
//#[ type NEW_DUMMY_PARAM
#ifdef OM_NEW_OPERATOR_NEEDS_DUMMY_PARAM
#define NEW_DUMMY_PARAM ,size_t = 0
#else
#define NEW_DUMMY_PARAM
#endif // OM_NEW_OPERATOR_NEEDS_DUMMY_PARAM
//#]

// The framework memory pool dummy new parameter (required by some compilers)
//#[ type NEW_DUMMY_PARAM_IMP
#ifdef OM_NEW_OPERATOR_NEEDS_DUMMY_PARAM
#define NEW_DUMMY_PARAM_IMP ,size_t
#else // !OM_NEW_OPERATOR_NEEDS_DUMMY_PARAM
#define NEW_DUMMY_PARAM_IMP
#endif // OM_NEW_OPERATOR_NEEDS_DUMMY_PARAM
//#]

// The framework memory pool dummy delete parameter (required by some compilers)
//#[ type DELETE_DUMMY_PARAM_IMP
#ifdef OM_NEW_OPERATOR_NEEDS_DUMMY_PARAM
#define SIZE_PARAM_NAME omSizeOfDeletedObject
#define DELETE_DUMMY_PARAM_IMP ,size_t SIZE_PARAM_NAME
#else // !OM_NEW_OPERATOR_NEEDS_DUMMY_PARAM
#define DELETE_DUMMY_PARAM_IMP
#define SIZE_PARAM_NAME 0
#endif // OM_NEW_OPERATOR_NEEDS_DUMMY_PARAM
//#]

// Request memory for a given number of instances of the given type
//#[ type OMNEW
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
#define OMNEW(aType, aSize) ( new(OMMemoryManager::getMemoryManager()->getMemory( sizeof(aType) * (static_cast<size_t>(aSize))) ) aType[static_cast<size_t>(aSize)] )
#else
// use the global new operator
#define OMNEW(aType, aSize) ( new aType[static_cast<size_t>(aSize)] )
#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

// Return memory allocated by OMNEW
//#[ type OMDELETE
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))

#define OMDELETE(object, size) (OMMemoryManager::getMemoryManager()->	\
/*LDRA_INSPECTED 554 S : cast is ok */                          \
	returnMemory( reinterpret_cast<void*>(object), size))
#else
// the dummy variable is used to avoid compilation warnings,
// it is required for the other definition of the OMDELETE() macro
// - when the memory manager is used.
#define OMDELETE(object, dummy)			\
	if ((dummy) == 0) {} 			\
	delete[] (object)

#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

// Request memory for a given number of bytes
//#[ type OMGET_MEMORY
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
#define OMGET_MEMORY(aSize) OMMemoryManager::getMemoryManager()->getMemory((size_t)(aSize))
#else
// use 'regular' new & delete for memory allocation
#define OMGET_MEMORY(aSize) ::operator new((size_t) (aSize))
#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

// Replacement delete operator declaration
//#[ type OM_DECLARE_REPLACEMENT_DELETE_OPERATOR
#ifndef OM_NO_COMPILER_SUPPORT_FOR_REPLACEMENT_DELETE
#define OM_DECLARE_REPLACEMENT_DELETE_OPERATOR	\
	static void operator delete (void*, void*)	\
	{											\
		return;									\
	}

#else
#define OM_DECLARE_REPLACEMENT_DELETE_OPERATOR
#endif // OM_NO_COMPILER_SUPPORT_FOR_REPLACEMENT_DELETE
//#]

// nothrow new and delete operators
//#[ type OM_DECLARE_NOTHROW_INLINE_ALLOCATION_OPERATORS
#ifdef OM_NO_NOTHROW_NEW_SUPPORT
#define OM_DECLARE_NOTHROW_INLINE_ALLOCATION_OPERATORS
#else
#define OM_DECLARE_NOTHROW_INLINE_ALLOCATION_OPERATORS \
	static void* operator new (size_t aSize, const struct std::nothrow_t&) throw() \
	{																		\
	return OMMemoryManager::getMemoryManager()->getMemory(aSize);			\
	}																		\
	static void* operator new[] (size_t aSize, const struct std::nothrow_t&) throw() \
	{																		\
		return OMMemoryManager::getMemoryManager()->getMemory(aSize);		\
	}																		\
	static void operator delete(void * const aObject, const struct std::nothrow_t&) throw() \
	{																		\
		if (aObject != NULL) {												\
			OMMemoryManager::getMemoryManager()->returnMemory(aObject,0);	\
		}																	\
	}																		\
	static void operator delete[] (void * const aObject, const struct std::nothrow_t&) throw() \
	{																		\
		if (aObject != NULL) {												\
			OMMemoryManager::getMemoryManager()->returnMemory(aObject,0);	\
		}																	\
	}
#endif

//#]

// Override on the new and delete operators to obtain memory from the framework memory manager
//#[ type OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
#define OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS					\
public:																		\
	static void* operator new (size_t aSize NEW_DUMMY_PARAM)				\
	{																		\
		return OMMemoryManager::getMemoryManager()->getMemory(aSize);		\
	}																		\
	static void* operator new[] (size_t aSize NEW_DUMMY_PARAM)				\
	{																		\
		return OMMemoryManager::getMemoryManager()->getMemory(aSize);		\
	}																		\
	static void * operator new(size_t, void * ptr)							\
	{																		\
		return ptr;															\
	}																		\
	static void operator delete (void * aObject DELETE_DUMMY_PARAM_IMP)		\
	{																		\
		if (aObject != NULL) {												\
			OMMemoryManager::getMemoryManager()->returnMemory(aObject,SIZE_PARAM_NAME);	\
		}																	\
	}																		\
	static void operator delete[] (void * aObject DELETE_DUMMY_PARAM_IMP)	\
	{																		\
		if (aObject != NULL) {												\
			OMMemoryManager::getMemoryManager()->returnMemory(aObject,SIZE_PARAM_NAME);	\
		}																	\
	}																		\
    OM_DECLARE_NOTHROW_INLINE_ALLOCATION_OPERATORS \
	OM_DECLARE_REPLACEMENT_DELETE_OPERATOR

#else
// empty
#define OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

// The pool size for the memory manager switch helper allocated memory list
//#[ type OM_MEMORY_MANAGER_SWITCH_HELPER_POOL_SIZE
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
#ifndef OM_MEMORY_MANAGER_SWITCH_HELPER_POOL_SIZE
#define OM_MEMORY_MANAGER_SWITCH_HELPER_POOL_SIZE 512
#endif // ifndef OM_MEMORY_MANAGER_SWITCH_HELPER_POOL_SIZE
#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

#endif



