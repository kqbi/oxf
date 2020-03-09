//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMUAbstractContainer
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


#ifndef OMUAbstractContainer_H
#define OMUAbstractContainer_H

//## dependency BasicTypes
#include "rawtypes.h"
//## class OMUIterator
class OMUIterator;

//## package Design::oxf::Services::Containers::Typeless

//## class OMUAbstractContainer
// Abstract type less container, provides unified interface for iterations.
class RP_FRAMEWORK_DLL OMUAbstractContainer {
public :

    // Abstract container pointer type
    //## type AbstractContainerPtr
    typedef OMUAbstractContainer* AbstractContainerPtr;
    
    ////    Friends    ////
    
    friend class OMUIterator;
    
    ////    Constructors and destructors    ////
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMUAbstractContainer()
    inline virtual ~OMUAbstractContainer(void) {
        //#[ operation ~OMUAbstractContainer()
        //#]
    }
    
    ////    Operations    ////
    

protected :

    // Get the item in the provided position (supplied by the iterator)
    // Argument void * pos :
    // the position
    //## operation getCurrent(void *) const
    virtual void * getCurrent(void * pos) const = 0;
    
    // iteration interface - get the initial position
    // Argument void *& pos :
    // the position to set
    //## operation getFirst(void *) const
    virtual void getFirst(void *& pos) const = 0;
    
    // Get the next position for the iterator
    // Argument void *& pos :
    // The current position
    //## operation getNext(void *) const
    virtual void getNext(void *& pos) const = 0;
    
};

#endif



