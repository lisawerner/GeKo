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
				 glm::vec3 camPosition;
				 camPosition = glm::vec3(player.getPosition() + (player.getViewDirection()*glm::vec4(-5.0)));
				 camPosition.y += 3.0;
				 tmp->getCamera()->setPosition(glm::vec4(camPosition, 1.0));
				// tmp->getCamera()->setPosition(glm::vec4(player.getPosition().x, 10.0, player.getPosition().z, 1.0));
				tmp->getCamera()->setLookAt(glm::vec3(player.getPosition() + player.getViewDirection()));
				
				 //tmp->getCamera()->setPosition(glm::vec4(camPosition, 1.0));
			 }
	
			 break;
		 case Object_Event::OBJECT_ROTATED:
			 tmp->addRotation(player.getPhi(), glm::vec3(0, 1, 0));
			 if (tmp->hasCamera())
			 {
				 //TODO: Kamera dreht sich zwar parallel mit, muss aber ihre Position zusätzlich ändern, da sie sich auf einem Kreis um das Object dreht
				 tmp->getCamera()->setLookAt(glm::vec3(player.getPosition() + player.getViewDirection()));
			 }
			 break;
		 case Object_Event::OBJECT_STOPPED:
			/* tmp->getCamera()->setPosition(glm::vec4(player.getPosition().x, 10.0, player.getPosition().z, 1.0));*/
			 glm::vec3 camPosition;
			 camPosition = glm::vec3(player.getPosition() + (player.getViewDirection()*glm::vec4(-5.0)));
			 camPosition.y += 3.0;
			 tmp->getCamera()->setPosition(glm::vec4(camPosition, 1.0));
			 tmp->getCamera()->setLookAt(glm::vec3(player.getPosition() + player.getViewDirection()));
			
			 break;
		 }
	 }

protected: 
	Level* m_level;	
};