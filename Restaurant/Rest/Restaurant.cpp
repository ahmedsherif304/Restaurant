#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}


void Restaurant::enqueueMotorCycle(Motorcycle* m){
	switch (m->getRegion()){
	case A_REG:{
		switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleA.enqueue(m);break;}
		case TYPE_VIP:{FastMotorCycleA.enqueue(m); break;}
		case TYPE_FROZ:{FrozenMotorCycleA.enqueue(m); break;}
		default:{break;}
		}
			   break;
			   } 
	case B_REG:{
			   switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleB.enqueue(m);break;}
		case TYPE_VIP:{FastMotorCycleB.enqueue(m); break;}
		case TYPE_FROZ:{FrozenMotorCycleB.enqueue(m); break;}
		default:{break;}
		
			   break;
			   }}
	case C_REG:{
			   switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleC.enqueue(m);break;}
		case TYPE_VIP:{FastMotorCycleC.enqueue(m); break;}
		case TYPE_FROZ:{FrozenMotorCycleC.enqueue(m); break;}
		default:{break;}
		
			   break;
			   }}
	case D_REG:{
			   switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleD.enqueue(m);break;}
		case TYPE_VIP:{FastMotorCycleD.enqueue(m); break;}
		case TYPE_FROZ:{FrozenMotorCycleD.enqueue(m); break;}
		default:{break;}
		
			   break;
			   }}
	
	default: {break;}
	}

}
void Restaurant::ADDOrder(Order*O)
{
	switch (O->GetRegion()){
	case A_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderA.enqueue(O,O->getPriority());break;}
			case TYPE_VIP:{VIPOrderA.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderA.enqueue(O,O->getPriority()); break;}
			default:{break;}
		}
			   break;
			   } 
	case B_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderB.enqueue(O,O->getPriority());break;}
			case TYPE_VIP:{VIPOrderB.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderB.enqueue(O,O->getPriority()); break;}
			default:{break;}
		}
			   break;
			   }
	case C_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderC.enqueue(O,O->getPriority());break;}
			case TYPE_VIP:{VIPOrderC.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderC.enqueue(O,O->getPriority()); break;}
			default:{break;}
			   break;
			   }
			   }
	case D_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderD.enqueue(O,O->getPriority());break;}
			case TYPE_VIP:{VIPOrderD.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderD.enqueue(O,O->getPriority()); break;}
			default:{break;}
			   break;
			   }
			   }
	default: {break;}
	}

}

void Restaurant::dequeueOrder(){////// DON'T FORGET

}

////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order type
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand()%4;
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg);
		AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while(DEMO_Queue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}


/// ==> end of DEMO-related function