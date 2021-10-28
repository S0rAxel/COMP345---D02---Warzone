#pragma once

#include "Observer.h"
#include <list>

using namespace std;

class Subject {
public:
	virtual ~Subject() {};
	virtual void Attach() = 0;
	virtual void Detach() = 0;
	virtual void Notify(class ILoggable log) = 0;
};