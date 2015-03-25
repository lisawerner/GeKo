#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

//#include <GeKo_Graphics/Scenegraph/Node.h>
//#include <GeKo_Graphics/Scenegraph/CollisionTest.h>
#include <GeKo_Graphics/Observer/Subject.h>
#include <GeKo_Gameplay/Item/Inventory.h>
#include <GeKo_Sound/SoundFileHandler.h>

#include "ObjectType.h"
#include "ClassType.h"
#include "States.h"

//class Node;

//class AI;

//template <class Entity>

class Object
{
public: 
	//Eine Position: Objekt startet zu Hause! (Weiterer Konstrutkor, falls Objekt woanders starten soll)
	//Object(Node* defaultGeometry);
	Object();
	~Object();

	void setPosition(glm::vec3 pos);

	glm::vec3 getPosition();

	//void setGeometry(Node* geom);

	float getStrength();

	void setHealth(float newHealth);
	float getHealth();

	void setNodeName(std::string nodeName);
	std::string getNodeName();

	Inventory* getInventory();

	void setObjectType(ObjectType type);
	ObjectType getObjectType();

	glm::vec3 getViewDirection();

	bool getStates(States state);
	void setStates(States state, bool b);

	//Per Frame
	//Update: Individuell für jeden
	virtual void update();
	//Gleich (Hunger, Leben, etc)
	void updateStates();

	//Move Object on Terrain
	virtual void move();

	virtual void eat();

	void collectItem(ItemType typeId, int count);

	ClassType getClassType();

	virtual void heal();

	float getExp();
	void addExp(float exp);
	void setExp(float exp);

	int getLvl();
	void levelUp();
	void setLevel(int level);

	float getLevelThreshold();
	void setLevelThreshold(float threshold);

	///Returns the m_sfh
	/**This Handler manages all the sounds of an object like the movement of a Player etc.*/
	SoundFileHandler* getSoundHandler();
	void setSoundHandler(SoundFileHandler* soundHandler);

protected:
	int m_id;
	ObjectType m_type;
	std::string m_name;
	std::string m_myNodeName;
	ClassType m_class;

	glm::vec3 m_position;

	glm::vec3 m_viewDirection;

	//Scala von 0 bis 10 oder so
	std::vector<std::pair<States, bool>> m_states;
	float m_hunger;
	float m_hungerMax;
	float m_health;
	float m_healthMax;
	float m_speed;
	float m_strength;
	float m_exp;
	int m_level;
	float m_levelThreshold;

	Inventory* m_inventory;
	SoundFileHandler* m_sfh;

	bool m_hasSound;
};