//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMEventQueue
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


#ifndef OMEventQueue_H
#define OMEventQueue_H

//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency OMOSEventGenerationParams
#include "OMOSEventGenerationParams.h"
//## dependency OMOSThread
#include "os.h"
//## package Design::oxf::Services::RTOSWrappers

//## class OMEventQueue
// An instantiation class of the event queue wrapper over the RTOS message queue.
// The message type is IOxfEvent*.
class RP_FRAMEWORK_DLL OMEventQueue {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Initialize
    // Argument const Rhp_int32_t messageQueueSize :
    // The RTOS message queue size
    // Argument bool dynamicMessageQueue :
    // When true, the RTOS queue size should be dynamic (grow on demand)
    //## operation OMEventQueue(Rhp_int32_t,bool)
    inline OMEventQueue(const Rhp_int32_t messageQueueSize, bool dynamicMessageQueue) : theQueue(NULL) {
        //#[ operation OMEventQueue(Rhp_int32_t,bool)
        init(messageQueueSize, dynamicMessageQueue);
        //#]
    }
    
    // Initialize without creating of the RTOS queue
    //## operation OMEventQueue()
    inline OMEventQueue(void) : theQueue(NULL) {
        //#[ operation OMEventQueue()
        //#]
    }
    
    // Cleanup
    //## operation ~OMEventQueue()
    inline virtual ~OMEventQueue(void) {
        //#[ operation ~OMEventQueue()
        cleanup();
        //#]
    }
    
    ////    Operations    ////
    
    // cleanup the RTOS resources
    //## operation cleanup()
    inline void cleanup(void) {
        //#[ operation cleanup()
        if (theQueue != NULL) {
        	delete theQueue;
        	theQueue = NULL;
        }
        //#]
    }
    
    // Get an event from the queue
    //## operation get() const
    inline virtual IOxfEvent* get(void) const {
        //#[ operation get() const
        IOxfEvent* msg = NULL;
        if (theQueue != NULL) {
        	msg = reinterpret_cast<IOxfEvent*>(theQueue->get());
        }
        return msg;
        //#]
    }
    
    // Get a list of the events in the queue
    // Argument OMEventListType & aList :
    // The output list
    //## operation getMessageList(OMEventListType & ) const
    inline virtual void getMessageList(OMEventListType & aList) const {
        //#[ operation getMessageList(OMEventListType & ) const
        if (theQueue != NULL) {
        	theQueue->getMessageList(reinterpret_cast< OMListType& >(aList));
        }
        //#]
    }
    
    // Get the RTOS queue 
    //## operation getOsHandle() const
    inline virtual void * getOsHandle(void) const {
        //#[ operation getOsHandle() const
        void* handle = NULL;
        if (theQueue != NULL) {
        	handle = theQueue->getOsHandle();
        }
        return handle;
        //#]
    }
    
    // Initialize the RTOS queue
    // Argument const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize :
    // The RTOS message queue size
    // Argument bool dynamicMessageQueue = true :
    // When true, the RTOS queue size should be dynamic (grow on demand)
    //## operation init(Rhp_int32_t,bool)
    inline void init(const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize, bool dynamicMessageQueue
 = true) {
        //#[ operation init(Rhp_int32_t,bool)
        if (theQueue == NULL) {
        	theQueue = OMOSFactory::instance()->createOMOSMessageQueue(dynamicMessageQueue, messageQueueSize);
        }
        //#]
    }
    
    // Check if the queue is empty
    //## operation isEmpty() const
    inline virtual bool isEmpty(void) const {
        //#[ operation isEmpty() const
        bool empty = true;
        if (theQueue != NULL) {
        	empty = (theQueue->isEmpty() != 0);
        }
        return empty;
        //#]
    }
    
    // Check if the queue is full (dynamic queues are never full)
    //## operation isFull() const
    inline virtual bool isFull(void) const {
        //#[ operation isFull() const
        bool full = true;
        if (theQueue != NULL) {
        	full = theQueue->isFull();
        }
        return full;
        //#]
    }
    
    // Block on the queue until a message arrives (non-blocking if there are messages in the queue)
    //## operation pend()
    inline virtual void pend(void) {
        //#[ operation pend()
        if (theQueue != NULL) {
        	theQueue->pend();
        }
        //#]
    }
    
    // Put a event into the queue
    // Argument IOxfEvent* ev :
    // The event
    // Argument const IOxfEventGenerationParams& params :
    // Put parameters
    //## operation putMessage(IOxfEvent*,IOxfEventGenerationParams)
    inline virtual bool putMessage(IOxfEvent* ev, const IOxfEventGenerationParams& params) {
        //#[ operation putMessage(IOxfEvent*,IOxfEventGenerationParams)
        bool res = false;
        if (theQueue != NULL) {
        	res = theQueue->putMessage(reinterpret_cast<void*>(ev), params);
        }
        return res;
        //#]
    }
    
    ////    Additional operations    ////
    
    //## auto_generated
    inline OMOSMessageQueue* getOsQueue(void) const {
        //#[ auto_generated
        return theQueue;
        //#]
    }
    
    ////    Relations and components    ////
    

private :

    // The RTOS message queue
    OMOSMessageQueue* theQueue;		//## link theQueue
    
};

#endif



