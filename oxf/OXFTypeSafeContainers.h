//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: TypeSafe
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


#ifndef OXFTypeSafeContainers_H
#define OXFTypeSafeContainers_H

//## dependency BasicTypes
#include "rawtypes.h"
//## dependency MISRA_Cpp_Types
#include "OXFMISRA_Cpp_Types.h"
//## auto_generated
template <class Concept> class OMAbstractContainer;

//## auto_generated
template <class Concept> class OMCollection;

//## auto_generated
template <class Node> class OMHeap;

//## auto_generated
template <class Concept> class OMIterator;

//## auto_generated
template <class Concept> class OMList;

//## auto_generated
template <class Key, class Concept> class OMMap;

//## auto_generated
template <class Concept> class OMNullValue;

//## auto_generated
template <class Concept> class OMQueue;

//## auto_generated
template <class Concept> class OMStack;

//## auto_generated
template <class Concept> class OMStaticArray;

//## package Design::oxf::Services::Containers::TypeSafe


//#[ ignore
// Type-safe (template) containers
//#]

// When allocating memory, the memory blocks must be aligned with the compiler settings.
// This macro is used in the memory pools, to guarantee that the pool allocates sufficient memory in order to avoid memory alignment issues.
//#[ type ContainersMemoryAlignment
#ifndef OM_LONG_MEMORY_ALIGNMENT
typedef Rhp_char_t omMemoryAlignedType;
#define OM_ALIGNED_SIZEOF(ELEMENT) (sizeof(ELEMENT) + (OMRAW_MEMORY_ALIGNMENT-1))
#else
typedef Rhp_int32_t omMemoryAlignedType;
#define OM_ALIGNED_SIZEOF(ELEMENT) ((sizeof(ELEMENT) + (OMRAW_MEMORY_ALIGNMENT-1) + 3) / 4)
#endif // OM_LONG_MEMORY_ALIGNMENT
//#]

// NULL array used for null element (OMNullValue)
//## attribute OMContainersNullBlock
//#[ ignore
#ifdef OMUseNullBlockContainer

//#]
extern Rhp_int32_t OMContainersNullBlock[];
//#[ ignore

#endif // OMUseNullBlockContainer
//#]

#endif



