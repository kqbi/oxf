//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfEvent
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


#ifndef IOxfEvent_H
#define IOxfEvent_H
#include <stdint.h>
#include <memory>
//## link destination
class IOxfReactive;

//## package Design::oxf::Core::CoreAPI

//## class IOxfEvent
// An event (signal/message) interface.
// Events are used for synchronous and asynchronous messaging.
class IOxfEvent : public std::enable_shared_from_this<IOxfEvent> {
public :

    typedef std::shared_ptr<IOxfEvent> Ptr;
    // An event id attribute type
    //## type ID
    typedef int16_t ID;
    
    ////    Constructors and destructors    ////
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~IOxfEvent()
    inline virtual ~IOxfEvent(void) {
        //#[ operation ~IOxfEvent()
        //#]
    }
    
    ////    Operations    ////
    
    // destroy the event
    //## operation destroy()
    virtual void destroy(void) = 0;
    
    //## operation isFrameworkEvent() const
    virtual bool isFrameworkEvent(void) const = 0;
    
    // check if the event is a sub-type of an event with the specified id
    // Argument const ID eventId :
    // The event id to test
    //## operation isTypeOf(ID) const
    virtual bool isTypeOf(const ID eventId) const = 0;
    
    ////    Additional operations    ////
    
    //## auto_generated
    virtual ID getId(void) const = 0;
    
    //## auto_generated
    virtual void setId(ID p_id) = 0;
    
    //## auto_generated
    virtual void * getPort(void) const = 0;
    
    //## auto_generated
    virtual void setPort(void * const p_port) = 0;
    
    //## auto_generated
    virtual bool getSynchronous(void) const = 0;
    
    //## auto_generated
    virtual void setSynchronous(bool p_synchronous) = 0;
    
    //## auto_generated
    virtual std::weak_ptr<IOxfReactive>& getDestination(void) = 0;
    
    //## auto_generated
    virtual void setDestination(const std::shared_ptr<IOxfReactive>& p_IOxfReactive) = 0;
    
};

#endif



