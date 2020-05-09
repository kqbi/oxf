/********************************************************************
	Rhapsody	: 8.4 
	Login		: kqbi
	Component	: TestComponent 
	Configuration 	: TestConfig
	Model Element	: testS
//!	Generated Date	: Mon, 4, May 2020  
	File Path	: ..\..\untitled\testS.cpp
*********************************************************************/

//## auto_generated
#include "testS.h"
//## auto_generated
//## package test

//## class testS
testS::testS(IOxfActive* theActiveContext) : a(1) {
    setActiveContext(theActiveContext, false);
    initStatechart();
}

testS::~testS() {
    cancelTimeouts();
}

bool testS::startBehavior() {
    bool done = false;
    done = OMReactive::startBehavior();
    return done;
}

void testS::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void testS::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool testS::cancelTimeout(const IOxfTimeout::Ptr &arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

int testS::getA() const {
    return a;
}

void testS::setA(int p_a) {
    a = p_a;
}

void testS::rootState_entDef() {
    {
        rootState_subState = Idle;
        rootState_active = Idle;
        //#[ state Idle.(Entry) 
        printf("Idle in\n");
        //#]
    }
}

IOxfReactive::TakeEventStatus testS::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Idle
        case Idle:
        {
            if(IS_EVENT_TYPE_OF(evPoll_test_id))
                {
                    //## transition 8 
                    if(a)
                        {
                            //#[ state Idle.(Exit) 
                            printf("Idle out\n");
                            //#]
                            rootState_subState = Poll;
                            rootState_active = Poll;
                            //#[ state Poll.(Entry) 
                            printf("Poll in\n");
                            //#]
                            rootState_timeout = scheduleTimeout(1000, NULL);
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        // State Poll
        case Poll:
        {
            if(IS_EVENT_TYPE_OF(test_test_id))
                {
                    //#[ transition 7 
                    printf("1111111111111111111111111111\n");
                    //#]
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            //#[ state Poll.(Exit) 
                            printf("Poll out\n");
                            //#]
                            rootState_subState = Poll;
                            rootState_active = Poll;
                            //#[ state Poll.(Entry) 
                            printf("Poll in\n");
                            //#]
                            rootState_timeout = scheduleTimeout(1000, NULL);
                            res = eventConsumed;
                        }
                }
            else if(IS_EVENT_TYPE_OF(evEnd_test_id))
                {
                    cancel(rootState_timeout);
                    //#[ state Poll.(Exit) 
                    printf("Poll out\n");
                    //#]
                    rootState_subState = End;
                    rootState_active = End;
                    rootState_timeout = scheduleTimeout(5000, NULL);
                    res = eventConsumed;
                }
            
        }
        break;
        // State End
        case End:
        {
            if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            rootState_subState = state_5;
                            rootState_active = state_5;
                            res = eventConsumed;
                        }
                }
            else if(IS_EVENT_TYPE_OF(evDestroy_test_id))
                {
                    cancel(rootState_timeout);
                    rootState_subState = terminationstate_3;
                    rootState_active = terminationstate_3;
                    res = eventConsumed;
                }
            
        }
        break;
        // State state_5
        case state_5:
        {
            if(IS_EVENT_TYPE_OF(evDestroy_test_id))
                {
                    rootState_subState = terminationstate_3;
                    rootState_active = terminationstate_3;
                    res = eventConsumed;
                }
            
        }
        break;
        default:
            break;
    }
    return res;
}

/*********************************************************************
	File Path	: ..\..\untitled\testS.cpp
*********************************************************************/
