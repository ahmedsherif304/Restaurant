#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, WaitTime;	//arrival, service start, and finish times
	
	int Priority;
	int AutoProm;
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order(int ID, ORD_TYPE r_Type, REGION r_region,int dis,int at,int m);
	virtual ~Order();

	int GetID();
	int getPriority();
	int GetType() const;
	void setTypeVIP();
	REGION GetRegion() const;
	int GetTime();
	void setMoney(int);
	int getMoney();
	void SetDistance(int d);
	int GetDistance() const;
	void setServTime(int);
	void setWaitTime(int);
	int getServTime();
	int getWaitTime();
	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif