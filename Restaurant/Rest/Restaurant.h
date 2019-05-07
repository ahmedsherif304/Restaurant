#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include"Motorcycle.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Generic_DS\List.h"
#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	PriorityQueue<Order*>InActive;
	PriorityQueue<Motorcycle*> FastMotorCycleA;
	PriorityQueue<Motorcycle*> NormalMotorCycleA;
	PriorityQueue<Motorcycle*> FrozenMotorCycleA;
	PriorityQueue<Motorcycle*> FastMotorCycleB;
	PriorityQueue<Motorcycle*> NormalMotorCycleB;
	PriorityQueue<Motorcycle*> FrozenMotorCycleB;
	PriorityQueue<Motorcycle*> FastMotorCycleC;
	PriorityQueue<Motorcycle*> NormalMotorCycleC;
	PriorityQueue<Motorcycle*> FrozenMotorCycleC;
	PriorityQueue<Motorcycle*> FastMotorCycleD;
	PriorityQueue<Motorcycle*>     NormalMotorCycleD;
	PriorityQueue<Motorcycle*>    FrozenMotorCycleD;
	
	Queue<Order*>         FrozenOrderA;
PriorityQueue<Order*>    VIPOrderA;
	Queue<Order*>			NormalOrderA;
	Queue<Order*>			FrozenOrderB;
	PriorityQueue<Order*>   VIPOrderB;
	Queue<Order*>			NormalOrderB;
	Queue<Order*>			FrozenOrderC;
	PriorityQueue<Order*>   VIPOrderC;
	Queue<Order*>			NormalOrderC;
	Queue<Order*>			FrozenOrderD;
	PriorityQueue<Order*>   VIPOrderD;
	Queue<Order*>          NormalOrderD;
	PriorityQueue<Motorcycle*> OutMotorCycles;
	PriorityQueue<Order*>Orders;
	PriorityQueue<Order*> SaveFile;
	int Prom;

	int MNA,MFA,MVA,MNB,MFB,MVB,MNC,MFC,MVC,MND,MFD,MVD;
public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	Order* ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void Read_Data();
	void Output_File();
	Order* CancelOrder(int ,int);
	void PromoteOrder(int,int,int);
	void AutoPromote(int);
	void Print(int);
	void Interactive();
	void enqueueMotorCycle(Motorcycle*);//enqueue for motorcycles and orders
	void returnMotorCycle(int);
	void ADDOrder(Order*);
	bool dequeueOrder(int,Order*&);
	void CancelFromInActive(int id);
	void assign(int);
	void deleteMotorC();
	void CancelFromOrders(int id);
	Order* ReturnOrder(int i);
};

#endif