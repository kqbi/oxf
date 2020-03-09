//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMCore
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



//## auto_generated
#include "OMCore.h"
//## dependency AnimServices
#ifdef _OMINSTRUMENT
#include <aom/AnimServices.h>
#endif //_OMINSTRUMENT
//## dependency Events
#include "OXFEvents.h"
//## auto_generated
#include "IOxfActive.h"
//## auto_generated
#include "IOxfEvent.h"
//## auto_generated
#include "OXFNotifyMacros.h"
//## auto_generated
#include "OMAnimReactive.h"
//## auto_generated
#include "state.h"
//## auto_generated
#include "OMMainThread.h"
//## auto_generated
#include "os.h"
//## dependency OMThreadManager
#include "OMThreadManager.h"
//## auto_generated
#include "OMTimeout.h"
//## dependency OMTimerManager
#include "OMTimerManager.h"
//## auto_generated
#include "oxf.h"
//## package Design::oxf::Services::ResourceManagement

//## class OMCore

//#[ ignore
#ifdef OM_REUSABLE_STATECHART_IMPLEMENTATION
#undef OM_REUSABLE_STATECHART_IMPLEMENTATION
#endif // OM_REUSABLE_STATECHART_IMPLEMENTATION
#define OM_ZERO_CHECK 0.5
//#]


//## class OMCore::TimeReqList
//## class OMCore::TimeReqList::TimeReq
OMCore::TimeReqList::TimeReq::TimeReq(OMOSEventFlag* lockFlag, OxfTimeUnit t) : lock(lockFlag), priority(0), time(t) {
    //#[ operation TimeReq(OMOSEventFlag,OxfTimeUnit)
    //#]
}

OMCore::TimeReqList::TimeReq::~TimeReq(void) {
}

OMOSEventFlag* OMCore::TimeReqList::TimeReq::getLock(void) const {
    return lock;
}

OxfTimeUnit OMCore::TimeReqList::TimeReq::getTime(void) const {
    return time;
}

void OMCore::TimeReqList::TimeReq::setTime(OxfTimeUnit p_time) {
    time = p_time;
}

OMCore::TimeReqList::~TimeReqList(void) {
}

OxfTimeUnit OMCore::TimeReqList::GetStep(void) const {
    //#[ operation GetStep() const
    OxfTimeUnit step = ~0U; //Max unsigned long
    if(!list.isEmpty())
    {
        int count = 0;
      	TimeReqIter it(list);
      	while(*it)
      	{   
      		TimeReq* item = reinterpret_cast<TimeReq*>(*it);
      		if(count == 0)
      			step = item->getTime(); // *sumPriorities/list.getFirstConcept()->getPriority();
      		else
      		if (item->getTime() // *sumPriorities/(*it)->getPriority() 
      			< step)
      			step = item->getTime(); // *sumPriorities/(*it)->getPriority();
      		it++;
      		count++;	 
      	}
    	#ifdef OM_WIN32_COMPILER_DISABLE_WARNING_4244
    	#pragma warning ( push )
    	#pragma warning ( disable : 4267 )
    	#endif // OM_WIN32_COMPILER_DISABLE_WARNING_4244
     
    	step *= list.getCount();
    
    	#ifdef OM_WIN32_COMPILER_DISABLE_WARNING_4244
    	#pragma warning ( pop )
    	#endif // OM_WIN32_COMPILER_DISABLE_WARNING_4244
    }
    return step;
    
    //#]
}

bool OMCore::TimeReqList::IsEmpty(void) const {
    //#[ operation IsEmpty() const
    return list.isEmpty() == 1;
    //#]
}

void OMCore::TimeReqList::Reduce(OxfTimeUnit t) {
    //#[ operation Reduce(OxfTimeUnit)
    TimeReqListType toBeRemoved;
    TimeReqIter it(list);
    while(*it)
    {
      	TimeReq* item = reinterpret_cast<TimeReq*>(*it);
    
    	#ifdef OM_WIN32_COMPILER_DISABLE_WARNING_4244
    	#pragma warning ( push )
    	#pragma warning ( disable : 4267 )
    	#endif // OM_WIN32_COMPILER_DISABLE_WARNING_4244
     
      	item->setTime(item->getTime()- t/list.getCount());  
    
    	#ifdef OM_WIN32_COMPILER_DISABLE_WARNING_4244
    	#pragma warning ( pop )
    	#endif // OM_WIN32_COMPILER_DISABLE_WARNING_4244
    
    	if(item->getTime() < OM_ZERO_CHECK)
    	{
    		toBeRemoved.add(*it);
    	}
    	it++;
    }
    
    TimeReqIter tbrIt(toBeRemoved);
    while(*tbrIt)
    {
      	TimeReq* item = reinterpret_cast<TimeReq*>(*tbrIt);
    	OMOSEventFlag* tmp = item->getLock();
    	list.remove(*tbrIt);
    	delete (item);
    	tbrIt++;                 
    	tmp->signal();
    }
    
    //#]
}

void OMCore::TimeReqList::add(OMOSEventFlag* l, OxfTimeUnit t) {
    //#[ operation add(OMOSEventFlag,OxfTimeUnit)
    //sumPriorities += OS::instance->getPriority(l);
    list.add(new TimeReq(l,t));
    //#]
}

