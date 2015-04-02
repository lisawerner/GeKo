#pragma once

#include "GeKo_Gameplay/Object/Player.h"

/**This class is a first generalisation of the Player class. A Geko has a view direction and a movement vector, so it can be moved over the terrain. 
The Geko-class also has its own movement Methods and each frame it will be updated, so the player can move*/
class Geko : public Player
{
public:
	///Same Constructors as the Player-class
	/** The Speed will be set to 0.8 and viewDirection and movement vector will be set automatically!*/
	Geko(std::string gekoName);
	Geko(std::string gekoName, glm::vec3 spawnPoint);
	Geko();
	~Geko();

	///A Method to move forward in view Direction
	/**Changes the movement vector*/
	void moveForward();
	///A Method to move backwards in relation to view direction
	/**Changes the movement vector*/
	void moveBackward();
	///A Method to move sidewards, right
	/**Changes the movement vector*/
	void moveRight();
	///A Method to move sidewards, left
	/**Changes the movement vector*/
	void moveLeft();

	///A Method to update the position
	/**If the movement vector has changed, the new position will be calculated. The model matrix of the geometry will be updated as well.
	If the view rotated, this method will update the model matrix additionally. The method will be called in each frame!*/
	void update(float deltaTime);

	glm::vec3 getPosition();

protected: 
	glm::vec3 m_movementVector;
};