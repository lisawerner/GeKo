#pragma once
#include <glm/ext.hpp>
#include <GeKo_Graphics/Observer/Observer.h>
#include <GeKo_Graphics/Scenegraph/Level.h>

/**An Obsever for the AI and Player which handles collision between them and lets the object move.*/
class ObjectObserver : public Observer<AI, Object_Event>, public Observer<AI, Collision_Event>, public Observer<Player, Object_Event>
{
public:
	ObjectObserver(Level* level){ m_level = level; }

	~ObjectObserver(){}

	void onNotify(AI& ai, Collision_Event event)  
	 {
		 switch (event)
		 {
		 case Collision_Event::COLLISION_KI_PLAYER:
			 ai.viewArea(true);
			 break;
			  
		 case Collision_Event::NO_COLLISION_KI_PLAYER:
			 ai.viewArea(false);
			 break;
		 }
	 }

	void onNotify(AI& ai, Object_Event event) 
	{
		switch (event)
		{
		case Object_Event::OBJECT_MOVED:
			std::string name = ai.getNodeName();
			Node* tmp = m_level->getActiveScene()->getScenegraph()->searchNode(name);
			tmp->addTranslation(glm::vec3(ai.getPosition()));
			break;
		}
	}

	void onNotify(Player& player, Object_Event event) 
	 {
		 std::string name = player.getNodeName();
		 Node* tmp = m_level->getActiveScene()->getScenegraph()->searchNode(name);
		 switch (event)
		 {
		 case Object_Event::OBJECT_MOVED:
			 tmp->addTranslation(glm::vec3(player.getPosition()));
			 if (tmp->hasCamera())
			 {
				 // Camera looks at player position
				 tmp->setCameraToPlayer();
			 }
	
			 break;
		 case Object_Event::OBJECT_ROTATED:
			 tmp->addRotation(player.getPhi(), glm::vec3(0, -1, 0));
			// tmp->addRotation(player.getAlpha(), glm::vec3(0, 1, 0));
			 if (tmp->hasCamera())
			 {
				 tmp->setCameraToPlayer();
			 }
			 break;
		 case Object_Event::OBJECT_STOPPED:
			
			 break;
		 }
	 }

protected: 
	Level* m_level;	
};