#pragma once
#include <glm/ext.hpp>
#include <GeKo_Graphics/Observer/Observer.h>
#include <GeKo_Graphics/Scenegraph/Level.h>

/**This Observer handles all the sound actions like the move-sound or the fight-sounds.*/
class SoundObserver : public Observer<AI, Object_Event>, public Observer<Player, Object_Event>, public Observer<Node, Collision_Event>, public Observer<Quest, Quest_Event>
{
public:
	SoundObserver(Level* level){ m_level = level; }

	~SoundObserver(){}

	void  onNotify(AI& node, Object_Event event)
	{
		std::string name = node.getNodeName();
		std::string soundName;
		Node* tmp = m_level->getActiveScene()->getScenegraph()->searchNode(name);
		switch (event)
		{

		case Object_Event::OBJECT_MOVED:
			soundName = node.getSourceName(MOVESOUND_AI);
			//node.getSoundHandler()->updateListenerPosition(node.getPosition());
			node.updateSourcesInMap();
			if (soundName != "oor")
			{
				if (!(node.getSoundHandler()->sourceIsPlaying(soundName)))
				{
					node.getSoundHandler()->playSource(soundName);
				}
			}
			break;

		case Object_Event::OBJECT_STOPPED:
			soundName = node.getSourceName(MOVESOUND_AI);
			if (soundName != "oor")
			{
				if ((node.getSoundHandler()->sourceIsPlaying(soundName)))
				{
					node.getSoundHandler()->pauseSource(soundName);
				}
			}
			break;

		case Object_Event::OBJECT_DIED:

			soundName = node.getSourceName(DEATHSOUND_AI);
			if (soundName != "oor")
			{
				if (!(node.getSoundHandler()->sourceIsPlaying(soundName)))
				{
					node.getSoundHandler()->playSource(soundName);
				}
			}

			m_level->getActiveScene()->getScenegraph()->getRootNode()->deleteChildrenNode(node.getNodeName());			
			break;
		}
	}

	void onNotify(Player& node, Object_Event event)
	 {
		 std::string name = node.getNodeName();
		 std::string soundName;
		 switch (event)
		 {

		 case Object_Event::OBJECT_MOVED:
			 soundName =  node.getSourceName(MOVESOUND);
			 node.getSoundHandler()->updateListenerPosition(node.getPosition());
			 node.updateSourcesInMap();
			 if (soundName != "oor")
			 {
				 if (!(node.getSoundHandler()->sourceIsPlaying(soundName)))
				 {
					 node.getSoundHandler()->playSource(soundName);
				 }
			 }
	
			 break;

		 case Object_Event::OBJECT_ROTATED:
			 node.getSoundHandler()->updateListenerOrientation(node.getViewDirection(), glm::vec3(0.0, 1.0, 0.0));
			 break;

		 case Object_Event::OBJECT_STOPPED:
			 soundName = node.getSourceName(MOVESOUND);
			 if (soundName != "oor")
			 {
				 if ((node.getSoundHandler()->sourceIsPlaying(soundName)))
				 {
					 node.getSoundHandler()->pauseSource(soundName);
				 }
			 }
			 break;

		 case Object_Event::PLAYER_COLLECT:
			soundName = node.getSourceName(ITEMSOUND);
			 if (soundName != "oor")
			 {
					 node.getSoundHandler()->playSource(soundName);
			 }
			 break;
		 }
	 }

	void onNotify(Node& nodeA, Node& nodeB, Collision_Event event)
	{
		std::string tmp;
		switch (event)
		{
		case Collision_Event::COLLISION_AI_FIGHT_PLAYER:
			tmp = nodeB.getPlayer()->getSourceName(FIGHTSOUND);

			if (glm::length(nodeA.getBoundingSphere()->center - nodeB.getBoundingSphere()->center) <= 4.5)
			{

				if (nodeA.getAI()->getHealth() > 0)
				{
					if (tmp != "oor")
					{
						if (!nodeB.getPlayer()->getSoundHandler()->sourceIsPlaying(tmp))
						{
							nodeB.getPlayer()->getSoundHandler()->playSource(tmp);
						}

					}

				}
				else{
					nodeB.getPlayer()->getSoundHandler()->stopSource(tmp);
				}
			}

			else{
				if (nodeB.getPlayer()->getSoundHandler()->sourceIsPlaying(tmp))
				{
					nodeB.getPlayer()->getSoundHandler()->stopSource(tmp);
				}
			}
			break;

		case Collision_Event::COLLISION_KI_PLAYER:
			if (!nodeA.getAI()->getStates(States::HEALTH) && nodeA.getAI()->getInventory()->countItem(ItemType::COOKIE) > 0)
			{
				std::string soundName = nodeB.getPlayer()->getSourceName(EATSOUND);
				if (soundName != "oor")
				{
					if (!(nodeB.getPlayer()->getSoundHandler()->sourceIsPlaying(soundName)))
					{
						nodeB.getPlayer()->getSoundHandler()->playSource(soundName);
					}
				}
			}
			break;
		}
	}

	void  onNotify(Quest& quest, Quest_Event event)
	{
		switch (event){
		case Quest_Event::QUEST_FINISHED:
			std::vector<Node*>* tmp = m_level->getActiveScene()->getScenegraph()->getRootNode()->getChildrenSet();
			Node* tmp2;
			for (int i = 0; i < tmp->size(); i++)
			{
				if (tmp->at(i)->getType() == ClassType::PLAYER)
				{
					tmp2 = tmp->at(i);
				}
			}

			std::string soundName = tmp2->getPlayer()->getSourceName(QUESTSOUND);

			if (soundName != "oor")
			{
				tmp2->getPlayer()->getSoundHandler()->playSource(soundName);
			}
			break;
		}
	}
protected: 
	Level* m_level;
};