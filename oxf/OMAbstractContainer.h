//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMAbstractContainer
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


#ifndef OMAbstractContainer_H
#define OMAbstractContainer_H

//## dependency OMNullValue
#include "OMNullValue.h"
//## dependency OMIterator
template <class Concept> class OMIterator;

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMAbstractContainer
// A generic type-safe container, Used by OMIterator<> to iterate over the derived containers.
template <class Concept> class OMAbstractContainer {
public :

    ////    Friend List    ////
    
    friend  class OMIterator<Concept>;
    
    
    ////    Constructors and destructors    ////
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMAbstractContainer()
    inline virtual ~OMAbstractContainer(void) {
        //#[ operation ~OMAbstractContainer()
        //#]
    }
    
    ////    Operations    ////
    

protected :

    // Get the element at the given position (called by the iterator)
    // Argument void * pos :
    // The current iterator position
    //## operation getCurrent(void *) const
    virtual Concept & getCurrent(void * pos) const = 0;
    
    // Set the initial position for the iterator
    // Argument void*& pos :
    // The position to set
    //## operation getFirst(void*&) const
    virtual void getFirst(void*& pos) const = 0;
    
    // Update the provided position to the next position in the container
    // Argument void*& pos :
    // The position to update
    //## operation getNext(void*&) const
    virtual void getNext(void*& pos) const = 0;
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMAbstractContainer

#endif



