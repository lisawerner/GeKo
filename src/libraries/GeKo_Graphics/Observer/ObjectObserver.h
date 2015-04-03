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

	void onNotify(AI& node, Collision_Event event)  
	 {
		 switch (event)
		 {
		 case Collision_Event::COLLISION_KI_PLAYER:
			 node.viewArea(true);
			 break;
			  
		 case Collision_Event::NO_COLLISION_KI_PLAYER:
			 node.viewArea(false);
			 break;
		 }
	 }

	void onNotify(AI& node, Object_Event event) 
	{
		switch (event)
		{
		case Object_Event::OBJECT_MOVED:
			std::string name = node.getNodeName();
			Node* tmp = m_level->getActiveScene()->getScenegraph()->searchNode(name);
			tmp->addTranslation(node.getPosition());
			break;
		}
	}

	void onNotify(Player& node, Object_Event event) 
	 {
		 std::string name = node.getNodeName();
		 Node* tmp = m_level->getActiveScene()->getScenegraph()->searchNode(name);
		 switch (event)
		 {
		 case Object_Event::OBJECT_MOVED:
			 tmp->addTranslation(node.getPosition());
			 if (tmp->hasCamera())
			 {
				 tmp->getCamera()->setCenter(glm::vec4(node.getPosition().x, tmp->getCamera()->getCenter().y, node.getPosition().z, 1.0));
			 }
	
			 break;

		 case Object_Event::OBJECT_STOPPED:
			 break;
		 }
	 }

protected: 
	Level* m_level;	
};