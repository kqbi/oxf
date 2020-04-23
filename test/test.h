/*********************************************************************
	Rhapsody	: 8.4 
	Login		: Administrator
	Component	: TestComponent 
	Configuration 	: TestConfig
	Model Element	: test
//!	Generated Date	: Sun, 15, Dec 2019  
	File Path	: ..\..\untitled\test.h
*********************************************************************/

#ifndef test_H
#define test_H

//## auto_generated
#include <event.h>
//## auto_generated
class testS;

//#[ ignore
#define evPoll_test_id 28001

#define evDestroy_test_id 28002

#define evEnd_test_id 28003
//#]

//## package test


//## attribute test_H_1
#define test_H_1

//## event evPoll()
class evPoll : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evPoll();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(const short id) const;
};

//## event evDestroy()
class evDestroy : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evDestroy();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(const short id) const;
};

//## event evEnd()
class evEnd : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evEnd();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(const short id) const;
};

#endif
/*********************************************************************
	File Path	: ..\..\untitled\test.h
*********************************************************************/