#include "PromotionEvent.h"


PromotionEvent::PromotionEvent(int ts,int id,int m):Event(ts,id)
{
	ExMoney=m;
}
Order* PromotionEvent::Execute(Restaurant* pRest){
	pRest->PromoteOrder(EventTime,OrderID,ExMoney);
	return pRest->ExecuteEvents(this->getEventTime());
}

PromotionEvent::~PromotionEvent(void)
{
}
