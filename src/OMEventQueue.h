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
#include "IOxfTimeout.h"
#include <unordered_set>
#include <mutex>
//## package Design::oxf::Services::RTOSWrappers

//## class OMEventQueue
// An instantiation class of the event queue wrapper over the RTOS message queue.
// The message type is IOxfEvent*.
class OMEventQueue {

    ////    Constructors and destructors    ////
    
public :

    // Initialize without creating of the RTOS queue
    //## operation OMEventQueue()
    inline OMEventQueue(void) {
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
    inline void cleanup() {
        //#[ operation cleanup()
        std::lock_guard<std::mutex> lock(_mutex);
        _theQueue.clear();
        //#]
    }
    
    // Get an event from the queue
    //## operation get() const
    inline virtual IOxfTimeout::Ptr get(void) {
        //#[ operation get() const
        IOxfTimeout::Ptr msg = 0;
        std::lock_guard<std::mutex> lock(_mutex);
        if (!_theQueue.empty()) {
            auto iter = _theQueue.begin();
            msg = *iter;
            _theQueue.erase(iter);
        }
        return msg;
        //#]
    }
    
    // Get a list of the events in the queue
    // Argument OMEventListType & aList :
    // The output list
    //## operation getMessageList(OMEventListType & ) const
//    inline virtual void getMessageList(std::vector<IOxfEvent::Ptr> & aList) const {
//        //#[ operation getMessageList(OMEventListType & ) const

//        if (theQueue != NULL) {
//            theQueue->getMessageList(reinterpret_cast< OMListType& >(aList));
//        }
//        //#]
//    }
    
    // Get the RTOS queue
    //## operation getOsHandle() const
//    inline virtual void * getOsHandle(void) const {
//        //#[ operation getOsHandle() const
//        void* handle = NULL;
//        if (theQueue != NULL) {
//            handle = theQueue->getOsHandle();
//        }
//        return handle;
//        //#]
//    }
    

    // Check if the queue is empty
    //## operation isEmpty() const
    inline virtual bool isEmpty(void) const {
        //#[ operation isEmpty() const
        return _theQueue.empty();
        //#]
    }
    
    // Put a event into the queue
    // Argument IOxfEvent* ev :
    // The event
    // Argument const IOxfEventGenerationParams& params :
    // Put parameters
    //## operation putMessage(IOxfEvent*,IOxfEventGenerationParams)
    inline virtual bool add(const IOxfTimeout::Ptr& ev) {
        //#[ operation putMessage(IOxfEvent*,IOxfEventGenerationParams)
        std::lock_guard<std::mutex> lock(_mutex);
        _theQueue.emplace(ev);
        return true;
        //#]
    }

    inline virtual bool remove(const IOxfTimeout::Ptr& ev) {
        //#[ operation putMessage(IOxfEvent*,IOxfEventGenerationParams)
        std::lock_guard<std::mutex> lock(_mutex);
        _theQueue.erase(ev);
        return true;
        //#]
    }
    ////    Additional operations    ////
    
    //## auto_generated
    inline std::unordered_set<IOxfTimeout::Ptr> getOsQueue(void) const {
        //#[ auto_generated
        return _theQueue;
        //#]
    }
    
    ////    Relations and components    ////
    

private :

    std::mutex _mutex;

    // The RTOS message queue
    std::unordered_set<IOxfTimeout::Ptr> _theQueue;		//## link theQueue
    
};

#endif



