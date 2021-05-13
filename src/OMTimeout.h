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
#include <Poller/Timer.h>
#include "OMEvent.h"
#include "Poller/EventPoller.h"
//## auto_generated
class IOxfReactive;

//## dependency OMTimerManager
class OMTimerManager;

//## package Design::oxf::Core::CoreImplementation

//## class OMTimeout
// IOxfTimeout implementation
class OMTimeout : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    // empty argument declaration, for arguments used in instrumented mode only.
    // Argument IOxfReactive* pdest :
    // The timeout client
    // Argument unsigned long delay :
    // The timeout delay
    // Argument const OMHandle* aomArg(theState) :
    // The destination state name (for design level debugging)
    //## operation OMTimeout(IOxfReactive,unsigned long,OMHandle)
    OMTimeout(std::shared_ptr<IOxfReactive> pdest, OMTimerManager& tm, oxf::EventPoller::Ptr &poller, unsigned long delay, const char* theState);
    
//    // Initialize a timeout
//    //## operation OMTimeout()
//    OMTimeout(void);
    
//    // copy constructor
//    // Argument const OMTimeout& tm :
//    // the timeout to copy
//    //## operation OMTimeout(OMTimeout)
//    explicit OMTimeout(const OMTimeout& tm);
    
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
    // Argument unsigned long now :
    // The current time (from the OMTimerManager singleton)
    //## operation setRelativeDueTime(unsigned long)
    void setRelativeDueTime(unsigned long now);
    
    ////    Additional operations    ////
    
    //## auto_generated
    bool isCanceled(void) const;
    
    //## auto_generated
    unsigned long getDelayTime(void) const;
    
    //## auto_generated
    void setDelayTime(unsigned long p_delayTime);
    
    //## auto_generated
    unsigned long getDueTime(void) const;
    
    //## auto_generated
    void setDueTime(unsigned long p_dueTime);
    
    //## auto_generated
    const char* getState(void) const;
    
    //## auto_generated
    void setState(const char* p_state);
    
    ////    Attributes    ////
    void action();

    oxf::EventPoller::Ptr _poller;

    std::shared_ptr<oxf::Timer> _timer;
private :

    OMTimerManager& _tm;
    // When the event is canceled, it should be ignored by the event dispatcher.
    bool canceled;		//## attribute canceled
    
    // The relative delay until the timeout should be expired.
    unsigned long delayTime;		//## attribute delayTime
    
    // The absolute time (i.e. system time) until the timeout will expire.
    // This time is calculated by:
    // dueTime = <timeout scheduling time> + delayTime.
    unsigned long dueTime;		//## attribute dueTime
    
    // The state that is the client of the timeout (for design level debugging)
    const char* state;		//## attribute state
    

   // DECLARE_MEMORY_ALLOCATOR(OMTimeout,OM_DYNAMIC_POOL_INITIALIZATION_SIZE)
    
};

#endif



