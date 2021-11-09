#include "LoggingObserver.h"
#include <iostream>
#include <fstream>

using namespace std;


Subject::Subject()
{
	observers = new list<LogObserver*>;
}

Subject::~Subject()
{
	delete observers;
}

void Subject::Attach(LogObserver* obs)
{
	observers->push_back(obs);
}

void Subject::Detach(LogObserver* obs)
{
	observers->remove(obs);
}


void Subject::Notify(ILoggable log) {
	for (LogObserver* obs : *observers)
	{
		obs->Update(log);
	}
}
LogObserver::LogObserver()
{

};

LogObserver::LogObserver(Subject* sub)
{
	this->subject = sub;
	this->subject->Attach(this);
};

LogObserver::~LogObserver()
{
	subject->Detach(this);
}

void LogObserver::Update(ILoggable log)
{
	ofstream outfile("gamelog.txt");

	log.stringToLog();

	outfile.close();
};