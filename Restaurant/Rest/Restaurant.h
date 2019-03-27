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

	Queue<Motorcycle*> FastMotorCycleA;
	Queue<Motorcycle*> NormalMotorCycleA;
	Queue<Motorcycle*> FrozenMotorCycleA;
	Queue<Motorcycle*> FastMotorCycleB;
	Queue<Motorcycle*> NormalMotorCycleB;
	Queue<Motorcycle*> FrozenMotorCycleB;
	Queue<Motorcycle*> FastMotorCycleC;
	Queue<Motorcycle*> NormalMotorCycleC;
	Queue<Motorcycle*> FrozenMotorCycleC;
	Queue<Motorcycle*> FastMotorCycleD;
	Queue<Motorcycle*> NormalMotorCycleD;
	Queue<Motorcycle*> FrozenMotorCycleD;
	
	PriorityQueue<Order*> FrozenOrderA;
	PriorityQueue<Order*> VIPOrderA;
	PriorityQueue<Order*> NormalOrderA;
	PriorityQueue<Order*> FrozenOrderB;
	PriorityQueue<Order*> VIPOrderB;
	PriorityQueue<Order*> NormalOrderB;
	PriorityQueue<Order*> FrozenOrderC;
	PriorityQueue<Order*> VIPOrderC;
	PriorityQueue<Order*> NormalOrderC;
	PriorityQueue<Order*> FrozenOrderD;
	PriorityQueue<Order*> VIPOrderD;
	PriorityQueue<Order*> NormalOrderD;

	
	
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void Read_Data();
	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 


	//
	// TODO: Add More Member Functions As Needed

	void enqueueMotorCycle(Motorcycle*);//enqueue for motorcycles and orders
	void ADDOrder(Order*);

	void dequeueOrder();

	//

};

#endif