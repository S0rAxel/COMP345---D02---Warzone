#include <iostream>
#include "LoggingObserver.h"
#include "Orders.h"



using namespace std;

int main() 
{
	cout << "\n\t - WARZONE PROJECT - \n";

	LogObserver* logObs = new LogObserver();
	OrdersList* orderList = new OrdersList();

	orderList->Attach(logObs);

	//cout << orderList->StringToLog();

	orderList->add(Order());

	/*/cout << "\n\t- MAP DEMO -\n";
	system("pause");
	MapDriverDemo();

	cout << "\n\t- PLAYER DEMO -\n";
	system("pause");
	PlayerDriverDemo();

	cout << "\n\t- ORDER DEMO -\n";
	system("pause");
	OrderDriverDemo();

	cout << "\n\t- CARD DEMO -\n";
	system("pause");
	CardsDriverDemo();

	cout << "\n\t- GAME ENGINE DEMO -\n";
	system("pause");
	GameEngineDriverDemo();*/
}