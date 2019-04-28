#include "CancellationEvent.h"

CancellationEvent::CancellationEvent(int id,int ts):Event(ts,id)
{
}
Order* CancellationEvent::Execute(Restaurant *pRest)
{
	pRest->CancelOrder(this->getOrderID(),this->getEventTime());
	return pRest->ExecuteEvents(this->getEventTime());
}

CancellationEvent::~CancellationEvent(void)
{
}
