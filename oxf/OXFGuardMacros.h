//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: GuardMacros
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


#ifndef OXFGuardMacros_H
#define OXFGuardMacros_H

//## package Design::oxf::Services::Macros::GuardMacros


//#[ ignore
// Guarding macros
//#]

// Unlock a reactive object guard
//#[ type END_REACTIVE_GUARDED_SECTION
#define END_REACTIVE_GUARDED_SECTION																\
{ 																		\
	OMThread* omThread = static_cast<OMThread*>(getActiveContext());	\
	if (omThread != NULL) 												\
	{																	\
		omThread->unlock(); 											\
	}																	\
}
//#]

// Unlock an active object guard
//#[ type END_THREAD_GUARDED_SECTION
#define END_THREAD_GUARDED_SECTION { unlock(); }
//#]

// Guard an operation using an OMGuard enter-exit object
//#[ type GUARD_OPERATION
#define GUARD_OPERATION OMGuard _omGuard(getGuard()); 
//#]

// Declare an OMProtected object and helpers to support guarding of a resource
//#[ type OMDECLARE_GUARDED
#define OMDECLARE_GUARDED													\
public:																	\
	inline void lock() const { m_omGuard.lock(); }						\
	inline void unlock() const { m_omGuard.unlock(); }					\
	virtual const OMProtected& getGuard() const { return m_omGuard; }	\
private:																\
	OMProtected m_omGuard; 
//#]

// Guard a reactive object destructor
//#[ type START_DTOR_REACTIVE_GUARDED_SECTION
#define START_DTOR_REACTIVE_GUARDED_SECTION																	\
{																			\
	if (!isUnderDestruction()) 												\
	{																		\
		setUnderDestruction();												\
		OMThread* omThread = static_cast<OMThread*>(getActiveContext());	\
		if (getToGuardReactive() && (omThread != NULL))						\
		{																	\
			omThread->lock();												\
		}																	\
	}																		\
}
//#]

// Guard an active object destructor
//#[ type START_DTOR_THREAD_GUARDED_SECTION
#define START_DTOR_THREAD_GUARDED_SECTION							\
{									\
	if (!isUnderDestruction()) 		\
	{								\
		setUnderDestruction();		\
		if (shouldGuardThread()) 	\
		{							\
			OMThread::lock();		\
		}							\
	}								\
}
//#]

// Lock a reactive object guard
//#[ type START_REACTIVE_GUARDED_SECTION
#define START_REACTIVE_GUARDED_SECTION					 											\
{ 																		\
	OMThread* omThread = static_cast<OMThread*>(getActiveContext());	\
	if (omThread != NULL) 												\
	{																	\
		omThread->lock();												\
	}																	\
}
//#]

// Lock an active object guard
//#[ type START_THREAD_GUARDED_SECTION
#define START_THREAD_GUARDED_SECTION { lock(); }
//#]

#endif



