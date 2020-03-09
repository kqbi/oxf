//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: Obsolete
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


#ifndef OMObsolete_H
#define OMObsolete_H

//## dependency OMTimerManager
#include "OMTimerManager.h"
//## dependency OMUAbstractContainer
#include "OMUAbstractContainer.h"
//## package Design::oxf::Services::Macros::CompatibilityMacros::Obsolete


//#[ ignore
// Pre-5.X compatibility macros
//#]

// Add forward compatibility - use popNullTransition instead.
//#[ type popNullConfig
#define popNullConfig popNullTransition
//#]

// Add forward compatibility - use pushNullTransition instead.
//#[ type pushNullConfig
#define pushNullConfig pushNullTransition
//#]

// Add forward compatibility - use setActiveContext instead.
// 
//#[ type setThread
#define setThread setActiveContext
//#]

#endif



