#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;
#include <fstream>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancellationEvent.h"
#include "..\Events\PromotionEvent.h"
#include <string>

Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	this->Read_Data();
	Interactive();
}


void Restaurant::Read_Data()
{
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	ifstream inFile ("test 1.txt");
	if (!inFile.is_open())
	{
		pGUI->PrintMessage("File is not found");
		return;
	}
	//// read Motorcycles speed data and its count in each region
	int SN, SF, SV;
	inFile >> SN >> SF >> SV;
	inFile>> MNA >> MFA >> MVA;
	inFile>> MNB >> MFB >> MVB;
	inFile>> MNC >> MFC >> MVC;
	inFile>> MND >> MFD >> MVD;
	Motorcycle*MOt;
	for(int i=0;i<MFA;i++)
	{
		MOt=new Motorcycle(A_REG,TYPE_FROZ,i+1,SF);
		FrozenMotorCycleA.enqueue(MOt,SF);
	}
	for(int i=0;i<MNA;i++)
	{
		MOt=new Motorcycle(A_REG,TYPE_NRM,i+1,SN);
		NormalMotorCycleA.enqueue(MOt,SN);
	}
	for(int i=0;i<MVA;i++)
	{
		MOt=new Motorcycle(A_REG,TYPE_VIP,i+1,SV);
		FastMotorCycleA.enqueue(MOt,SV);
	}


	for(int i=0;i<MFB;i++)
	{
		MOt=new Motorcycle(B_REG,TYPE_FROZ,i+1,SF);
		FrozenMotorCycleB.enqueue(MOt,SF);
	}
	for(int i=0;i<MNB;i++)
	{
		MOt=new Motorcycle(B_REG,TYPE_NRM,i+1,SN);
		NormalMotorCycleB.enqueue(MOt,SN);
	}
	for(int i=0;i<MVB;i++)
	{
		MOt=new Motorcycle(B_REG,TYPE_VIP,i+1,SV);
		FastMotorCycleB.enqueue(MOt,SV);
	}


	for(int i=0;i<MFC;i++)
	{
		MOt=new Motorcycle(C_REG,TYPE_FROZ,i+1,SF);
		FrozenMotorCycleC.enqueue(MOt,SF);
	}
	for(int i=0;i<MNC;i++)
	{
		MOt=new Motorcycle(C_REG,TYPE_NRM,i+1,SN);
		NormalMotorCycleC.enqueue(MOt,SN);
	}
	for(int i=0;i<MVC;i++)
	{
		MOt=new Motorcycle(C_REG,TYPE_VIP,i+1,SV);
		FastMotorCycleC.enqueue(MOt,SV);
	}


	for(int i=0;i<MFD;i++)
	{
		MOt=new Motorcycle(D_REG,TYPE_FROZ,i+1,SF);
		FrozenMotorCycleD.enqueue(MOt,SF);
	}
	for(int i=0;i<MND;i++)
	{
		MOt=new Motorcycle(D_REG,TYPE_NRM,i+1,SN);
		NormalMotorCycleD.enqueue(MOt,SN);
	}
	for(int i=0;i<MVD;i++)
	{
		MOt=new Motorcycle(D_REG,TYPE_VIP,i+1,SV);
		FastMotorCycleD.enqueue(MOt,SV);
	}
	
	int prom;
	inFile >> prom;
	Prom=prom;
	inFile>> EventCnt;
	int TS,ID,DST,MON;
	char R,REG,TYP;	
	// lazm assign el speed w 3dd el motorcycle abl ay 7aga
	Event *E;
	//// initialize them to NULL
	//ea = eb = ec = ed = NULL;
	//oa = ob = oc = od = NULL;
	for(int i=0;i<EventCnt;i++)
	{ 
	inFile >> R;//new Event 3alashan tslem el order information w hnak han3mel new order w mts2lsh 3n el region hna eb3at el region 3ala tool
	if(R == 'R')
	{
		inFile>>TS >> TYP >> ID >> DST >> MON >>REG ;
		if (TYP == 'N')
		{
			E=new ArrivalEvent(ID,TYPE_NRM,int(REG)-65,DST,TS,MON);
			AddEvent(E);
		}
		else if(TYP == 'F')
			{
			E=new ArrivalEvent(ID,TYPE_FROZ,int(REG)-65,DST,TS,MON);
			AddEvent(E);
			}
		else if(TYP == 'V')
				{
			E=new ArrivalEvent(ID,TYPE_VIP,int(REG)-65,DST,TS,MON);
			AddEvent(E);
				}
	}
	else if(R == 'X')
		{
			inFile>> TS >> ID;
			E=new CancellationEvent(ID,TS);
			AddEvent(E);

		}
	else
		{
			inFile>> TS >> ID >> MON;
			E=new PromotionEvent(TS,ID,MON);
			AddEvent(E);
		}

}
	inFile.close();
}
//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
Order* Restaurant::ExecuteEvents(int CurrentTimeStep)
{Order*OP;
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return NULL;
		if(pE->getEventTime()==CurrentTimeStep)
		{ 
		EventsQueue.dequeue(pE);	//remove event from the queue
		OP= pE->Execute(this);
		delete pE;
		return OP;
		}		//deallocate event object from memory
	}
	return NULL;
}


