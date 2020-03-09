//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMStack
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


#ifndef omstack_H
#define omstack_H

//## class OMStack
#include "omlist.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMStack
// A stack (FILO)
// Based on a linked-list
template <class Concept> class OMStack : public OMList<Concept> {
    ////    Constructors and destructors    ////
    
public :

    // Copy constructor
    // Argument const OMStack<Concept> & aStack :
    // The stack to copy
    //## operation OMStack(const OMStack<Concept> & )
    explicit inline OMStack(const OMStack<Concept> & aStack) : OMList<Concept>()
     	 {
        //#[ operation OMStack(const OMStack<Concept> & )
        copy(aStack);
        //#]
    }
    
    // Initialize an empty stack
    //## operation OMStack()
    inline OMStack(void) {
        //#[ operation OMStack()
        //#]
    }
    
    ////    Operations    ////
    
    // Assignment operator
    // Argument const OMStack<Concept> & aStack :
    // the stack to copy
    //## operation operator=(const OMStack<Concept> & )
    inline OMStack<Concept> & operator=(const OMStack<Concept> & aStack) {
        //#[ operation operator=(const OMStack<Concept> & )
        copy(aStack);
        return (*this);
        //#]
    }
    
    // Pop the top of the stack
    //## operation pop()
    inline Concept pop(void) {
        //#[ operation pop()
        Concept item = top();
        if ( !this->isEmpty() ) {
        	this->_removeFirst();
        }
        return item;
        //#]
    }
    
    // Push an element to the stack
    // Argument Concept aConcept :
    // The element to add
    //## operation push(Concept)
    inline void push(Concept aConcept) {
        //#[ operation push(Concept)
        this->addFirst(aConcept);
        //#]
    }
    
    // Get the top of the stack without changing its state
    //## operation top()
    inline Concept top(void) {
        //#[ operation top()
        return this->getFirstConcept();
        //#]
    }
    

private :

    // Copy a stack
    // Argument const OMStack<Concept>& aStack :
    // The stack to copy
    //## operation copy(const OMStack<Concept>&)
    inline void copy(const OMStack<Concept>& aStack) {
        //#[ operation copy(const OMStack<Concept>&)
        OMList<Concept>::copy(aStack);
        //#]
    }
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMStack

#endif



