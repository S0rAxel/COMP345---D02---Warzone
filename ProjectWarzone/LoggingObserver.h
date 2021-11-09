#pragma once

#include <list>
#include <string>

using namespace std;

class Observer;

class Subject
{
public:
	Subject();
	Subject(const Subject& sub);
	virtual ~Subject();
	virtual void Attach(Observer* obs) = 0;
	virtual void Detach(Observer* obs) = 0;
	virtual void Notify( class ILoggable &log) = 0;

	Subject& operator= (const Subject& ordList);
private:
	list<Observer*>* observers;
};

class ILoggable
{
public:
	virtual string StringToLog() = 0;
};

class Observer
{
public:
	virtual void Update(ILoggable &log) = 0;
};

class LogObserver : public Observer
{
public:
	LogObserver();
	LogObserver(Subject* sub);
	~LogObserver();
	void Update(ILoggable &log);

private:
	Subject* subject;
};