Restaurant::~Restaurant()
{

	FastMotorCycleA.clear();
	FastMotorCycleB.clear();
	FastMotorCycleC.clear();
	FastMotorCycleD.clear();
	FrozenMotorCycleA.clear();
	FrozenMotorCycleB.clear();
	FrozenMotorCycleC.clear();
	FrozenMotorCycleD.clear();
	NormalMotorCycleA.clear();
	NormalMotorCycleB.clear();
	NormalMotorCycleC.clear();
	NormalMotorCycleD.clear();
	delete pGUI;
}


void Restaurant::enqueueMotorCycle(Motorcycle* m){
	switch (m->getRegion()){
	case A_REG:{
		switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleA.enqueue(m,m->getSpeed());break;}
		case TYPE_VIP:{FastMotorCycleA.enqueue(m,m->getSpeed()); break;}
		case TYPE_FROZ:{FrozenMotorCycleA.enqueue(m,m->getSpeed()); break;}
		default:{break;}
		}
			   break;
			   } 
	case B_REG:{
			   switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleB.enqueue(m,m->getSpeed());break;}
		case TYPE_VIP:{FastMotorCycleB.enqueue(m,m->getSpeed()); break;}
		case TYPE_FROZ:{FrozenMotorCycleB.enqueue(m,m->getSpeed()); break;}
		default:{break;}
		
			   break;
			   }
			   }
	case C_REG:{
			   switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleC.enqueue(m,m->getSpeed());break;}
		case TYPE_VIP:{FastMotorCycleC.enqueue(m,m->getSpeed()); break;}
		case TYPE_FROZ:{FrozenMotorCycleC.enqueue(m,m->getSpeed()); break;}
		default:{break;}
		
			   break;
			   }
			   }
	case D_REG:{
			   switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleD.enqueue(m,m->getSpeed());break;}
		case TYPE_VIP:{FastMotorCycleD.enqueue(m,m->getSpeed()); break;}
		case TYPE_FROZ:{FrozenMotorCycleD.enqueue(m,m->getSpeed()); break;}
		default:{break;}
		
			   break;
			   }
			   }
	default: {break;}
	}

}
void Restaurant::PromoteOrder(int ts,int id,int m){
	//Write Promotion Code
	Order* order=ReturnOrder(id);
	if (order!=NULL){
		pGUI->RemoveOrder(order);
		pGUI->UpdateInterface();
		if(!Orders.isEmpty())
			CancelFromOrders(id);
		else if(!InActive.isEmpty())
			CancelFromInActive(id);
	}
	Order*pOrd;
	if (order!=NULL)
		{
		order->setMoney(order->getMoney()+m);
		order->setTypeVIP();
		ADDOrder(order);
		if(!Orders.isEmpty())
			Orders.enqueue(order,order->getPriority());
		else if(!InActive.isEmpty())
			InActive.enqueue(order,order->getPriority());
	}
	if(Orders.isEmpty())
		return;
	Queue<Order*>Q;
	pGUI->ResetDrawingList();
	while(!Orders.isEmpty())
	{
		Orders.dequeue(pOrd);
		pGUI->AddOrderForDrawing(pOrd);
		Q.enqueue(pOrd);
	}
		pGUI->UpdateInterface();
	while(!Q.isEmpty())
	{
		Q.dequeue(pOrd);
		Orders.enqueue(pOrd,pOrd->getPriority());
	}

}
void Restaurant::AutoPromote(int CurrentTimeStep){
	Order* pOrd;
	NormalOrderA.peekFront(pOrd);
	while  (pOrd!=NULL)
	{
		if ((pOrd->GetTime()+Prom)==CurrentTimeStep)
			{PromoteOrder(pOrd->GetTime(),pOrd->GetID(),100);
		NormalOrderA.peekFront(pOrd);}
		else break;
	}

	NormalOrderB.peekFront(pOrd);
	while (pOrd!=NULL && (pOrd->GetTime()+Prom)==CurrentTimeStep)
		{
		PromoteOrder(pOrd->GetTime(),pOrd->GetID(),0);
		NormalOrderB.peekFront(pOrd);
	}

	NormalOrderC.peekFront(pOrd);
	while (pOrd!=NULL && pOrd->GetTime()+Prom==CurrentTimeStep)
		{
		PromoteOrder(pOrd->GetTime(),pOrd->GetID(),0);
		NormalOrderC.peekFront(pOrd);
	}

	NormalOrderD.peekFront(pOrd);
	while (pOrd!=NULL && pOrd->GetTime()+Prom==CurrentTimeStep)
		{
		PromoteOrder(pOrd->GetTime(),pOrd->GetID(),0);
		NormalOrderD.peekFront(pOrd);
	}

}

