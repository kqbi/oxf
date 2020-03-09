//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMValueCompare
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


#ifndef OMValueCompare_H
#define OMValueCompare_H

//## auto_generated
#include <utility>
//## package Design::oxf::Services::Containers::STLContainersSupport

//## class OMValueCompare
// STL compare functor.
// Used for qualified relations that are implemented with STL containers.
template <class Key, class Value> class OMValueCompare {
public :

    ////    Constructors and destructors    ////
    
    // constructor
    // Argument Value value :
    // The value to find
    //## operation OMValueCompare(Value)
    explicit inline OMValueCompare(Value value) : value_(value) {
        //#[ operation OMValueCompare(Value)
        //#]
    }
    
    //## auto_generated
    ~OMValueCompare(void);
    
    ////    Operations    ////
    
    // the operator used by std::find_if() to compare the map element with the one we are searching for
    // Argument const std::pair<Key,Value>& item :
    // The map item to check against the value
    //## operation operator()(const std::pair<Key,Value>&)
    inline bool operator()(const std::pair<Key,Value>& item) {
        //#[ operation operator()(const std::pair<Key,Value>&)
        return (item.second == value_);
        //#]
    }
    
    ////    Attributes    ////
    

private :

    // The value to compare against (this is what we are looking for)
    Value value_;		//## attribute value_
    
};

//## package Design::oxf::Services::Containers::STLContainersSupport

//## class OMValueCompare
template <class Key, class Value> OMValueCompare<Key, Value>::~OMValueCompare(void) {
}

#endif



