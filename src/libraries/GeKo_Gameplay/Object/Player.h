#pragma once
#include <glm/ext.hpp>
#include <iostream>

#include "Object.h"
/** 
The Player class is a Basic class to provide a playable character. It is just an Basic-Class and every "real" character-class has to be a generalisation of this class.
It provides a spawnpoint location, a  name, a current, a speed and can be visualized by a Geometry. The Geometry has to be bound to a Node (see Scenegraph for details!).
*/
enum Soundtype{
	MOVESOUND, BACKGROUNDMUSIC, FIGHTSOUND, EATSOUND, QUESTSOUND, ITEMSOUND
};

class Player : public Object, public Subject<Player, Object_Event>
{

public:	

	/// Contructor needs at least a name
	Player(std::string playerName);
	/// Second constructor with a Name and a Spawnpoint
	/** The Spawnpoint will be the first position of the character on the playground*/
	Player(std::string playerName, glm::vec3 spawnPoint);
	Player();
	~Player();

	///Returns the m_spawnPoint position
	/**/
	glm::vec3 getSpawnPoint();

	//Updates the object per Frame
	void update();

	//Moves Object on Terrain
	void move(glm::vec3 newPosition);
	
	///A method to rotate the view direction
	/**This method is used to simulate the movement of the head of the character*/
	void rotateView(float leftRight, float upDown);

	///Returns the m_sourceName string
	/**If a Sound-File-Handler was attached, the m_sourceName contains the name of the source which should be played!*/
	std::string getSourceName(Soundtype type);
	///Sets a specific source-file to the node
	/**This method uses the sfh to generate a new sound-source which can be played with the sfh later ingame!*/
	void setSourceName(Soundtype type, std::string sourceName, const char* filepath);

	void updateSourcesInMap();

protected:
	glm::vec3 m_spawnPoint;

	std::map<Soundtype, std::string> m_soundMap;
};