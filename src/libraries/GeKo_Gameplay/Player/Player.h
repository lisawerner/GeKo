#pragma once
#include <glm/ext.hpp>
#include <iostream>
#include <GeKo_Graphics/Scenegraph/Node.h>

/** 
The Player class is a Basic class to provide a playable character. It is just an Basic-Class and every "real" character-class has to be a generalisation of this class.
It provides a spawnpoint location, a  name, a current, a speed and can be visualized by a Geometry. The Geometry has to be bound to a Node (see Scenegraph for details!).
*/
class Player 
{

public:	

	/// Contructor needs at least a name
	Player(std::string playerName);
	/// Second constructor with a Name and a Spawnpoint
	/** The Spawnpoint will be the first position of the character on the playground*/
	Player(glm::vec3 spawnPoint, std::string playerName);
	~Player();

	///Returns the m_playerName Attribute
	/**/
	std::string getName();

	///Returns the m_spawnPoint position
	/**/
	glm::vec3 getSpawnPoint();

	///Returns the m_currentPosition
	/**/
	glm::vec3 getCurrentPosition();

	///Sets the m_currentPosition to the newPosition
	/** Will change the currentPosition completely*/
	void changePosition(glm::vec3 newPosition);

	///Sets the m_geometryPlayer
	/**With this method a Node will be add to the Player-class. If the Node has a geometry, this geometry can be used to visualize the Character on screen*/
	void setNode(Node* geometryNode);

protected:
	std::string m_playerName;

	glm::vec3 m_spawnPoint;

	glm::vec3 m_currentPosition;

	float m_speed;

	Node* m_geometryPlayer;

};