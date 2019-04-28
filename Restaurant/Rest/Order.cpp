#include "Order.h"
#include<iostream>
using namespace std;


Order::Order(int id, ORD_TYPE r_Type, REGION r_region,int dis,int at,int m)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	Distance=dis;
	ArrTime=at;
	totalMoney=m;
	if(type==TYPE_VIP)
	{Priority=abs(3*totalMoney-2*ArrTime-Distance);}
	else if(type==TYPE_NRM)Priority=0;
	else if(type==TYPE_FROZ)Priority=1;
}
int Order::getPriority(){//retyur it's priority
	return Priority;
}
Order::~Order()
{
}
int Order:: GetTime()
{
	return ArrTime;
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
void Order::setMoney(int m){totalMoney=m;}
int Order::getMoney(){return totalMoney;}
void Order::setTypeVIP(){
	Priority=abs(3*totalMoney-2*ArrTime-Distance);
	type=TYPE_VIP;
}
