//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2008, 2013. All Rights Reserved.
//
//  Note to U.S. Government Users Restricted Rights:  
//  Use, duplication or disclosure restricted by GSA ADP Schedule 
//  Contract with IBM Corp.
//

#include "OMSFunctionTimer.h"
#include "OMTimerManager.h"

OMSFunctionTimer::OMSFunctionTimer(const timeUnit tickResolution, void /* pcbkfunc */(void*), void *pparam)
{
	m_TickResolution = tickResolution;
	cbkfunc = OMTimerManager::cbkBridgeWithTime;
	param = pparam;
	m_CurrentSystemTime = 0;
	OMTimerManager::setExternalTimer(true);
}
 
OMSFunctionTimer::~OMSFunctionTimer(void)
{
	m_TickResolution = 0;
	cbkfunc = NULL;
	param = NULL;
	m_CurrentSystemTime = 0;
}

void OMSFunctionTimer::setSystemTime(timeUnit time)
{
	m_CurrentSystemTime = time;

	if(cbkfunc && param)
	{
		(*(cbkfunc))(param, m_CurrentSystemTime);
	}
}