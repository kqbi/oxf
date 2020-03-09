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


#ifndef OMCore_H
#define OMCore_H

//## class OMCore
#include "omreactive.h"
//## classInstance thread
#include "omthread.h"
//## dependency AnimServices
class AnimServices;

//## auto_generated
class IOxfActive;

//## auto_generated
class IOxfEvent;

//## auto_generated
class OMAnimReactive;

//## auto_generated
class OMComponentState;

//## auto_generated
class OMMainThread;

//## auto_generated
class OMOS;

//## dependency OMOSEventFlag
class OMOSEventFlag;

//## auto_generated
class OMOSThread;

//## dependency OMThreadManager
class OMThreadManager;

//## auto_generated
class OMTimeout;

//## dependency OMTimerManager
class OMTimerManager;

//## auto_generated
class OXF;

//## package Design::oxf::Services::ResourceManagement

//## class OMCore
class OMCore : public OMReactive {
public :

    //## class OMCore::TimeReqList
    class TimeReqList {
    public :
    
        //## auto_generated
        class TimeReq;
        
        //#[ type TimeReqListType
        #ifdef OM_NO_TEMPLATES_USAGE
        typedef OMUList  TimeReqListType;
        #else
        typedef OMList<TimeReq*>  TimeReqListType;
        #endif
        //#]
        
        //#[ type TimeReqIter
        #ifdef OM_NO_TEMPLATES_USAGE
        typedef OMUIterator TimeReqIter; 
        #else
        typedef OMIterator<TimeReq*> TimeReqIter; 
        #endif // OM_NO_TEMPLATES_USAGE
        
        //#]
        
        //## class OMCore::TimeReqList::TimeReq
        class TimeReq {
            ////    Constructors and destructors    ////
            
        public :
        
            //## operation TimeReq(OMOSEventFlag,OxfTimeUnit)
            TimeReq(OMOSEventFlag* lockFlag, OxfTimeUnit t);
            
            //## auto_generated
            virtual ~TimeReq(void);
            
            ////    Additional operations    ////
            
            //## auto_generated
            OMOSEventFlag* getLock(void) const;
            
            //## auto_generated
            OxfTimeUnit getTime(void) const;
            
            //## auto_generated
            void setTime(OxfTimeUnit p_time);
            
            ////    Attributes    ////
            
        
        private :
        
            OMOSEventFlag* lock;		//## attribute lock
            
            // For future development. Currently it is not used.
            double priority;		//## attribute priority
            
            OxfTimeUnit time;		//## attribute time
            
        };
        
        ////    Constructors and destructors    ////
        
        //## auto_generated
        virtual ~TimeReqList(void);
        
        ////    Operations    ////
        
        //## operation GetStep() const
        OxfTimeUnit GetStep(void) const;
        
        //## operation IsEmpty() const
        bool IsEmpty(void) const;
        
        //## operation Reduce(OxfTimeUnit)
        void Reduce(OxfTimeUnit t);
        
        //## operation add(OMOSEventFlag,OxfTimeUnit)
        void add(OMOSEventFlag* l, OxfTimeUnit t);
        
        ////    Attributes    ////
        
    
    private :
    
        TimeReqListType list;		//## attribute list
        
    };
    
    ////    Constructors and destructors    ////
    
    //## operation OMCore(OMAffinity_t)
    explicit OMCore(const OMAffinity_t& coreIdVal);
    
    //## auto_generated
    virtual ~OMCore(void);
    
    ////    Operations    ////
    
    //## operation ElapsedTime()
    OxfTimeUnit ElapsedTime(void);
    
    //## operation consumeTime(OxfTimeUnit)
    void consumeTime(OxfTimeUnit t);
    
    //## operation startBehavior()
    virtual bool startBehavior(void);
    
    ////    Additional operations    ////
    
    //## auto_generated
    OxfTimeUnit getCoreTime(void) const;
    
    //## auto_generated
    void setCoreTime(OxfTimeUnit p_coreTime);
    
    //## auto_generated
    virtual bool cancelTimeout(const IOxfTimeout* arg);
    

protected :

    //## auto_generated
    void initStatechart(void);
    
    //## auto_generated
    void cancelTimeouts(void);
    
    ////    Attributes    ////
    

private :

    OxfTimeUnit coreTime;		//## attribute coreTime
    
    OxfTimeUnit prevTime;		//## attribute prevTime
    
    RhpReal sumPriorities;		//## attribute sumPriorities
    
    OMAffinity_t coreId;		//## attribute coreId
    
    TimeReqList reqList;		//## attribute reqList
    
    ////    Relations and components    ////
    
    // The OMCore context
    OMThread thread;		//## classInstance thread
    
    ////    Framework operations    ////
    

public :

    // rootState:
    //## statechart_method
    inline RhpBoolean rootState_IN(void) const;
    
    // timedOut:
    //## statechart_method
    inline RhpBoolean timedOut_IN(void) const;
    
    // idle:
    //## statechart_method
    inline RhpBoolean idle_IN(void) const;
    
    // busy:
    //## statechart_method
    inline RhpBoolean busy_IN(void) const;
    

protected :

    //## statechart_method
    virtual void rootState_entDef(void);
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent(void);
    
    ////    Framework    ////
    
//#[ ignore
    enum OMCore_Enum {
        OMNonState = 0,
        timedOut = 1,
        idle = 2,
        busy = 3
    };
    
//#]

private :

//#[ ignore
    OMCore_Enum rootState_subState;
    
    OMCore_Enum rootState_active;
    
    IOxfTimeout* rootState_timeout;
    
//#]
};

inline RhpBoolean OMCore::rootState_IN(void) const {
    return true;
}

inline RhpBoolean OMCore::timedOut_IN(void) const {
    return rootState_subState == timedOut;
}

inline RhpBoolean OMCore::idle_IN(void) const {
    return rootState_subState == idle;
}

inline RhpBoolean OMCore::busy_IN(void) const {
    return rootState_subState == busy;
}

#endif



