#pragma once
#include "Event.h"
#include "..\Rest\Restaurant.h"
#include "..\Rest\Order.h"
class PromotionEvent:public Event
{
	int ExMoney;
public:
	PromotionEvent(int,int,int);
	virtual Order*  Execute(Restaurant* pRest);
	~PromotionEvent(void);
};

