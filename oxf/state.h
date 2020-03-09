//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: ReusableBaseStates
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


#ifndef state_H
#define state_H

//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency IOxfReactive
#include "IOxfReactive.h"
//## dependency Manager
#include "OXFManager.h"
//## dependency AOMInstance
class AOMInstance;

//## dependency AOMSState
class AOMSState;

//## dependency AnimServices
class AnimServices;

//## link concept
class IOxfReactive;

//## auto_generated
class OMAndState;

//## link component
class OMComponentState;

//## auto_generated
class OMFinalState;

//## auto_generated
class OMLeafState;

//## auto_generated
class OMOrState;

//## auto_generated
class OMState;

//## package Design::oxf::Services::ReusableBaseStates


//#[ ignore
// Reusable statechart implementation support
//#]

// Make IReactive::TakeEventStatus literals available in state classes
//#[ type eventConsumed
#define eventConsumed IOxfReactive::eventConsumed
//#]

// Make IReactive::TakeEventStatus literals available in state classes
//#[ type eventNotConsumed
#define eventNotConsumed IOxfReactive::eventNotConsumed
//#]

// Make IReactive::TakeEventStatus literals available in state classes
//#[ type instanceReachTerminate
#define instanceReachTerminate IOxfReactive::instanceReachTerminate
//#]

// Make IReactive::TakeEventStatus literals available in state classes
//#[ type instanceUnderDestruction
#define instanceUnderDestruction IOxfReactive::instanceUnderDestruction
//#]

//## package Design::oxf::Services::ReusableBaseStates

//## class OMState
// The base state class
class RP_FRAMEWORK_DLL OMState {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Initialize
    // Argument OMState* par = NULL :
    // The parent state
    //## operation OMState(OMState*)
    explicit inline OMState(OMState* par = NULL) : stateHandle(NULL), parent(par) {
        //#[ operation OMState(OMState*)
        //#]
    }
    
    //## auto_generated
    virtual ~OMState(void);
    
    ////    Operations    ////
    
    // Enter this state via the default transition
    //## operation entDef()
    virtual void entDef(void) = 0;
    
    // Enter a state via a history connector.
    //## operation entHist()
    virtual void entHist(void);
    
    // Enter a state via a shallow history connector.
    //## operation entShallowHist()
    virtual void entShallowHist(void);
    
    // Enter this state
    //## operation enterState()
    virtual void enterState(void) = 0;
    
    // Exit from this state
    //## operation exitState()
    virtual void exitState(void) = 0;
    
    // Get the last active state in this sub graph (for history connector support)
    //## operation getLastState()
    virtual OMState* getLastState(void);
    
    // Get the active sub state
    //## operation getSubState()
    virtual OMState* getSubState(void);
    
    // Handle the current event (of the reactive owner)
    //## operation handleEvent()
    virtual IOxfReactive::TakeEventStatus handleEvent(void);
    
    // Check is this state is in the active states graph
    //## operation in()
    virtual bool in(void) = 0;
    
    // Check is this state is completed (the sub graph reached a final state)
    //## operation isCompleted()
    virtual bool isCompleted(void);
    
    // Serialize the state graph (instrumentation)
    // Argument AOMSState* /*s*/ :
    // The serialization data
    //## operation serializeStates(AOMSState) const
    inline virtual void serializeStates(AOMSState* /*s*/) const {
        //#[ operation serializeStates(AOMSState) const
        //#]
    }
    
    // Set the last active state in this sub graph (for history connector support)
    // Argument OMState* /*s*/ :
    // The last state
    //## operation setLastState(OMState)
    virtual void setLastState(OMState* /*s*/);
    
    // Set the active sub state
    // Argument OMState* /*s*/ :
    // The new sub state
    //## operation setSubState(OMState)
    virtual void setSubState(OMState* /*s*/);
    

protected :

    // Get the reactive owner of this state
    //## operation getConcept() const
    virtual AOMInstance* getConcept(void) const;
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    const Rhp_char_t* getHandle(void) const;
    
    //## auto_generated
    void setHandle(const Rhp_char_t* p_stateHandle);
    
    //## auto_generated
    OMState* getParent(void) const;
    
    //## auto_generated
    void setParent(OMState* p_OMState);
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Attributes    ////
    
    // The state name (for instrumentation)
    const Rhp_char_t* stateHandle;		//## attribute stateHandle
    
    ////    Relations and components    ////
    

public :

    // The parent state
    OMState* parent;		//## link parent
    
};

//## package Design::oxf::Services::ReusableBaseStates

//## class OMOrState
// A non-concurrent composite state
class RP_FRAMEWORK_DLL OMOrState : public OMState {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    // Argument OMState* par = NULL :
    // The parent state
    //## operation OMOrState(OMState)
    explicit inline OMOrState(OMState* par = NULL) : OMState(par), subState(NULL)  {
        //#[ operation OMOrState(OMState)
        //#]
    }
    
    //## auto_generated
    virtual ~OMOrState(void);
    
    ////    Operations    ////
    
    // Enter this state via the default transition
    //## operation entDef()
    virtual void entDef(void);
    
    // Enter this state
    //## operation enterState()
    virtual void enterState(void);
    
    // Exit from this state
    //## operation exitState()
    virtual void exitState(void);
    
    // Check is this state is in the active states graph
    //## operation in()
    inline virtual bool in(void) {
        //#[ operation in()
        return parent->getSubState() == this;
        //#]
    }
    
    // Serialize the state graph (instrumentation)
    // Argument AOMSState* aomArg(s) :
    // The serialization data
    //## operation serializeStates(AOMSState) const
    //#[ ignore
    #ifdef _OMINSTRUMENT
    
