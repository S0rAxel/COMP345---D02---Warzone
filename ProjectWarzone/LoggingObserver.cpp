#define _CRT_SECURE_NO_DEPRECATE

#include "LoggingObserver.h"
#include <iostream>
#include <fstream>

using namespace std;

#pragma region Subject

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

// Assignment operator
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

// Stream insertion operator
ostream& operator<<(ostream& stream, const Subject& sub) {
	return stream << " Subject to stream insertion operator";
}

#pragma endregion

#pragma region LogObserber

//Default Constructor
LogObserver::LogObserver()
{

}

// Copy Constructor
LogObserver::LogObserver(const LogObserver& obs)
{
	subject = obs.subject;
}

// Assignment operator
LogObserver& LogObserver::operator= (const LogObserver& obs)
{
	// self-assignment guard
	if (this == &obs)
		return *this;

	subject = obs.subject;

	return *this;
}

// Destructor
LogObserver::~LogObserver()
{
	subject->Detach(this);
}

// Implementation of virtual method from parent class Observer
void LogObserver::Update(ILoggable& log)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	ofstream file("gamelog.txt", ios::app);

	// Check if the file was not been able to open
	if (!file.is_open())
		cout << "File could not be opened" << endl;


	file << 5 + ltm->tm_hour << ":" << 30 + ltm->tm_min << ":" << ltm->tm_sec << " - " << log.StringToLog();

	file.close();
};

// Stream insertion operator
ostream& operator<<(ostream& stream, const LogObserver& sub) {
	return stream << " Log Observer from stream insertion operator";
}

#pragma endregion
