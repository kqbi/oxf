//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMNullValue
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


#ifndef OMNullValue_H
#define OMNullValue_H

//## auto_generated
#include "OXFTypeSafeContainers.h"
//## dependency BasicTypes
#include "rawtypes.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMNullValue
// Empty value class - used by containers to return non-existing element
template <class Concept> class OMNullValue {
    ////    Operations    ////
    
public :

    // Get the empty value
    //## operation get()
    inline static Concept & get(void) {
        //#[ operation get()
        #ifdef OMUseNullBlockContainer
        	// ensure that the OMContainersNullBlock is initialized
        	initNullBlock();
        	// get the NULL value
        	Concept& con = (Concept&)(*OMContainersNullBlock);
        	return con;
        #else
        	static Rhp_int32_t nullSet = 0;
        	static omMemoryAlignedType nillValue[OM_ALIGNED_SIZEOF(Concept)];
        	if (nullSet == 0) {
        		// need to zero the array 
        		nullSet = 1; 
        		for (Rhp_uint32_t i = 0U; i < (OM_ALIGNED_SIZEOF(Concept)); ++i) {
        			nillValue[i] = 0;
        		}
        	}
        	return ((Concept&)(*nillValue));
        #endif
        //#]
    }
    
    // Ensure that the OMContainersNullBlock is initialized
    //## operation initNullBlock()
    //#[ ignore
    #ifdef OMUseNullBlockContainer
    //#]
    inline static void initNullBlock(void) {
        //#[ operation initNullBlock()
        if (OMContainersNullBlock[0] != 0) {
        	OMContainersNullBlock[0] = 0;
        	OMContainersNullBlock[1] = 0;
        	OMContainersNullBlock[2] = 0;
        	OMContainersNullBlock[3] = 0;
        }
        //#]
    }
    //#[ ignore
    #endif // OMUseNullBlockContainer
    //#]
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMNullValue

#endif



