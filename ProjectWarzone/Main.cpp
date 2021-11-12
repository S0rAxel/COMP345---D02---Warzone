#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>
#include "LoggingObserver.h"
#include "Orders.h"
#include "CommandProcessingDriver.h"
#include "OrderExecutionDriver.h"
#include "CommandProcessing.h"


using namespace std;

int main() 
{
	OrderExecutionDriverDemo();
	
	cout << "\n\t - WARZONE PROJECT - \n";

	ofstream file("gamelog.txt", ios::app);

	time_t t = time(0);

	file << "\n - New log created at time: " << ctime(&t) << " \n" << endl;

	file.close();

	LogObserver* logObs = new LogObserver();
	OrdersList* orderList = new OrdersList();
	Command* cmd = new Command();
	CommandProcessor* cmdP = new CommandProcessor();

	Order* order = new Negotiate(new Player(), new Player());
	order->Attach(logObs);

	cmd->Attach(logObs);
	cmdP->Attach(logObs);
	orderList->Attach(logObs);

	cmdP->saveCommand(cmd);
	cmd->saveEffect("");
	orderList->add(order);

	order->execute();


	CommandProcessingDemo();
	
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