#pragma once
#include "Observer.h"
#include <vector>
#include <string>

class Subject
{
private:
	std::vector<Observer*> m_observers;
public:
	Subject();
	virtual ~Subject();

	void AddObserver(Observer* p_observer);
	void RemoveObserver(Observer* p_observer);
protected:
	void NotifyObservers(std::string p_msg);
};