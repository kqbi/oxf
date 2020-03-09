//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2008, 2011. All Rights Reserved.
//
//  Note to U.S. Government Users Restricted Rights:  
//  Use, duplication or disclosure restricted by GSA ADP Schedule 
//  Contract with IBM Corp.
//

#ifndef _OMSFunctionTimerFactory_H
#define _OMSFunctionTimerFactory_H

#include "omtypes.h"
#include "os.h"
#include "IOxfTickTimerFactory.h"

class OMSFunctionTimerFactory : public IOxfTickTimerFactory
{
private:
	OMOSTimer* m_pCurrentTimer;
	static OMSFunctionTimerFactory* m_pInstance;
	OMSFunctionTimerFactory(void);

public:
	~OMSFunctionTimerFactory(void);

	static OMSFunctionTimerFactory* instance(void);
	static void cleanup(void);

	OMOSTimer* getCurrentTimer() { return m_pCurrentTimer; }
	void setCurrentTimer(OMOSTimer* pTimer) { m_pCurrentTimer = pTimer; }

	//overridden from IOxfTickTimerFactory
	virtual OMOSTimer* createRealTimeTimer(OxfTimeUnit tickTime, TimerManagerCallBack callBack, void * callBackParams) const;
	virtual OMOSTimer* createSimulatedTimeTimer(TimerManagerCallBack callBack, void * callBackParams) const; 
};

#endif