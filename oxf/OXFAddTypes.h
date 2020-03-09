//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: addTypes
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


#ifndef OXFAddTypes_H
#define OXFAddTypes_H

//## dependency IOxfTimeout
#include "IOxfTimeout.h"
//## dependency OMCollection
#ifndef OM_NO_TEMPLATES_USAGE
#include "omcollec.h"
#endif //OM_NO_TEMPLATES_USAGE

//## dependency OMList
#ifndef OM_NO_TEMPLATES_USAGE
#include "omlist.h"
#endif // OM_NO_TEMPLATES_USAGE

//## dependency OMQueue
#ifndef OM_NO_TEMPLATES_USAGE
#include "omqueue.h"
#endif // OM_NO_TEMPLATES_USAGE

//## dependency OMUCollection
#ifdef OM_NO_TEMPLATES_USAGE
#include "omucollec.h"
#endif // OM_NO_TEMPLATES_USAGE

//## dependency OMUList
#ifdef OM_NO_TEMPLATES_USAGE
#include "omulist.h"
#endif // OM_NO_TEMPLATES_USAGE


//## dependency OMUQueue
#ifdef OM_NO_TEMPLATES_USAGE
#include "omuqueue.h"
#endif // OM_NO_TEMPLATES_USAGE

//## dependency OMHeap
#ifndef OM_NO_TEMPLATES_USAGE
template <class Node> class OMHeap;


#endif // OM_NO_TEMPLATES_USAGE

//## dependency OMThread
class OMThread;

//## dependency OMUHeap
#ifdef OM_NO_TEMPLATES_USAGE
class OMUHeap;


#endif //OM_NO_TEMPLATES_USAGE

//## package Design::oxf::Services::Types::addTypes


//#[ type OMListType
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUList OMListType; 
#else
typedef OMList<void*> OMListType; 
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type OMQueueType
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUQueue OMQueueType; 
#else
typedef OMQueue<void*> OMQueueType; 
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type OMEventListType
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUList OMEventListType; 
#else
typedef OMList<IOxfEvent*> OMEventListType; 
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type OMEventQueueIter
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUIterator OMEventQueueIter; 
#else
typedef OMIterator<IOxfEvent*> OMEventQueueIter; 
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type OMTimeoutIter
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUIterator OMTimeoutIter; 
#else
typedef OMIterator<IOxfTimeout*> OMTimeoutIter; 
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type OMThreadIter
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUIterator OMThreadIter; 
#else
typedef OMIterator<OMThread*> OMThreadIter;
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type OMHeapType
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUHeap OMHeapType; 
#else
typedef OMHeap<IOxfTimeout> OMHeapType; 
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type OMTmCollecType
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUCollection OMTmCollecType; 
#else
typedef OMCollection<IOxfTimeout*> OMTmCollecType; 
#endif // OM_NO_TEMPLATES_USAGE
//#]

//#[ type OMTimeoutValueIter
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUIterator OMTimeoutValueIter; 
#else
typedef OMIterator<IOxfTimeout> OMTimeoutValueIter; 
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type OMThreadType
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUList OMThreadType; 
#else
typedef OMList<OMThread*> OMThreadType;
#endif // OM_NO_TEMPLATES_USAGE

//#]

//#[ type OMThreadVoidIter
#ifdef OM_NO_TEMPLATES_USAGE
typedef OMUIterator OMThreadVoidIter; 
#else
typedef OMIterator<void *> OMThreadVoidIter;
#endif // OM_NO_TEMPLATES_USAGE

//#]

//## package Design::oxf::Services::Types::addTypes



#endif



