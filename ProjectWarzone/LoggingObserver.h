#pragma once

#include <list>
#include <string>

class LogObserver;

using namespace std;

class Subject
{
public:
	Subject();
	virtual ~Subject();
	virtual void Attach(LogObserver* obs) = 0;
	virtual void Detach(LogObserver* obs) = 0;
	virtual void Notify(class ILoggable log) = 0;
private:
	list<LogObserver*>* observers;
};

class ILoggable
{
public:
	virtual string stringToLog() { return "help"; };
};

class Observer
{
public:
	virtual void Update(class ILoggable log) = 0;
};

class LogObserver : public Observer
{
public:
	LogObserver();
	LogObserver(Subject* sub);
	~LogObserver();
	virtual void Update(ILoggable log);

private:
	Subject* subject;
};

