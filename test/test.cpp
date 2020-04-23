/********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: TestComponent 
	Configuration 	: TestConfig
	Model Element	: test
//!	Generated Date	: Sun, 15, Dec 2019  
	File Path	: ..\..\untitled\test.cpp
*********************************************************************/

//## auto_generated
#include "test.h"
//## auto_generated
#include "testS.h"
//## package test



//## event evPoll()
evPoll::evPoll(const std::string p_notify) : notify(p_notify) {
    setId(evPoll_test_id);
}

bool evPoll::isTypeOf(const short id) const {
    return (evPoll_test_id==id);
}

//## event evDestroy()
evDestroy::evDestroy() {
    setId(evDestroy_test_id);
}

bool evDestroy::isTypeOf(const short id) const {
    return (evDestroy_test_id==id);
}

//## event evEnd()
evEnd::evEnd() {
    setId(evEnd_test_id);
}

bool evEnd::isTypeOf(const short id) const {
    return (evEnd_test_id==id);
}

/*********************************************************************
	File Path	: ..\..\untitled\test.cpp
*********************************************************************/