Order* Restaurant:: ReturnOrder(int id){
	Order*p=NULL,*temp=NULL,*temp1=NULL,*pOrd=NULL;
	bool flag=0;
	if (!NormalOrderA.isEmpty()){
	NormalOrderA.dequeue(temp);
	if(temp->GetID()==id)
	{
	
	return temp;
	}
	NormalOrderA.enqueue(temp);
	NormalOrderA.peekFront(p);
	while (temp!=p)
		{

			NormalOrderA.dequeue(temp1);
			if(temp1->GetID()==id)
			{
				flag=1;

			}
			else
				NormalOrderA.enqueue(temp1);
			NormalOrderA.peekFront(p);
		}
	if (flag)
		return temp1;}

	if (!NormalOrderB.isEmpty()){
	NormalOrderB.dequeue(temp);
	if(temp->GetID()==id)
	{
	return temp;
	}


	NormalOrderB.enqueue(temp);
	NormalOrderB.peekFront(p);
	while (temp!=p)
		{

			NormalOrderB.dequeue(temp1);
			if(temp1->GetID()==id)
			{
				flag=1;
				
			}
			else
				NormalOrderB.enqueue(temp1);
			NormalOrderB.peekFront(p);
		}
	if (flag)
		return temp1;
	}

	
	if (!NormalOrderC.isEmpty()){
	NormalOrderC.dequeue(temp);
	if(temp->GetID()==id)
	{
	
	return temp;
	}
	NormalOrderC.enqueue(temp);
	NormalOrderC.peekFront(p);
	while (temp!=p)
		{

			NormalOrderC.dequeue(temp1);
			if(temp1->GetID()==id)
			{
				flag=1;
				
			}
			else
				NormalOrderC.enqueue(temp1);
			NormalOrderC.peekFront(p);
		}
	if (flag)
		return temp1;
	
	}

	if (!NormalOrderD.isEmpty()){
	NormalOrderD.dequeue(temp);
	if(temp->GetID()==id)
	{
	
		return temp;
	}


	NormalOrderD.enqueue(temp);
	NormalOrderD.peekFront(p);
	while (temp!=p)
		{

			NormalOrderD.dequeue(temp1);
			if(temp1->GetID()==id)
			{
				flag=1;
				
			}
			else
			NormalOrderD.enqueue(temp1);
			NormalOrderD.peekFront(p);
		}
	if (flag)
		return temp1;
	
	}
	return NULL;


}
Order* Restaurant::CancelOrder(int id,int ts)
{
	Order* temp=ReturnOrder(id);
	if (temp!=NULL){
		pGUI->RemoveOrder(temp);
		CancelFromInActive(id);
		pGUI->UpdateInterface();
		return temp;
	}
	return NULL;
}
void Restaurant::CancelFromOrders(int id)
{
	Order*New,*pOrd;
	Queue<Order*>Temp;
	while(!Orders.isEmpty())
	{
		Orders.peekFront(New);
	if(New->GetID()==id)
	{
		Orders.dequeue(New);  
	}
	else 
	{
		Orders.dequeue(New);
		Temp.enqueue(New);
	}
	}
	while(!Temp.isEmpty())
	{
		Temp.dequeue(New);
		Orders.enqueue(New,New->getPriority());
	}
}

