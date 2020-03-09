//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2008, 2013. All Rights Reserved.
//
//  Note to U.S. Government Users Restricted Rights:  
//  Use, duplication or disclosure restricted by GSA ADP Schedule 
//  Contract with IBM Corp.
//

#ifndef _OMSFunctionTimer_H
#define _OMSFunctionTimer_H

#include "omtypes.h"
#include "os.h"

class OMSFunctionTimer : public OMOSTimer {
private:
	timeUnit m_TickResolution;
	timeUnit m_CurrentSystemTime;
    void (*cbkfunc)(void*, timeUnit);
    void *param;
    
public:
    OMSFunctionTimer(const timeUnit tickResolution, void /*pcbkfunc*/(void*), void *pparam);  
    ~OMSFunctionTimer(void);

	void setSystemTime(timeUnit time);
	timeUnit getSystemTime(void) { return m_CurrentSystemTime; }

	//overriden functions from OMOSTimer
	virtual void* getOsHandle(void) const { return NULL; }
	virtual void setAffinity(const OMAffinity_t aff) {}
};


#endif