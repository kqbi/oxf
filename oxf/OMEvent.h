//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMEvent
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


#ifndef OMEvent_H
#define OMEvent_H

//## class OMEvent
#include "IOxfTimeout.h"
//## dependency Manager
#include "OXFManager.h"
//## dependency AnimServices
class AnimServices;

//## auto_generated
class IOxfReactive;

//## package Design::oxf::Core::CoreImplementation

//## class OMEvent
// The event base implementation class
class RP_FRAMEWORK_DLL OMEvent : public IOxfTimeout {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // initialize the event
    // Argument IOxfEvent::ID eventId = 0 :
    // the event id
    // Argument IOxfReactive* dest = 0 :
    // the event destination
    //## operation OMEvent(ID,IOxfReactive)
    OMEvent(IOxfEvent::ID eventId = 0, IOxfReactive* dest = 0);
    
    // copy constructor
    // Argument const OMEvent& ev :
    // the event to copy
    //## operation OMEvent(OMEvent)
    OMEvent(const OMEvent& ev);
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMEvent()
    ~OMEvent(void);
    
    ////    Operations    ////
    
    //## operation ATG_showEventID()
    //#[ ignore
    #ifdef ATG_MODIFICATIONS_TO_OXF
    
    //#]
    OMEvent* ATG_showEventID(void);
    //#[ ignore
    #endif // ATG_MODIFICATIONS_TO_OXF
    
    //#]
    
    // cancel the timeout
    //## operation cancel()
    void cancel(void);
    
    // destroy the event
    //## operation destroy()
    void destroy(void);
    
    // Empty implementation to ITimeout API
    //## operation getDelayTime() const
    OxfTimeUnit getDelayTime(void) const;
    
    // Empty implementation to ITimeout API
    //## operation getDueTime() const
    OxfTimeUnit getDueTime(void) const;
    
    // Empty implementation to ITimeout API
    //## operation isCanceled() const
    bool isCanceled(void) const;
    
    // Check that the event is an application event.
    //## operation isRealEvent() const
    bool isRealEvent(void) const;
    
    // Check if the event is a timeout
    //## operation isTimeout() const
    inline bool isTimeout(void) const;
    
    // check if the event is a sub-type of an event with the specified id
    // Argument const IOxfEvent::ID eventId :
    // The event id to check
    //## operation isTypeOf(ID) const
    inline virtual bool isTypeOf(const IOxfEvent::ID eventId) const;
    
    // assignment operator
    // Argument const OMEvent& ev :
    // the event to copy
    //## operation operator =(OMEvent)
    OMEvent& operator =(const OMEvent& ev);
    
    // Empty implementation to IOxfTimeout API
    // Argument OxfTimeUnit /**/ :
    // The delay time
    //## operation setDelayTime(OxfTimeUnit)
    void setDelayTime(OxfTimeUnit /**/);
    
    // Empty implementation to IOxfTimeout API
    // Argument OxfTimeUnit /**/ :
    // The absolute due time
    //## operation setDueTime(OxfTimeUnit)
    void setDueTime(OxfTimeUnit /**/);
    
    ////    Additional operations    ////
    
    //## auto_generated
    bool shouldDeleteAfterConsume(void) const;
    
    //## auto_generated
    void setDeleteAfterConsume(bool p_deleteAfterConsume);
    
    //## auto_generated
    bool isFrameworkEvent(void) const;
    
    //## auto_generated
    void setFrameworkEvent(bool p_frameworkEvent);
    
    //## auto_generated
    inline IOxfEvent::ID getId(void) const {
        //#[ auto_generated
        return lId;
        //#]
    }
    
    //## auto_generated
    inline void setId(IOxfEvent::ID p_lId) {
        //#[ auto_generated
        lId = p_lId;
        //#]
    }
    
    //## auto_generated
    void * getPort(void) const;
    
    //## auto_generated
    void setPort(void * const p_port);
    
    //## auto_generated
    bool getSynchronous(void) const;
    
    //## auto_generated
    void setSynchronous(bool p_synchronous);
    
    //## auto_generated
    IOxfReactive* getDestination(void) const;
    
    //## auto_generated
    void setDestination(IOxfReactive* p_IOxfReactive);
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Attributes    ////
    
    // The event id.
    IOxfEvent::ID lId;		//## attribute lId
    

private :

    // This flag is used to indicate if the event dispatcher should delete the event after it was dispatched
    bool deleteAfterConsume;		//## attribute deleteAfterConsume
    
    // This flag mark an event as an internal framework event (that should be invisible in design-level debugging)
    bool frameworkEvent;		//## attribute frameworkEvent
    
    // The port that the event was sent to
    void * port;		//## attribute port
    
    // Mark the event as a synchronous event (i.e. triggered operation).
    bool synchronous;		//## attribute synchronous
    
    ////    Relations and components    ////
    

protected :

    IOxfReactive* destination;		//## link destination
    
};

inline bool OMEvent::isTimeout(void) const {
    //#[ operation isTimeout() const
    return false;
    //#]
}

inline bool OMEvent::isTypeOf(const IOxfEvent::ID eventId) const {
    //#[ operation isTypeOf(ID) const
    return (lId == eventId);
    //#]
}

#endif



