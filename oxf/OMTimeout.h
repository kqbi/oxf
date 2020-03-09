//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMTimeout
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


#ifndef OMTimeout_H
#define OMTimeout_H

//## class OMTimeout
#include "OMEvent.h"
//## dependency Pools
#include "OXFPools.h"
//## auto_generated
class AnimServices;

//## auto_generated
class IOxfReactive;

//## dependency OMThread
class OMThread;

//## dependency OMTimerManager
class OMTimerManager;

//## dependency OXF
class OXF;

//## package Design::oxf::Core::CoreImplementation

//## class OMTimeout
// IOxfTimeout implementation
class RP_FRAMEWORK_DLL OMTimeout : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    // empty argument declaration, for arguments used in instrumented mode only.
    // Argument IOxfReactive* pdest :
    // The timeout client
    // Argument OxfTimeUnit delay :
    // The timeout delay
    // Argument const OMHandle* aomArg(theState) :
    // The destination state name (for design level debugging)
    //## operation OMTimeout(IOxfReactive,OxfTimeUnit,OMHandle)
    OMTimeout(IOxfReactive* pdest, OxfTimeUnit delay, const OMHandle* aomArg(theState));
    
    // Initialize a timeout
    //## operation OMTimeout()
    OMTimeout(void);
    
    // copy constructor
    // Argument const OMTimeout& tm :
    // the timeout to copy
    //## operation OMTimeout(OMTimeout)
    explicit OMTimeout(const OMTimeout& tm);
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMTimeout()
    virtual ~OMTimeout(void);
    
    ////    Operations    ////
    
    // cancel the timeout
    //## operation cancel()
    void cancel(void);
    
    // assignment operator
    // Argument const OMTimeout& tm :
    // the event to copy
    //## operation operator =(OMTimeout)
    OMTimeout& operator =(const OMTimeout& tm);
    
    // Compare timeouts by due time
    // Argument const OMTimeout& tn :
    // The other timeout
    //## operation operator<(OMTimeout) const
    bool operator<(const OMTimeout& tn) const;
    
    // Compare timeouts by due time
    // Argument const OMTimeout& tn :
    // The other timeout
    //## operation operator>(OMTimeout) const
    bool operator>(const OMTimeout& tn) const;
    
    // set the timeout to be a delay timeout
    //## operation setDelayTimeout()
    void setDelayTimeout(void);
    
    // Set the timeout due time based on the current time and the delay time
    // Argument OxfTimeUnit now :
    // The current time (from the OMTimerManager singleton)
    //## operation setRelativeDueTime(OxfTimeUnit)
    void setRelativeDueTime(OxfTimeUnit now);
    
    ////    Additional operations    ////
    
    //## auto_generated
    bool isCanceled(void) const;
    
    //## auto_generated
    OxfTimeUnit getDelayTime(void) const;
    
    //## auto_generated
    void setDelayTime(OxfTimeUnit p_delayTime);
    
    //## auto_generated
    OxfTimeUnit getDueTime(void) const;
    
    //## auto_generated
    void setDueTime(OxfTimeUnit p_dueTime);
    
    //## auto_generated
    const OMHandle* getState(void) const;
    
    //## auto_generated
    void setState(const OMHandle* p_state);
    
    ////    Attributes    ////
    

private :

    // When the event is canceled, it should be ignored by the event dispatcher.
    bool canceled;		//## attribute canceled
    
    // The relative delay until the timeout should be expired.
    OxfTimeUnit delayTime;		//## attribute delayTime
    
    // The absolute time (i.e. system time) until the timeout will expire.
    // This time is calculated by:
    // dueTime = <timeout scheduling time> + delayTime.
    OxfTimeUnit dueTime;		//## attribute dueTime
    
    // The state that is the client of the timeout (for design level debugging)
    const OMHandle* state;		//## attribute state
    

    DECLARE_MEMORY_ALLOCATOR(OMTimeout,OM_DYNAMIC_POOL_INITIALIZATION_SIZE)
    
};

#endif



