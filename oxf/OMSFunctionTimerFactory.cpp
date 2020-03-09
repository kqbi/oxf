//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2008, 2011. All Rights Reserved.
//
//  Note to U.S. Government Users Restricted Rights:  
//  Use, duplication or disclosure restricted by GSA ADP Schedule 
//  Contract with IBM Corp.
//

#include "OMSFunctionTimerFactory.h"
#include "OMSFunctionTimer.h"

OMSFunctionTimerFactory* OMSFunctionTimerFactory::m_pInstance = NULL;

OMSFunctionTimerFactory::OMSFunctionTimerFactory(void)
{
	m_pCurrentTimer = NULL;
}

OMSFunctionTimerFactory::~OMSFunctionTimerFactory(void)
{
	m_pCurrentTimer = NULL;
}

OMSFunctionTimerFactory* OMSFunctionTimerFactory::instance(void)
{
	if(m_pInstance == NULL)
		m_pInstance = new OMSFunctionTimerFactory;
	return m_pInstance;
}

void OMSFunctionTimerFactory::cleanup(void)
{
	if(m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

OMOSTimer* OMSFunctionTimerFactory::createRealTimeTimer(OxfTimeUnit tickTime, TimerManagerCallBack callBack, void * callBackParams) const
{
	OMOSTimer* pTimer = new OMSFunctionTimer(tickTime, callBack, callBackParams);
	((OMSFunctionTimerFactory*)(this))->setCurrentTimer(pTimer);
	return (OMOSTimer*)(pTimer);
}

OMOSTimer* OMSFunctionTimerFactory::createSimulatedTimeTimer(TimerManagerCallBack callBack, void * callBackParams) const
{
	return NULL;
}