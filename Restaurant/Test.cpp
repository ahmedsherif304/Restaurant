//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include<iostream>
using namespace std;

//#include <vld.h> //calculating the memory leak
int main()
{
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	delete pRest;
	
	return 0;
}
