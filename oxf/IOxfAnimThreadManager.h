//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfAnimThreadManager
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


#ifndef IOxfAnimThreadManager_H
#define IOxfAnimThreadManager_H

//## dependency IOxfActive
class IOxfActive;

//## package Design::oxf::Anim::AnimAPI

//## class IOxfAnimThreadManager
// An animation interface to thethreads manager singleton class implementation.
// Enables the animation layer to communicate with the threads manager in order to control threads
class RP_FRAMEWORK_DLL IOxfAnimThreadManager {
    ////    Constructors and destructors    ////
    
public :

    // Cleanup
    //## operation ~IOxfAnimThreadManager()
    inline virtual ~IOxfAnimThreadManager(void) {
        //#[ operation ~IOxfAnimThreadManager()
        //#]
    }
    
    ////    Operations    ////
    
    // Wakeup the specified thread (the thread is supposed to be waiting for events)
    // Argument IOxfActive* thread :
    // The thread to wakeup
    //## operation wakeup(IOxfActive) const
    virtual void wakeup(IOxfActive* thread) const = 0;
    
};

#endif



