//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMPortOptimizationManager
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


#ifndef OMPortOptimizationManager_H
#define OMPortOptimizationManager_H

//## dependency IOMPortOptimizer
#include "IOMPortOptimizer.h"
//## dependency OMList
#include "omlist.h"
//## package Design::oxf::Services::Ports::PortsOptimization

//## class OMPortOptimizationManager
// Manages collection of IOMPortOptimizer interfaces. 
// Allows to add and execute optimizers. 
class RP_FRAMEWORK_DLL OMPortOptimizationManager {
public :

    //#[ type OptimizerList
    typedef OMList<IOMPortOptimizer*> OptimizerList;
    //#]
    
    //#[ type OptimizerIterator
    typedef OMIterator<IOMPortOptimizer*> OptimizerIterator;
    //#]
    
    //## type OptimizerInterface
    typedef IOMPortOptimizer OptimizerInterface;
    
    ////    Operations    ////
    
    // Add optimizer to the managers' list
    //## operation RegisterOptimizer(OptimizerInterface)
    inline void RegisterOptimizer(OptimizerInterface& optimizer) {
        //#[ operation RegisterOptimizer(OptimizerInterface)
        if (!m_optimizersList.find(&optimizer))
        {
        	m_optimizersList.add(&optimizer);
        }
        //#]
    }
    
    // Iterate through registered optimizers, execute and cleanup one by one. 
    //## operation RunAllOptimizers()
    inline void RunAllOptimizers(void) {
        //#[ operation RunAllOptimizers()
        OptimizerIterator iter(m_optimizersList);
        while ((*iter) != NULL)
        {
        	(*iter)->Optimize();
        	(*iter)->Cleanup();	 
        	++iter;
        }
        //#]
    }
    
    //## operation getInstance()
    inline static OMPortOptimizationManager& getInstance(void) {
        //#[ operation getInstance()
        static OMPortOptimizationManager instance;
        return instance; 
        //#]
    }
    
    ////    Attributes    ////
    

private :

    OptimizerList m_optimizersList;		//## attribute m_optimizersList
    
};

#endif



