#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>
#include "LoggingObserver.h"
//#include "CommandProcessingDriver.h"
//#include "OrderExecutionDriver.h"
//#include "CommandProcessing.h"
#include "GameEngineDriver2.h"
#include "Drivers.h"

using namespace std;

int main() 
{
	
	cout << "\n\t - WARZONE PROJECT - \n";

	ofstream file("gamelog.txt", ios::app);

	time_t t = time(0);

	file << "\n - New log created at time: " << ctime(&t) << " \n" << endl;

	file.close();

	LogObserver* lObs = new LogObserver();
	vector<Player*>* players = new vector<Player*>;
	Deck* deck = new Deck();


	CommandProcessingDemo(*lObs);
	OrderExecutionDriverDemo(*lObs); //place somewhere else
	runGameLoop(players, deck);
}