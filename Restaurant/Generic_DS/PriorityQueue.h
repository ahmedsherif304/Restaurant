#pragma once
//PriorityQueue LinkedList Implementation same as in Queue bu has a diff in Enqueue due to priority
#include "Node.h"

template <typename T>
class PriorityQueue
{
private :
	
	Node<T>* backPtr;
	Node<T>* frontPtr;
	//Priority is the diff between PriorityQueue and Queue will find it in Node.h 
public :
	PriorityQueue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry,int Priority);
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;	
	~PriorityQueue();
};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{frontptr=nullptr;
backptr=nullptr;
}
template <typename T>
bool PriorityQueue<T>::isEmpty()const
{    if(frontPtr==nullptr) 
                return true;
     else
               return false;
}
template <typename T>
bool PriorityQueue<T>::enqueue(const T&newEntry,int Priority)
{Node<T>New=new Node;
New->setItem(newEntry);
New->SetPriority(Priority);
if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
else if(Priority>frontPtr->getPriority())//if true this should be inserted in the beginning of the Queue
{New->setNext(frontPtr);
frontPtr=New;
}
else//to insert in its place according to priority
{
	Node<T>SCN=frontPtr;
while(SCN->getPriority()>Priority)
{if(SCN->getNext()==nullptr)break;
SCN=SCN->getNext()
}
New->setNext(SCN->getNext());
SCN->getNext(New);
}
}
template <typename T>
bool PriorityQueue<T>::dequeue(T&frntEntry)
{if(isEmpty())return false;
else{
	Node<T>*Temp=frontPtr;
	frontPtr=frontPtr->getNext();
	if(Temp==backPtr)backPtr=nullptr;
	delete temp;
	temp=nullptr;
	frntEntry=Temp->getItem();
	return true;
}
}
template <typename T>
bool PriorityQueue<T>::peekFront(T&frontEntry)const
{if(isEmpty())return false;
else
{frontEntry=frontPtr->getItem();
return true;
}
}
template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
}