void Restaurant::CancelFromInActive(int id)
{
	Order*New,*pOrd;
	Queue<Order*>Temp;
	while(!InActive.isEmpty())
	{
		InActive.peekFront(New);
	if(New->GetID()==id)
	{
		InActive.dequeue(New);  
	}
	else 
	{
		InActive.dequeue(New);
		Temp.enqueue(New);
	}
	}
	while(!Temp.isEmpty())
	{
		Temp.dequeue(New);
		InActive.enqueue(New,New->getPriority());
	}
}
void Restaurant::ADDOrder(Order*O)
{
	switch (O->GetRegion()){
	case A_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderA.enqueue(O);
				break;}
			case TYPE_VIP:{VIPOrderA.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderA.enqueue(O); break;}
			default:{break;}
		}
			   break;
			   } 
	case B_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderB.enqueue(O);break;}
			case TYPE_VIP:{VIPOrderB.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderB.enqueue(O); break;}
			default:{break;}
		}
			   break;
			   }
	case C_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderC.enqueue(O);break;}
			case TYPE_VIP:{VIPOrderC.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderC.enqueue(O); break;}
			default:{break;}
		}
			   break;
			   }
	case D_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderD.enqueue(O);break;}
			case TYPE_VIP:{VIPOrderD.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderD.enqueue(O); break;}
			default:{break;}
		}
			   break;
			   }
	default: {break;}
	}

}

bool Restaurant::dequeueOrder(int time,Order*&order)
{

	if(VIPOrderA.peekFront(order))
		if(order->GetTime()==time)
		{
			VIPOrderA.dequeue(order);
			return true;
		}
	if(VIPOrderB.peekFront(order))
		if(order->GetTime()==time)
		{
			VIPOrderB.dequeue(order);
			return true;
		}
	if(VIPOrderC.peekFront(order))
		if(order->GetTime()==time)
		{
			VIPOrderC.dequeue(order);
			return true;
		}
	if(VIPOrderD.peekFront(order))
		if(order->GetTime()==time)
		{
			VIPOrderD.dequeue(order);
			return true;
		}


	if(FrozenOrderA.peekFront(order))
		if(order->GetTime()==time)
		{
			FrozenOrderA.dequeue(order);
			return true;
		}
	if(FrozenOrderB.peekFront(order))
		if(order->GetTime()==time)
		{
			FrozenOrderB.dequeue(order);
			return true;
		}
	if(FrozenOrderC.peekFront(order))
		if(order->GetTime()==time)
		{
			FrozenOrderC.dequeue(order);
			return true;
		}
	if(FrozenOrderD.peekFront(order))
		if(order->GetTime()==time)
		{
			FrozenOrderD.dequeue(order);
			return true;
		}
	if(NormalOrderA.peekFront(order))
		if(order->GetTime()==time)
		{
			NormalOrderA.dequeue(order);
			return true;
		}
	if(NormalOrderB.peekFront(order))
		{if(order->GetTime()==time)
		{
			NormalOrderB.dequeue(order);
			return true;
		}
	}
	if(NormalOrderC.peekFront(order))
		if(order->GetTime()==time)
		{
			NormalOrderC.dequeue(order);
			return true;
		}
	if(NormalOrderD.peekFront(order))
		if(order->GetTime()==time)
		{
			NormalOrderD.dequeue(order);
			return true;
		}
	return false;
}

