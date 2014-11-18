#pragma once

#include "GeKo_Graphics/Defs.h"

class Camera
{
public:
	Camera();
	Camera(std::string cameraName);
	~Camera();

	glm::mat4 getViewMatrix();

	glm::mat4 getProjectionMatrix();
	
	void setNearFar(float near, float far);
	float getNear();
	float getFar();

	void setWidthHeight(int width, int height);

	void setPosition(glm::vec4 position);

	glm::vec4 getPosition();

	std::string getName();
	void setName(std::string n);

	// changes the positon in direction of the z axis
	virtual void moveForward();
	virtual void moveBackward();

	// Implemented in Trackball
	virtual void moveAroundRight();
	virtual void moveAroundLeft();
	virtual void moveOverForward();
	virtual void moveOverBackward();

	

protected:
	std::string m_name;
	float m_fov, m_near, m_far;
	int m_width, m_height;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;


	glm::vec4 m_position, m_center, m_up;
	
};

