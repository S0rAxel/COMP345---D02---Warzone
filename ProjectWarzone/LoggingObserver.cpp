#include "LoggingObserver.h"
#include <iostream>
#include <fstream>

using namespace std;

//Default Constructor
Subject::Subject()
{
	observers = new list<Observer*>;
}

// Copy constructor
Subject::Subject(const Subject& sub)
{
	observers = sub.observers;
}

// Assignment operator for OrdersList
Subject& Subject::operator= (const Subject& sub)
{
	// self-assignment guard
	if (this == &sub)
		return *this;

	for (Observer* obs : *sub.observers)
	{
		observers = new list<Observer*>;
		observers->push_back(obs);
	}

	return *this;
}

//Deconstructor
Subject::~Subject()
{
	delete observers;
}

void Subject::Attach(Observer* obs)
{
	observers->push_back(obs);
}

void Subject::Detach(Observer* obs)
{
	observers->remove(obs);
}

void Subject::Notify(ILoggable& log) {
	for (Observer* obs : *observers)
	{
		obs->Update(log);
	}
}

LogObserver::LogObserver()
{

}

/// <summary>
/// Copy Constructor
/// </summary>
LogObserver::LogObserver(const LogObserver& obs)
{
	subject = obs.subject;
}

// Assignment operator for OrdersList
LogObserver& LogObserver::operator= (const LogObserver& obs)
{
	// self-assignment guard
	if (this == &obs)
		return *this;

	subject = obs.subject;

	return *this;
}

LogObserver::~LogObserver()
{
	subject->Detach(this);
}

void LogObserver::Update(ILoggable& log)
{
	ofstream file("gamelog.txt", ios::app);
	
	if (!file.is_open())
		cout << "File could not be opened" << endl;

	file << log.StringToLog();

	file.close();
};