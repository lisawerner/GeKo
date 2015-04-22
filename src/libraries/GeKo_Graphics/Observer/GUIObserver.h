#pragma once
#include <glm/ext.hpp>
#include <GeKo_Graphics/Observer/Observer.h>
#include <GeKo_Graphics/Scenegraph/Node.h>
#include <GeKo_Graphics/Scenegraph/Level.h>

/**Handles all the gravity-effects of the game.*/
class GUIObserver : public Observer<Object, Object_Event>
{
public:
	GUIObserver(Level* level){ m_level = level; }

	~GUIObserver(){}

	void onNotify(Object& object, Object_Event event)
	 {
		switch (event)
		{
		case Object_Event::PLAYER_EXP:
			break;
		}
	 }


protected:
	Level* m_level;
};