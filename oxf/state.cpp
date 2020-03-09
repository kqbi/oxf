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



//## auto_generated
#include "state.h"
//## link concept
#include "IOxfReactive.h"
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## package Design::oxf::Services::ReusableBaseStates



//## package Design::oxf::Services::ReusableBaseStates

//## class OMState
OMState::~OMState(void) {
    cleanUpRelations();
}

void OMState::entHist(void) {
    //#[ operation entHist()
    //#]
}

void OMState::entShallowHist(void) {
    //#[ operation entShallowHist()
    //#]
}

OMState* OMState::getLastState(void) {
    //#[ operation getLastState()
    return NULL;
    //#]
}

OMState* OMState::getSubState(void) {
    //#[ operation getSubState()
    return NULL;
    //#]
}

IOxfReactive::TakeEventStatus OMState::handleEvent(void) {
    //#[ operation handleEvent()
    IOxfReactive::TakeEventStatus retValue = eventNotConsumed;
    if (parent != NULL) {
    	retValue = parent->handleEvent();
    }
    return retValue;
    //#]
}

bool OMState::isCompleted(void) {
    //#[ operation isCompleted()
    return true;
    //#]
}

void OMState::setLastState(OMState* /*s*/) {
    //#[ operation setLastState(OMState)
    //#]
}

void OMState::setSubState(OMState* /*s*/) {
    //#[ operation setSubState(OMState)
    //#]
}

AOMInstance* OMState::getConcept(void) const {
    //#[ operation getConcept() const
    return NULL;
    //#]
}

const Rhp_char_t* OMState::getHandle(void) const {
    return stateHandle;
}

void OMState::setHandle(const Rhp_char_t* p_stateHandle) {
    stateHandle = p_stateHandle;
}

OMState* OMState::getParent(void) const {
    return parent;
}

void OMState::setParent(OMState* p_OMState) {
    parent = p_OMState;
}

void OMState::cleanUpRelations(void) {
    if(parent != NULL)
        {
            parent = NULL;
        }
}

//## package Design::oxf::Services::ReusableBaseStates

//## class OMOrState
OMOrState::~OMOrState(void) {
    cleanUpRelations();
}

void OMOrState::entDef(void) {
    //#[ operation entDef()
    enterState();
    if(subState != NULL) {
    	subState->entDef();
    }
    //#]
}

void OMOrState::enterState(void) {
    //#[ operation enterState()
    if (parent != NULL) {
    	parent->setSubState(this);
    }
    #ifdef _OMINSTRUMENT
    AnimServices::notifyStateEntered(getConcept(), getHandle());
    #endif
    //#]
}

void OMOrState::exitState(void) {
    //#[ operation exitState()
    if(subState != NULL) {
    	subState->exitState();
    	subState = NULL;
    }
    #ifdef _OMINSTRUMENT
    AnimServices::notifyStateExited(getConcept(), getHandle());
    #endif
    //#]
}

//#[ ignore
#ifdef _OMINSTRUMENT

//#]
void OMOrState::serializeStates(AOMSState* aomArg(s)) const {
    //#[ operation serializeStates(AOMSState) const
    AnimServices::addState(s, getHandle());
    if (subState != NULL) {
    	subState->serializeStates(s);
    }
    //#]
}
//#[ ignore


#endif // _OMINSTRUMENT
//#]

OMState* OMOrState::getSubState(void) {
    return subState;
}

void OMOrState::setSubState(OMState* p_OMState) {
    subState = p_OMState;
}

void OMOrState::cleanUpRelations(void) {
    if(subState != NULL)
        {
            subState = NULL;
        }
}

//## package Design::oxf::Services::ReusableBaseStates

//## class OMComponentState
OMComponentState::~OMComponentState(void) {
    cleanUpRelations();
}

void OMComponentState::enterState(void) {
    //#[ operation enterState()
    #ifdef _OMINSTRUMENT
    AnimServices::notifyStateEntered(getConcept(), getHandle());
    #endif
    //#]
}

