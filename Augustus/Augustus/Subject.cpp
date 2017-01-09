#include "stdafx.h"
#include "Subject.h"

Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::AddObserver(Observer * p_observer)
{
	m_observers.push_back(p_observer);
}

void Subject::RemoveObserver(Observer * p_observer)
{
	for (unsigned int i = 0; i < m_observers.size(); i++) {
		Observer* o = m_observers[i];
		if (o == p_observer) {
			m_observers.erase(m_observers.begin() + i);
		}
	}
}

void Subject::NotifyObservers(std::string p_msg)
{
	for (auto o : m_observers) {
		o->Notify(p_msg);
	}
}
