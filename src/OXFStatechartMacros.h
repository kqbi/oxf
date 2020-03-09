//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: StatechartMacros
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


#ifndef OXFStatechartMacros_H
#define OXFStatechartMacros_H

//## package Design::oxf::Services::Macros::StatechartMacros


//#[ ignore
// Statechart helper macros to support reusable and flat statechart implementation
//#]

// Check if the specified state reached completion.
// A macro is used to support both flat and reusable statechart implementation.
//#[ type IS_COMPLETED
#ifndef OM_REUSABLE_STATECHART_IMPLEMENTATION
#define IS_COMPLETED(state) state##_isCompleted()
#else
#define IS_COMPLETED(state) state->isCompleted()
#endif // OM_REUSABLE_STATECHART_IMPLEMENTATION
//#]

// Test if the current event is of the type of the given id.
// A macro is used to support both flat and reusable statechart implementation.
//#[ type IS_EVENT_TYPE_OF
#ifndef OM_REUSABLE_STATECHART_IMPLEMENTATION
#define IS_EVENT_TYPE_OF(id) ((getCurrentEvent() != NULL) ? getCurrentEvent()->isTypeOf((id)) : false)
#else
#define IS_EVENT_TYPE_OF(id) (((concept != NULL) && ((concept->getCurrentEvent()) != NULL)) ? (concept->getCurrentEvent())->isTypeOf((id)) : false)
#endif // OM_REUSABLE_STATECHART_IMPLEMENTATION
//#]

// Check if the given state is active.
// A macro is used to support both flat and reusable statechart implementation.
//#[ type IS_IN
#ifndef OM_REUSABLE_STATECHART_IMPLEMENTATION
#define IS_IN(state) state##_IN()
#else
#define IS_IN(state) state->in()
#endif // OM_REUSABLE_STATECHART_IMPLEMENTATION
//#]

// Set a triggered operation return value.
// A macro is used to support both flat and reusable statechart implementation.
//#[ type OMREPLY
#define OMREPLY(retVal)		(params->om_reply = retVal)
//#]

// Set a local variable  called params of the specific event type to enable access to the current event data.
// A macro is used to support both flat and reusable statechart implementation.
//#[ type OMSETPARAMS
//#[ ignore
//lint -save -e773  Expression-like macro not parenthesized

//#]
#define OMSETPARAMS(type) type* params = static_cast<type*>(getCurrentEvent())
//#[ ignore

//lint -restore
//#]
//#]

// Shorted name for OMREPLY
//#[ type reply
#define reply(retVal)	OMREPLY(retVal)
//#]

// Shorted name for OMSETPARAMS
//#[ type SETPARAMS
#define SETPARAMS(type) OMSETPARAMS(type)
//#]

// Get the current event id.
// A macro is used to support both flat and reusable statechart implementation.
//#[ type OM_CURRENT_EVENT_ID
#ifndef OM_REUSABLE_STATECHART_IMPLEMENTATION
#define OM_CURRENT_EVENT_ID ((getCurrentEvent() != NULL) ? getCurrentEvent()->getId() : 0)
#else
#define OM_CURRENT_EVENT_ID (((concept != NULL) && ((concept->getCurrentEvent()) != NULL)) ? (concept->getCurrentEvent())->getId() : 0)
#endif // OM_REUSABLE_STATECHART_IMPLEMENTATION
//#]

#endif



