#pragma once
#include <glm/ext.hpp>
#include <GeKo_Graphics/Observer/Observer.h>
#include <GeKo_Graphics/Scenegraph/Node.h>


class GravityObserver : public Observer<Node, Collision_Event>
{
public:
	GravityObserver(){}

	~GravityObserver(){}

	void onNotify(Node& node, Collision_Event event)
	 {
		 switch (event)
		 {
		 case Collision_Event::PLANE_COLLISION:
			 //==TODO: Der 0.75-Wert müsste aus der HeightMap ausgelesen werden ==//
			 if (node.getType() == ClassType::OBJECT)
			 {
				 break;
			 }
			 else if (node.getType() == ClassType::PLAYER){
					 if (node.getPlayer()->getPosition().y < 0.75){
						 node.setGravity(false);
					 }
					 else if (true)
					 {
						 node.setGravity(true);
					 }
			 }
			 else if (node.getType() == ClassType::AI)
			 {
					 if (node.getAI()->getPosition().y < 0.75)
					 {
						 node.setGravity(false);
					 }
					 else if (true){
						 node.setGravity(true);
					 }
			 }
			
		 }
	 }

	
	void  onNotify(AI& node, Collision_Event event) 
	 {

	 }
	
};