void Restaurant:: Print(int T){//printing the messages

	string s="Time="+ to_string(T)+"   Region A :  ";

	s+=" "+to_string(VIPOrderA.GetCount());

	s+=" "+to_string(FrozenOrderA.GetCount());	
	s+=" "+to_string(NormalOrderA.GetCount());
	s+=" "+to_string(FastMotorCycleA.GetCount());
	s+=" "+to_string(FrozenMotorCycleA.GetCount());
	s+=" "+to_string(NormalMotorCycleA.GetCount());
	s+="    Region B :  ";


	s+=" "+to_string(VIPOrderB.GetCount());	
	s+=" "+to_string(FrozenOrderB.GetCount());
	s+=" "+to_string(NormalOrderB.GetCount());
	s+=" "+to_string(FastMotorCycleB.GetCount());
	s+=" "+to_string(FrozenMotorCycleB.GetCount());
	s+=" "+to_string(NormalMotorCycleB.GetCount());

		s+="    Region C :  ";

	s+=" "+to_string(VIPOrderC.GetCount());
	s+=" "+to_string(FrozenOrderC.GetCount());
	s+=" "+to_string(NormalOrderC.GetCount());
	s+=" "+to_string(FastMotorCycleC.GetCount());
	s+=" "+to_string(FrozenMotorCycleC.GetCount());
	s+=" "+to_string(NormalMotorCycleC.GetCount());

			s+="    Region D :  ";

	s+=" "+to_string(VIPOrderD.GetCount());
	s+=" "+to_string(FrozenOrderD.GetCount());
	s+=" "+to_string(NormalOrderD.GetCount());
	s+=" "+to_string(FastMotorCycleD.GetCount());
	s+=" "+to_string(FrozenMotorCycleD.GetCount());
	s+=" "+to_string(NormalMotorCycleD.GetCount());
	
	
		pGUI->PrintMessage(s);



}
void Restaurant::assign(int TimeStep){//like assigning to motorcycle but every time step
	
	
	//Region A
	Order*pOrd;
	Motorcycle*Mot;
	if(!VIPOrderA.isEmpty()&&(!FastMotorCycleA.isEmpty()||!NormalMotorCycleA.isEmpty()||!FrozenMotorCycleA.isEmpty()))
	{
		VIPOrderA.dequeue(pOrd);
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
		if(!FastMotorCycleA.isEmpty())
		{
			FastMotorCycleA.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if(!NormalMotorCycleA.isEmpty())
		{
			NormalMotorCycleA.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if (!FrozenMotorCycleA.isEmpty()){
			FrozenMotorCycleA.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	else  if(!FrozenOrderA.isEmpty() && !FrozenMotorCycleA.isEmpty())
	{
		
		FrozenOrderA.dequeue(pOrd);
		FrozenMotorCycleA.dequeue(Mot);
		Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
		OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	else if(!NormalOrderA.isEmpty()&& (!NormalMotorCycleA.isEmpty()||!FastMotorCycleA.isEmpty()))
	{
		NormalOrderA.dequeue(pOrd);
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
		if(!NormalMotorCycleA.isEmpty())
		{
			NormalMotorCycleA.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if(!FastMotorCycleA.isEmpty())
		{
			FastMotorCycleA.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}

	//Region B
	if(!VIPOrderB.isEmpty()&&(!FastMotorCycleB.isEmpty()||!NormalMotorCycleB.isEmpty()||!FrozenMotorCycleB.isEmpty()))
	{
		VIPOrderB.dequeue(pOrd);
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
		if(!FastMotorCycleB.isEmpty())
		{
			FastMotorCycleB.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if(!NormalMotorCycleB.isEmpty())
		{
			NormalMotorCycleB.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if (!FrozenMotorCycleB.isEmpty()){
			FrozenMotorCycleB.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	else  if(!FrozenOrderB.isEmpty() && !FrozenMotorCycleB.isEmpty())
	{

			FrozenOrderB.dequeue(pOrd);
			pGUI->RemoveOrder(pOrd);
			CancelFromOrders(pOrd->GetID());
			FrozenMotorCycleB.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
			pOrd->setWaitTime(TimeStep - pOrd->GetTime());
			pOrd->setServTime(Mot->getReturnTime()/2);
			SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	else if(!NormalOrderB.isEmpty()&& (!NormalMotorCycleB.isEmpty()||!FastMotorCycleB.isEmpty()))
	{
		NormalOrderB.dequeue(pOrd);
		pGUI->RemoveOrder(pOrd);
		CancelFromOrders(pOrd->GetID());
		if(!NormalMotorCycleB.isEmpty())
		{
			NormalMotorCycleB.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if(!FastMotorCycleB.isEmpty())
		{
			FastMotorCycleB.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	//Region C
	if(!VIPOrderC.isEmpty()&&(!FastMotorCycleC.isEmpty()||!NormalMotorCycleC.isEmpty()||!FrozenMotorCycleC.isEmpty()))
	{
		VIPOrderC.dequeue(pOrd);
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
		if(!FastMotorCycleC.isEmpty())
		{
			FastMotorCycleC.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if(!NormalMotorCycleC.isEmpty())
		{
			NormalMotorCycleC.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if (!FrozenMotorCycleC.isEmpty()){
			FrozenMotorCycleC.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	else  if(!FrozenOrderC.isEmpty() && !FrozenMotorCycleC.isEmpty())
	{
		FrozenOrderC.dequeue(pOrd);
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
			FrozenMotorCycleC.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	else if(!NormalOrderC.isEmpty()&& (!NormalMotorCycleC.isEmpty()||!FastMotorCycleC.isEmpty()))
	{
		NormalOrderC.dequeue(pOrd);
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
		if(!NormalMotorCycleC.isEmpty())
		{
			NormalMotorCycleC.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if(!FastMotorCycleC.isEmpty())
		{
			FastMotorCycleC.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	//Regioon D
	if(!VIPOrderD.isEmpty()&&(!FastMotorCycleD.isEmpty()||!NormalMotorCycleD.isEmpty()||!FrozenMotorCycleD.isEmpty()))
	{
		VIPOrderD.dequeue(pOrd);
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
		if(!FastMotorCycleD.isEmpty())
		{
			FastMotorCycleD.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if(!NormalMotorCycleD.isEmpty())
		{
			NormalMotorCycleD.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if (!FrozenMotorCycleD.isEmpty()){
			FrozenMotorCycleD.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	else  if(!FrozenOrderD.isEmpty() && !FrozenMotorCycleD.isEmpty())
	{
		FrozenOrderD.dequeue(pOrd);
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
		FrozenMotorCycleD.dequeue(Mot);
		Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
		OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
	else if(!NormalOrderD.isEmpty()&& (!NormalMotorCycleD.isEmpty()||!FastMotorCycleD.isEmpty()))
	{
		NormalOrderD.dequeue(pOrd);
		CancelFromOrders(pOrd->GetID());
		pGUI->RemoveOrder(pOrd);
		if(!NormalMotorCycleD.isEmpty())
		{
			NormalMotorCycleD.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		else if(!FastMotorCycleD.isEmpty())
		{
			FastMotorCycleD.dequeue(Mot);
			Mot->setReturnTime(TimeStep+2*pOrd->GetDistance()/Mot->getSpeed());
			OutMotorCycles.enqueue(Mot,-Mot->getReturnTime());
		}
		pOrd->setWaitTime(TimeStep - pOrd->GetTime());
		pOrd->setServTime(Mot->getReturnTime()/2);
		SaveFile.enqueue(pOrd,-(pOrd->GetTime()+pOrd->getServTime()+pOrd->getWaitTime()));
	}
}
void Restaurant::returnMotorCycle(int TimeStep){
	Motorcycle* Mot;
	while (OutMotorCycles.peekFront(Mot))
	{
		if (Mot->getReturnTime()==TimeStep)
		{
			OutMotorCycles.dequeue(Mot);
			enqueueMotorCycle(Mot);
		}
		else break;
	}

}

void Restaurant::Interactive()
{
	
	bool test;
	Order*pOrd;
	int CurrentTimeStep = 1;
	PROG_MODE Mode =pGUI->getGUIMode();
	//as long as events queue is not empty yet
	while( !EventsQueue.isEmpty()  || !VIPOrderA.isEmpty() || !VIPOrderB.isEmpty() || !VIPOrderC.isEmpty() || !VIPOrderD.isEmpty() ||
		   !FrozenOrderA.isEmpty() ||!FrozenOrderB.isEmpty() ||!FrozenOrderC.isEmpty() ||!FrozenOrderD.isEmpty() ||
		   !NormalOrderA.isEmpty() ||!NormalOrderB.isEmpty() ||!NormalOrderC.isEmpty() ||!NormalOrderD.isEmpty() || 
		   !OutMotorCycles.isEmpty()
		   )
	{
		Print(CurrentTimeStep);
		//ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		pOrd=ExecuteEvents(CurrentTimeStep);
		while(pOrd)
		{
			Print(CurrentTimeStep);
			InActive.enqueue(pOrd,pOrd->getPriority());
			pOrd=ExecuteEvents(CurrentTimeStep);
		}
		pGUI->ResetDrawingList();
		pGUI->UpdateInterface();
		while(!InActive.isEmpty())
		{
			InActive.dequeue(pOrd);
			Orders.enqueue(pOrd,pOrd->getPriority());
			pGUI->AddOrderForDrawing(pOrd);
		}
		pGUI->UpdateInterface();
		//Region A
		while((!FastMotorCycleA.isEmpty() || !NormalMotorCycleA.isEmpty() || !FrozenMotorCycleA.isEmpty())&& !VIPOrderA.isEmpty() &&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}

		while((!FrozenMotorCycleA.isEmpty()&&!FrozenOrderA.isEmpty())&&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}
		while(((!NormalMotorCycleA.isEmpty() || !FastMotorCycleA.isEmpty())&&!NormalOrderA.isEmpty())&&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}
		


		//Region B
		while((!FastMotorCycleB.isEmpty() || !NormalMotorCycleB.isEmpty() || !FrozenMotorCycleB.isEmpty())&& !VIPOrderB.isEmpty() &&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}

		while((!FrozenMotorCycleB.isEmpty()&&!FrozenOrderB.isEmpty())&&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}
		while(((!NormalMotorCycleB.isEmpty() || !FastMotorCycleB.isEmpty())&&!NormalOrderB.isEmpty())&&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}
		
		//Region C
		while((!FastMotorCycleC.isEmpty() || !NormalMotorCycleC.isEmpty() || !FrozenMotorCycleC.isEmpty())&& !VIPOrderC.isEmpty() &&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}

		while((!FrozenMotorCycleC.isEmpty()&&!FrozenOrderC.isEmpty())&&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}
		while(((!NormalMotorCycleC.isEmpty() || !FastMotorCycleC.isEmpty())&&!NormalOrderC.isEmpty())&&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}
		

		//Region D
		while((!FastMotorCycleD.isEmpty() || !NormalMotorCycleD.isEmpty() || !FrozenMotorCycleD.isEmpty())&& !VIPOrderD.isEmpty() &&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}

		while((!FrozenMotorCycleD.isEmpty()&&!FrozenOrderD.isEmpty())&&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}
		while(((!NormalMotorCycleD.isEmpty() || !FastMotorCycleD.isEmpty())&&!NormalOrderD.isEmpty())&&!Orders.isEmpty())
		{
			assign(CurrentTimeStep);
		}
		

		AutoPromote(CurrentTimeStep);
		while(!Orders.isEmpty())
		{
			Orders.dequeue(pOrd);
			InActive.enqueue(pOrd,pOrd->getPriority());	
		}
		
		if(Mode==MODE_INTR)
			pGUI->waitForClick();
		else if(Mode==MODE_STEP)
			Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	
		returnMotorCycle(CurrentTimeStep);
		pGUI->UpdateInterface();
		}
		Output_File();
		if (Mode!=MODE_SLNT)
		{
			Print(CurrentTimeStep);
			Sleep(5000);
			pGUI->PrintMessage("Done");
			if(Mode==MODE_INTR)
					pGUI->waitForClick();
			else if(Mode==MODE_STEP)
					Sleep(1000);
		}
}
void Restaurant::Output_File(){
	ofstream output;
	Order * O;
	int FT;
	int AN=0,AF=0,AV=0,BN=0,BF=0,BV=0,CN=0,CF=0,CV=0,DN=0,DF=0,DV=0;
	float SWA=0,SWB=0,SWC=0,SWD=0,SSA=0,SSB=0,SSC=0,SSD=0;
	output.open("OUTPUT.txt");
	output<<"FT  ID  AT  WT  ST\n";
	while (!SaveFile.isEmpty())
	{
		SaveFile.dequeue(O);
		FT=O->getServTime()+O->GetTime()+O->getWaitTime();
		output<<FT<<"   "<<O->GetID()<<"   "<<O->GetTime()<<"   "<<O->getWaitTime()<<"   "<<O->getServTime()<<endl;



		switch (O->GetRegion()){
	case A_REG:{
		SWA+=O->getWaitTime();
		SSA+=O->getServTime();
		switch (O->GetType()){
			case TYPE_NRM:{AN++; break;}
			case TYPE_VIP:{AV++; break;}
			case TYPE_FROZ:{AF++; break;}
			default:{break;}
		}
			   break;
			   } 
	case B_REG:{
		SWB+=O->getWaitTime();
		SSB+=O->getServTime();
		switch (O->GetType()){
			case TYPE_NRM:{BN++;break;}
			case TYPE_VIP:{BV++; break;}
			case TYPE_FROZ:{BF++; break;}
			default:{break;}
			}
			   break;
			   }
	case C_REG:{
		SWC+=O->getWaitTime();
		SSC+=O->getServTime();
		switch (O->GetType()){
			case TYPE_NRM:{CN++;break;}
			case TYPE_VIP:{CV++; break;}
			case TYPE_FROZ:{CF++; break;}
			default:{break;}
		}
			   break;
			   }
	case D_REG:{
		SWD+=O->getWaitTime();
		SSD+=O->getServTime();
		switch (O->GetType()){
			case TYPE_NRM:{DN++;break;}
			case TYPE_VIP:{DV++; break;}
			case TYPE_FROZ:{DF++; break;}
			default:{break;}
		}
			   break;
			   }
	default: {break;}
	}





	}
	float num=15.6;
	//Region A
	output<<"Region A:\n	Orders: "<<AN+AF+AV<<" [Norm:"<<AN<<", Froz:"<<AF<<", VIP:"<<AV<<"]\n";
	output<<"	MotorC: "<<MNA+MFA+MVA<<"  [Norm:"<<MNA<<", Froz:"<<MFA<<", VIP:"<<MVA<<"]\n";
	output<<"	AVG Wait = "<<SWA/(AN+AF+AV)<<", AVG Serve = "<<SSA/(AN+AF+AV)<<endl<<endl;

	//Region B
	output<<"Region B:\n	Orders: "<<BN+BF+BV<<" [Norm:"<<BN<<", Froz:"<<BF<<", VIP:"<<BV<<"]\n";
	output<<"	MotorC: "<<MNB+MFB+MVB<<"  [Norm:"<<MNB<<", Froz:"<<MFB<<", VIP:"<<MVB<<"]\n";
	output<<"	AVG Wait = "<<SWB/(BN+BF+BV)<<", AVG Serve = "<<SSB/(BN+BF+BV)<<endl<<endl;

	//Region C
	output<<"Region C:\n	Orders: "<<CN+CF+CV<<" [Norm:"<<CN<<", Froz:"<<CF<<", VIP:"<<CV<<"]\n";
	output<<"	MotorC: "<<MNC+MFC+MVC<<"  [Norm:"<<MNC<<", Froz:"<<MFC<<", VIP:"<<MVC<<"]\n";
	output<<"	AVG Wait = "<<SWC/(CN+CF+CV)<<", AVG Serve = "<<SSC/(CN+CF+CV)<<endl<<endl;

	//Region D
	output<<"Region D:\n	Orders: "<<DN+DF+DV<<" [Norm:"<<DN<<", Froz:"<<DF<<", VIP:"<<DV<<"]\n";
	output<<"	MotorC: "<<MND+MFD+MVD<<"  [Norm:"<<MND<<", Froz:"<<MFD<<", VIP:"<<MVD<<"]\n";
	output<<"	AVG Wait = "<<SWD/(DN+DF+DV)<<", AVG Serve = "<<SSD/(DN+DF+DV)<<endl<<endl;

	output.close();
}

