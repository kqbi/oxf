/********************************************************************
	Rhapsody	: 8.4 
	Login		: kqbi
	Component	: TestComponent 
	Configuration 	: TestConfig
	Model Element	: test
//!	Generated Date	: Mon, 4, May 2020  
	File Path	: ..\..\untitled\test.cpp
*********************************************************************/

//## auto_generated
#include "test.h"
//## auto_generated
#include "testS.h"
//## package test



//## event evPoll()
evPoll::evPoll() {
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

//## event test()
test::test() {
    setId(test_test_id);
}

bool test::isTypeOf(const short id) const {
    return (test_test_id==id);
}

/*********************************************************************
	File Path	: ..\..\untitled\test.cpp
*********************************************************************/
