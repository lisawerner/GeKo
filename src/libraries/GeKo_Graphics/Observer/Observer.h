#pragma once
#include <glm/ext.hpp>
#include <GeKo_Graphics/Observer/Collision_Event.h>
#include <GeKo_Graphics/Observer/Object_Event.h>
#include <GeKo_Graphics/Observer/Quest_Event.h>


template <class Entity, class Event>

class Observer
{
public:
	Observer(){}

	~Observer(){}


	virtual void onNotify(Entity& node, Event event){}

	virtual void onNotify(Entity& nodeA, Entity& nodeB, Event event){}

protected:


	
};

