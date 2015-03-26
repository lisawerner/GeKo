#pragma once
#include <glm/ext.hpp>
///Scenegraph contains Node
/**Every scenegraph is connected with one scene.
The scenegraph is managing all the objects in the scene which are added to the scenegraph by adding them to the scene*/
class Gravity
{
public:
	Gravity();

	~Gravity();

	glm::mat4 addGravity(glm::mat4 modelMatrix);

	glm::vec3 getGravity();

	void setGravity(glm::vec3 newGravity);


protected:
	glm::vec3 m_gravity;

	
};

