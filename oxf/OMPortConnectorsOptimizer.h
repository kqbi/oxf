//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OM_REGISTER_PORT_CONNECTOR
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


#ifndef OMPortConnectorsOptimizer_H
#define OMPortConnectorsOptimizer_H

//## dependency IOMPortConnector
#include "IOMPortConnector.h"
//## class OMPortInterfaceConnectorsOptimizer
#include "IOMPortOptimizer.h"
//## dependency OMList
#include "omlist.h"
//## dependency OMMap
#include "ommap.h"
//## dependency OMPortOptimizationManager
#include "OMPortOptimizationManager.h"
//## package Design::oxf::Services::Ports::PortsOptimization

//## class OMPortInterfaceConnectorsOptimizer
// Keep a list of port connectors by creating instances of the nested Connector class. 
// New connectors are added by calling the RegisterConnector method. 
// Optimization is done by the Optimize method. Cleanup frees the list of 
// connectors. 
template <class TPortInterface> class OMPortInterfaceConnectorsOptimizer : public IOMPortOptimizer {
public :

    //## auto_generated
    class Connector;
    
    //#[ type Port
    typedef IOMPortConnector<TPortInterface> Port;
    //#]
    
    //## type PortInterface
    typedef TPortInterface PortInterface;
    
    //#[ type ConnectorIterator
    typedef OMIterator<Connector*> ConnectorIterator;
    //#]
    
    //#[ type ConnectorList
    typedef OMList<Connector*> ConnectorList;
    //#]
    
    //#[ type Interface2ConnectorMap
    typedef OMMap<TPortInterface*,Connector*> Interface2ConnectorMap;
    //#]
    
    //## class OMPortInterfaceConnectorsOptimizer::Connector
    class Connector {
    public :
    
        // Add new and delete overrides to make use of the freamework memory management.
        //#[ type OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
        OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS;
        //#]
        
        ////    Constructors and destructors    ////
        
        //## operation Connector()
        inline Connector(void) {
            //#[ operation Connector()
            //#]
        }
        
        //## operation ~Connector()
        inline ~Connector(void) {
            //#[ operation ~Connector()
            //#]
        }
        
        ////    Attributes    ////
        
        Port* port;		//## attribute port
        
        PortInterface* targetInterface;		//## attribute targetInterface
        
    };
    
    ////    Constructors and destructors    ////
    
    //## operation ~OMPortInterfaceConnectorsOptimizer()
    ~OMPortInterfaceConnectorsOptimizer(void);
    
    ////    Operations    ////
    
    // Removes and deletes the connectors stored in the list and the map.
    //## operation Cleanup()
    void Cleanup(void);
    
    // Optimize all the connectors registered for a given interface. 
    //## operation Optimize()
    void Optimize(void);
    
    //## operation RegisterConnector(Port,PortInterface,PortInterface)
    inline void RegisterConnector(Port* const port, PortInterface* const source, PortInterface* const target) {
        //#[ operation RegisterConnector(Port,PortInterface,PortInterface)
        if (port != NULL && 
        	source != NULL && 
        	target != NULL)
        {
        	Connector* connector = new Connector();
        	if (connector != NULL)
        	{
        		connector->port = port;
        		connector->targetInterface = target;
        		m_interface2ConnectorMap.add(source, connector);
        		m_allConnectorsList.add(connector);
        	}
        }
        //#]
    }
    

private :

    // Optimize the connector by finding a chain of connectors starting from the given one. 
    // The chain is build by looking for the target of each connector inside the map
    // and funding the next element of the chain. Continue untill target of the last connector in the chain
    // is no longer found in the map. 
    //## operation OptimizeConnector(Connector* const)
    void OptimizeConnector(Connector* const connector);
    
    ////    Attributes    ////
    
    ConnectorList m_allConnectorsList;		//## attribute m_allConnectorsList
    
    Interface2ConnectorMap m_interface2ConnectorMap;		//## attribute m_interface2ConnectorMap
    
};

//## package Design::oxf::Services::Ports::PortsOptimization

//## class OMPortInterfaceConnectorsOptimizerFacade
// Provides an instance of OMPortConnectorsOptimizer class. Used by 
// OM_REGISTER_PORT_CONNECTOR macro. 
template <class TPortInterface> class OMPortInterfaceConnectorsOptimizerFacade {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    ~OMPortInterfaceConnectorsOptimizerFacade(void);
    
    ////    Operations    ////
    
    //## operation getInstance()
    static OMPortInterfaceConnectorsOptimizer<TPortInterface>& getInstance(void);
    
};

