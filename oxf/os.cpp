//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMOSThread
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
#include "os.h"
//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSThread
//#[ ignore
/*

//#]
const Rhp_int32_t OMOSThread::DefaultMessageQueueSize = 100;
//#[ ignore

*/
//#]

//#[ ignore
/*

//#]
const Rhp_int32_t OMOSThread::DefaultStackSize = 1000;
//#[ ignore

*/
//#]

//#[ ignore
/*

//#]
const Rhp_int32_t OMOSThread::DefaultThreadPriority = 0;
//#[ ignore

*/
//#]

bool OMOSThread::exeOnMyThread(void) {
    //#[ operation exeOnMyThread()
    // a handle to the thread that executes the delete
    void * executedOsHandle = OMOSFactory::instance()->getCurrentThreadHandle();
    // a handle to this' 'thread'
    void * myOsHandle = getOsHandle();
    
    bool res = ((executedOsHandle == myOsHandle) ? true : false);
    return res;
    //#]
}




