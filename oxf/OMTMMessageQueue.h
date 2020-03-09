//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMTMMessageQueue
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


#ifndef OMTMMessageQueue_H
#define OMTMMessageQueue_H

//## dependency OMList
#include "omlist.h"
//## dependency OMOSEventGenerationParams
#include "OMOSEventGenerationParams.h"
//## link theQueue
#include "os.h"
//## package Design::oxf::Services::RTOSWrappers

//## class OMTMMessageQueue
// A typed (Msg*) RTOS message queue (single message type)
template <class Msg> class OMTMMessageQueue {
    ////    Constructors and destructors    ////
    
public :

    // Initialize the queue
    // Argument const Rhp_int32_t messageQueueSize :
    // The RTOS message queue size
    // Argument bool dynamicMessageQueue :
    // When true, the RTOS queue size should be dynamic (grow on demand)
    //## operation OMTMMessageQueue(Rhp_int32_t,bool)
    inline OMTMMessageQueue(const Rhp_int32_t messageQueueSize, bool dynamicMessageQueue) : theQueue(NULL) {
        //#[ operation OMTMMessageQueue(Rhp_int32_t,bool)
        init(messageQueueSize, dynamicMessageQueue);
        //#]
    }
    
    // Initialize without creating of the RTOS queue
    //## operation OMTMMessageQueue()
    inline OMTMMessageQueue(void) : theQueue(0) {
        //#[ operation OMTMMessageQueue()
        //#]
    }
    
    // Cleanup
    //## operation ~OMTMMessageQueue()
    inline virtual ~OMTMMessageQueue(void) {
        //#[ operation ~OMTMMessageQueue()
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
    
    // Get a message from the queue
    //## operation get()
    inline virtual Msg* get(void) {
        //#[ operation get()
        Msg* msg = NULL;
        if (theQueue != NULL) {
        	msg = reinterpret_cast<Msg*>(theQueue->get());
        }
        return msg;
        //#]
    }
    
    // Get a list of the messages in the queue
    // Argument OMList<Msg*> & aList :
    // The output list
    //## operation getMessageList(OMList<Msg*> & )
    inline virtual void getMessageList(OMList<Msg*> & aList) {
        //#[ operation getMessageList(OMList<Msg*> & )
        if (theQueue != NULL) {
        	theQueue->getMessageList((OMList<void*>&)aList);
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
    
    // Put a message into the queue
    // Argument Msg* aMessage :
    // The message
    // Argument const IOxfEventGenerationParams& params :
    // Put parameters
    //## operation putMessage(Msg*,IOxfEventGenerationParams)
    inline virtual bool putMessage(Msg* aMessage, const IOxfEventGenerationParams& params) {
        //#[ operation putMessage(Msg*,IOxfEventGenerationParams)
        bool res = false;
        if (theQueue != NULL) {
        	res = theQueue->putMessage(reinterpret_cast<void*>(aMessage), params);
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

//## package Design::oxf::Services::RTOSWrappers

//## class OMTMMessageQueue

#endif



