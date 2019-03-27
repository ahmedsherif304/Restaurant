#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent( int oID, ORD_TYPE oType, REGION reg,int dis,int ArrTime,int M):Event(ArrTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdDistance=dis;
	OrdMoney=M;
	

}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phase 1&2
	Order* pOrd = new Order(OrderID,OrdType,OrdRegion,OrdDistance,EventTime,OrdMoney);
	pRest->AddtoDemoQueue(pOrd);
}