OMCore::OMCore(const OMAffinity_t& coreIdVal) : coreTime(0), prevTime(0), sumPriorities(0.0), coreId(coreIdVal), thread("OMCore", 
OMOSThread::DefaultThreadPriority, OMOSThread::DefaultStackSize, OMOSThread::DefaultMessageQueueSize, true) {
    initStatechart();
    //#[ operation OMCore(OMAffinity_t)
    OMReactive::setActiveContext(&thread, true);
    thread.setDeletionAllowed(true);
    OMThreadManager::addToCoreList(coreId , this);
    #ifdef _OMINSTRUMENT
    char  coreName[100];
    sprintf(coreName,"core_%ld",coreId);
    AnimServices::setThreadName(thread.getOsThread()->getOsHandle(), coreName);
    #endif
    
    //#]
}

OMCore::~OMCore(void) {
    cancelTimeouts();
}

OxfTimeUnit OMCore::ElapsedTime(void) {
    //#[ operation ElapsedTime()
    OxfTimeUnit now = OMTimerManager::instance()->getElapsedTime();
    OxfTimeUnit elapsed = now-prevTime;
    prevTime = now;
    return elapsed;
    
    //#]
}

void OMCore::consumeTime(OxfTimeUnit t) {
    //#[ operation consumeTime(OxfTimeUnit)
    OMOSEventFlag* lockFlag = OMOSFactory::instance()->createOMOSEventFlag();
    GEN(evGetBusy(t, lockFlag));
    OM_LOCK(lockFlag->wait())
    delete  lockFlag;
    //#]
}

bool OMCore::startBehavior(void) {
    //#[ operation startBehavior()
    bool done = OMReactive::startBehavior();
    if (done) {
        thread.startDispatching();
    } 
    return done;
    
    //#]
}

OxfTimeUnit OMCore::getCoreTime(void) const {
    return coreTime;
}

void OMCore::setCoreTime(OxfTimeUnit p_coreTime) {
    coreTime = p_coreTime;
}

bool OMCore::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void OMCore::initStatechart(void) {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void OMCore::cancelTimeouts(void) {
    cancel(rootState_timeout);
}

void OMCore::rootState_entDef(void) {
    {
        rootState_subState = idle;
        rootState_active = idle;
    }
}

IOxfReactive::TakeEventStatus OMCore::rootState_processEvent(void) {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State idle
        case idle:
        {
            if(IS_EVENT_TYPE_OF(evGetBusy_Events_Services_oxf_Design_id) == 1)
                {
                    OMSETPARAMS(evGetBusy);
                    //#[ transition 1 
                    reqList.add(params->myLocker,params->t);
                    prevTime = OMTimerManager::instance()->getElapsedTime();
                    //#]
                    rootState_subState = busy;
                    rootState_active = busy;
                    //#[ state busy.(Entry) 
                    OxfTimeUnit step = reqList.GetStep();
                    //#]
                    rootState_timeout = scheduleTimeout(step, NULL);
                    res = eventConsumed;
                }
            
        }
        break;
        // State busy
        case busy:
        {
            if(IS_EVENT_TYPE_OF(OMTimeoutEventId) == 1)
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            //#[ state busy.(Exit) 
                            OxfTimeUnit t = ElapsedTime();
                            coreTime += t;
                            reqList.Reduce(t);
                            //#]
                            pushNullTransition();
                            rootState_subState = timedOut;
                            rootState_active = timedOut;
                            res = eventConsumed;
                        }
                }
            else {
                if(IS_EVENT_TYPE_OF(evGetBusy_Events_Services_oxf_Design_id) == 1)
                    {
                        OMSETPARAMS(evGetBusy);
                        cancel(rootState_timeout);
                        //#[ state busy.(Exit) 
                        OxfTimeUnit t = ElapsedTime();
                        coreTime += t;
                        reqList.Reduce(t);
                        //#]
                        //#[ transition 3 
                        reqList.add(params->myLocker,params->t);
                        //#]
                        rootState_subState = busy;
                        rootState_active = busy;
                        //#[ state busy.(Entry) 
                        OxfTimeUnit step = reqList.GetStep();
                        //#]
                        rootState_timeout = scheduleTimeout(step, NULL);
                        res = eventConsumed;
                    }
                }
                
            
        }
        break;
        // State timedOut
        case timedOut:
        {
            if(IS_EVENT_TYPE_OF(OMNullEventId) == 1)
                {
                    //## transition 4 
                    if(reqList.IsEmpty())
                        {
                            popNullTransition();
                            rootState_subState = idle;
                            rootState_active = idle;
                            res = eventConsumed;
                        }
                    else
                        {
                            //## transition 5 
                            if(!reqList.IsEmpty())
                                {
                                    popNullTransition();
                                    rootState_subState = busy;
                                    rootState_active = busy;
                                    //#[ state busy.(Entry) 
                                    OxfTimeUnit step = reqList.GetStep();
                                    //#]
                                    rootState_timeout = scheduleTimeout(step, NULL);
                                    res = eventConsumed;
                                }
                        }
                }
            
        }
        break;
        default:
            break;
    }
    return res;
}