    //#]
    virtual void serializeStates(AOMSState* aomArg(s)) const;
    //#[ ignore
    
    #endif // _OMINSTRUMENT
    //#]
    
    ////    Additional operations    ////
    
    //## auto_generated
    OMState* getSubState(void);
    
    //## auto_generated
    void setSubState(OMState* p_OMState);
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Relations and components    ////
    

public :

    // The direct sub state that is part of the active graph
    OMState* subState;		//## link subState
    
};

//## package Design::oxf::Services::ReusableBaseStates

//## class OMComponentState
// A part of an AND state or the root state
class RP_FRAMEWORK_DLL OMComponentState : public OMOrState {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    // Argument OMState* par = NULL :
    // The parent state
    //## operation OMComponentState(OMState)
    explicit inline OMComponentState(OMState* par = NULL) : OMOrState(par), active(NULL)  {
        //#[ operation OMComponentState(OMState)
        //#]
    }
    
    //## auto_generated
    virtual ~OMComponentState(void);
    
    ////    Operations    ////
    
    // Enter into this state
    //## operation enterState()
    virtual void enterState(void);
    
    // Handle the current event
    //## operation handleEvent()
    virtual IOxfReactive::TakeEventStatus handleEvent(void);
    
    // Check is this state is in the active states graph
    //## operation in()
    virtual bool in(void);
    
    ////    Additional operations    ////
    
    //## auto_generated
    OMState* getActive(void) const;
    
    //## auto_generated
    void setActive(OMState* p_OMState);
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Relations and components    ////
    

public :

    // The active sub state
    OMState* active;		//## link active
    
};

//## package Design::oxf::Services::ReusableBaseStates

//## class OMLeafState
// A simple state that doesn't contain additional states
class RP_FRAMEWORK_DLL OMLeafState : public OMState {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    // Argument OMState* par :
    // The parent state
    // Argument OMState* cmp :
    // A parent component state
    //## operation OMLeafState(OMState,OMState)
    OMLeafState(OMState* par, OMState* cmp);
    
    //## auto_generated
    virtual ~OMLeafState(void);
    
    ////    Operations    ////
    
    // Take the state default transition
    //## operation entDef()
    virtual void entDef(void);
    
    // Enter the state
    //## operation enterState()
    virtual void enterState(void);
    
    // Exit the state
    //## operation exitState()
    virtual void exitState(void);
    
    // Check is this state is in the active states graph
    //## operation in()
    virtual bool in(void);
    
    // Serialize the state graph (instrumentation)
    // Argument AOMSState* aomArg(s) :
    // The serialization data
    //## operation serializeStates(AOMSState) const
    //#[ ignore
    #ifdef _OMINSTRUMENT
    
    //#]
    virtual void serializeStates(AOMSState* aomArg(s)) const;
    //#[ ignore
    
    #endif // _OMINSTRUMENT
    //#]
    
    ////    Additional operations    ////
    
    //## auto_generated
    OMComponentState* getComponent(void) const;
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Relations and components    ////
    

public :

    OMComponentState* component;		//## link component
    
};

//## package Design::oxf::Services::ReusableBaseStates

//## class OMAndState
// A concurrent state
class RP_FRAMEWORK_DLL OMAndState : public OMLeafState {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    // Argument OMState* par :
    // The parent state
    // Argument OMState* cmp :
    // A parent OMComponentState
    //## operation OMAndState(OMState,OMState)
    OMAndState(OMState* par, OMState* cmp);
    
    //## auto_generated
    ~OMAndState(void);
    
    ////    Operations    ////
    
    // Set the lock
    //## operation lock()
    void lock(void);
    
    // Unset the lock
    //## operation unlock()
    void unlock(void);
    
    ////    Additional operations    ////
    

private :

    //## auto_generated
    bool get_lock(void) const;
    
    ////    Attributes    ////
    
    // A locked flag
    bool _lock;		//## attribute _lock
    
};

//## package Design::oxf::Services::ReusableBaseStates

//## class OMFinalState
// UML Final state
class RP_FRAMEWORK_DLL OMFinalState : public OMLeafState {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    // Argument IOxfReactive* cpt :
    // The reactive owner
    // Argument OMState* par :
    // The parent state
    // Argument OMState* cmp :
    // A parent component state
    // Argument const Rhp_const_char_pt aomArg(hdl) = NULL :
    // The state name
    //## operation OMFinalState(IOxfReactive,OMState,OMState,Rhp_const_char_pt)
    inline OMFinalState(IOxfReactive* cpt, OMState* par, OMState* cmp, const Rhp_const_char_pt aomArg(hdl) = NULL
) : OMLeafState(par, cmp), concept(cpt)
     	 {
        //#[ operation OMFinalState(IOxfReactive,OMState,OMState,Rhp_const_char_pt)
        #ifdef _OMINSTRUMENT
        setHandle(hdl);
        #endif // _OMINSTRUMENT
        //#]
    }
    
    //## auto_generated
    virtual ~OMFinalState(void);
    
    ////    Operations    ////
    

protected :

    // Get the reactive owner
    //## operation getConcept() const
    //#[ ignore
    #ifdef _OMINSTRUMENT
    
    //#]
    virtual AOMInstance* getConcept(void) const;
    //#[ ignore
    
    #endif // _OMINSTRUMENT
    //#]
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    void setConcept(IOxfReactive* p_IOxfReactive);
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Relations and components    ////
    

private :

    // The reactive owner
    IOxfReactive* concept;		//## link concept
    
};

#endif



