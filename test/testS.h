/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: TestComponent 
	Configuration 	: TestConfig
	Model Element	: testS
//!	Generated Date	: Sun, 15, Dec 2019  
	File Path	: ..\..\untitled\testS.h
*********************************************************************/

#ifndef testS_H
#define testS_H

//## auto_generated
#include "test.h"
//## auto_generated
#include <omreactive.h>
//## auto_generated
#include <state.h>
//## auto_generated
#include <event.h>
//## package test

//## class testS
class testS : public OMReactive {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    testS(IOxfActive* theActiveContext = 0);
    
    //## auto_generated
    ~testS();
    
    ////    Additional operations    ////
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cancelTimeouts();
    
    //## auto_generated
    bool cancelTimeout(const IOxfTimeout::Ptr& arg);
    
    ////    Framework operations    ////
    
    ////    Framework    ////

public :

    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    inline bool rootState_isCompleted();
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // terminationstate_3:
    //## statechart_method
    inline bool terminationstate_3_IN() const;
    
    // state_5:
    //## statechart_method
    inline bool state_5_IN() const;
    
    // Poll:
    //## statechart_method
    inline bool Poll_IN() const;
    
    // Idle:
    //## statechart_method
    inline bool Idle_IN() const;
    
    // End:
    //## statechart_method
    inline bool End_IN() const;

protected :

//#[ ignore
    enum testS_Enum {
        OMNonState = 0,
        terminationstate_3 = 1,
        state_5 = 2,
        Poll = 3,
        Idle = 4,
        End = 5
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    std::shared_ptr<IOxfTimeout> rootState_timeout;
//#]
};

inline bool testS::rootState_IN() const {
    return true;
}

inline bool testS::rootState_isCompleted() {
    return ( IS_IN(terminationstate_3) );
}

inline bool testS::terminationstate_3_IN() const {
    return rootState_subState == terminationstate_3;
}

inline bool testS::state_5_IN() const {
    return rootState_subState == state_5;
}

inline bool testS::Poll_IN() const {
    return rootState_subState == Poll;
}

inline bool testS::Idle_IN() const {
    return rootState_subState == Idle;
}

inline bool testS::End_IN() const {
    return rootState_subState == End;
}

#endif
/*********************************************************************
	File Path	: ..\..\untitled\testS.h
*********************************************************************/