IOxfReactive::TakeEventStatus OMComponentState::handleEvent(void) {
    //#[ operation handleEvent()
    return eventNotConsumed;
    //#]
}

bool OMComponentState::in(void) {
    //#[ operation in()
    bool status;
    if (parent != NULL) {
        // Is It Root state 
    	status = parent->in(); // Components are always in if their parent is in
    } else {
    	status = true;
    }
    return status;
    //#]
}

OMState* OMComponentState::getActive(void) const {
    return active;
}

void OMComponentState::setActive(OMState* p_OMState) {
    active = p_OMState;
}

void OMComponentState::cleanUpRelations(void) {
    if(active != NULL)
        {
            active = NULL;
        }
}

//## package Design::oxf::Services::ReusableBaseStates

//## class OMLeafState
OMLeafState::OMLeafState(OMState* par, OMState* cmp) : OMState(par), component(static_cast<OMComponentState*>(cmp)) 
  {
    //#[ operation OMLeafState(OMState,OMState)
    //#]
}

OMLeafState::~OMLeafState(void) {
    cleanUpRelations();
}

void OMLeafState::entDef(void) {
    //#[ operation entDef()
    enterState();
    //#]
}

void OMLeafState::enterState(void) {
    //#[ operation enterState()
    if (parent != NULL) {
    	parent->setSubState(this);
    }
    component->active = this;  // Setting the activeState of the component
    #ifdef _OMINSTRUMENT
    AnimServices::notifyStateEntered(getConcept(), getHandle());
    #endif
    //#]
}

void OMLeafState::exitState(void) {
    //#[ operation exitState()
    #ifdef _OMINSTRUMENT
    AnimServices::notifyStateExited(getConcept(), getHandle());
    #endif
    //#]
}

bool OMLeafState::in(void) {
    //#[ operation in()
    bool in_me = false;
    if (parent != NULL) {
    	in_me = (parent->getSubState() == this);
    }
    return in_me;
    //#]
}

//#[ ignore
#ifdef _OMINSTRUMENT

//#]
void OMLeafState::serializeStates(AOMSState* aomArg(s)) const {
    //#[ operation serializeStates(AOMSState) const
    AnimServices::addState(s, getHandle());
    //#]
}
//#[ ignore


#endif // _OMINSTRUMENT
//#]

OMComponentState* OMLeafState::getComponent(void) const {
    return component;
}

void OMLeafState::cleanUpRelations(void) {
    if(component != NULL)
        {
            component = NULL;
        }
}

//## package Design::oxf::Services::ReusableBaseStates

//## class OMAndState
OMAndState::OMAndState(OMState* par, OMState* cmp) : OMLeafState(par, cmp), _lock(false)
  {
    //#[ operation OMAndState(OMState,OMState)
    //#]
}

OMAndState::~OMAndState(void) {
}

void OMAndState::lock(void) {
    //#[ operation lock()
    _lock = true;
    //#]
}

void OMAndState::unlock(void) {
    //#[ operation unlock()
    _lock = false;
    //#]
}

bool OMAndState::get_lock(void) const {
    return _lock;
}

//## package Design::oxf::Services::ReusableBaseStates

//## class OMFinalState
OMFinalState::~OMFinalState(void) {
    cleanUpRelations();
}

//#[ ignore
#ifdef _OMINSTRUMENT

//#]
AOMInstance* OMFinalState::getConcept(void) const {
    //#[ operation getConcept() const
    return AnimServices::getAnimInstance(concept);
    //#]
}
//#[ ignore


#endif // _OMINSTRUMENT
//#]

void OMFinalState::setConcept(IOxfReactive* p_IOxfReactive) {
    concept = p_IOxfReactive;
}

void OMFinalState::cleanUpRelations(void) {
    if(concept != NULL)
        {
            concept = NULL;
        }
}