//#[ type OM_REGISTER_PORT_CONNECTOR
#define OM_REGISTER_PORT_CONNECTOR(TInterface, target) OMPortInterfaceConnectorsOptimizerFacade<TInterface>::getInstance().RegisterConnector(this, this, target);
//#]

//#[ type OM_OPTIMIZE_PORT_CONNECTORS
#define OM_OPTIMIZE_PORT_CONNECTORS OMPortOptimizationManager::getInstance().RunAllOptimizers();
//#]

//## package Design::oxf::Services::Ports::PortsOptimization

//## class OMPortInterfaceConnectorsOptimizerFacade
template <class TPortInterface> OMPortInterfaceConnectorsOptimizer<TPortInterface>&
 OMPortInterfaceConnectorsOptimizerFacade<TPortInterface>::getInstance(void) {
    //#[ operation getInstance()
    // static instance of optimizer per interface
    static OMPortInterfaceConnectorsOptimizer<TPortInterface> m_instance; 
    
    // register instance in the optimization manager
    OMPortOptimizationManager::getInstance().RegisterOptimizer(m_instance);
    
    return m_instance;
    //#]
}

template <class TPortInterface> OMPortInterfaceConnectorsOptimizerFacade<TPortInterface>
::~OMPortInterfaceConnectorsOptimizerFacade(void) {
}

//## package Design::oxf::Services::Ports::PortsOptimization

//## class OMPortInterfaceConnectorsOptimizer
template <class TPortInterface> OMPortInterfaceConnectorsOptimizer<TPortInterface>::~OMPortInterfaceConnectorsOptimizer
(void) {
    //#[ operation ~OMPortInterfaceConnectorsOptimizer()
    Cleanup();
    //#]
}

template <class TPortInterface> void OMPortInterfaceConnectorsOptimizer<TPortInterface>::Cleanup(void) {
    //#[ operation Cleanup()
    ConnectorIterator iter(m_allConnectorsList);
    while ((*iter) != NULL)
    {
    	delete *iter;
    	++iter;
    }
    m_allConnectorsList.removeAll();
    m_interface2ConnectorMap.removeAll();
    
    //#]
}

template <class TPortInterface> void OMPortInterfaceConnectorsOptimizer<TPortInterface>::Optimize(void) {
    //#[ operation Optimize()
    ConnectorIterator iter(m_allConnectorsList);
    while ((*iter) != NULL)
    {
    	OptimizeConnector(*iter);
    	++iter;
    }
    //#]
}

template <class TPortInterface> void OMPortInterfaceConnectorsOptimizer<TPortInterface>::OptimizeConnector
(Connector* const connector) {
    //#[ operation OptimizeConnector(Connector* const)
    //
    // connector is the first connector in the chain to be found. 
    //
    if (connector != NULL)
    { 
    	//                                
    	// create a list to store the chain of connectors.
    	//
    	ConnectorList chain; 
    	Connector* currentConnector = connector;
        
    	//
    	// currentConnector represents the next connector in the chain. 
    	// loop until it exists 
    	//    
    	while (currentConnector != NULL && currentConnector->targetInterface != NULL)
    	{    
    		// 
    		// add the connector found to the chain
    		//
    		chain.add(currentConnector);		
    		//
    		// jump from current connector to the next one 
    		// by finding its target in the map. 
    		// 	
    		currentConnector = m_interface2ConnectorMap[currentConnector->targetInterface];
    	}
    
    	//
    	// if chain contains more that one connector
    	// a shortcut can be created between each 
    	// element in the chain to the last one.
    	//	
    	if (chain.getCount() >= 2)
    	{
    		//
    		// get last element in the chain
    		//
    		Connector* tail = chain.getLastConcept();	
    		//
    		// interate through the chain
    		//
    		ConnectorIterator iter(chain);
    		while ((*iter) != NULL)
    		{   
    			Connector * currentChainItem = (*iter);
    			//
    			// all elements but the last should be updated
    			//
    			if (currentChainItem != tail) 
    			{
    				// 
    				// update the current connector item
    				//
    				currentChainItem->targetInterface = tail->targetInterface;
    
    				//				
    				// update the target of the port
    				//
    				if (currentChainItem->port != NULL)
    				{
    					currentChainItem->port->setItsTarget(tail->targetInterface); 
    				}
    			}
    			++iter;
    		}
    	}
    }
    //#]
}

#endif



