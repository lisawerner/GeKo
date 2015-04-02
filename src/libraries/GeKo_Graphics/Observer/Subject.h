#pragma once
#include <glm/ext.hpp>
#include <vector>
#include <GeKo_Graphics/Observer/Observer.h>


template <class Entity, class Event>

class Subject
{
public:
	Subject() {}

	~Subject(){}

	void addObserver(Observer<Entity, Event>* observer)
	{
		m_myObserver.push_back(observer);
	}

	void removeObserver(Observer<Entity, Event>* observer)
	{
		for (int i = 0; i < m_myObserver.size(); i++)
		{
			//TODO: wirft Fehler
			/*if (typeid(m_myObserver.at(i)) == typeid(observer))
				m_myObserver.erase.at(i);*/
		}
	}

protected:


	void notify(Entity& node, Event event)
	{
		for (int i = 0; i < m_myObserver.size(); i++)
		{
			m_myObserver.at(i)->onNotify(node, event);
		}
	}

	void notify(Entity& nodeA, Entity& nodeB, Event event)
	{
		for (int i = 0; i < m_myObserver.size(); i++)
		{
			m_myObserver.at(i)->onNotify(nodeA,nodeB, event);
		}
	}


private:
	std::vector<Observer<Entity, Event>*> m_myObserver;


protected:


	
};

