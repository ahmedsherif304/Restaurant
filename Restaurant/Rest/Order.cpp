#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region,int dis,int at,int m)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	Distance=dis;
	ArrTime=at;
	totalMoney=m;
	///adding priority equation
}
int Order::getPriority(){//retyur it's priority
	return Priority;
}
Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


int Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}
