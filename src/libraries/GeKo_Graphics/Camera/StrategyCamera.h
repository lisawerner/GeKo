#pragma once

#include "Camera.h"

class StrategyCamera : public Camera
{

public:

	StrategyCamera(std::string name);

	~StrategyCamera();

	void update(GLFWwindow* window);

	void setCenter(glm::vec4 center);
	void setRadius(float radius);

	void updateCursor(GLFWwindow* window);

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void increaseRadius();
	void decreaseRadius();

	void setViewDirection(glm::vec3 viewDirection);

	double getXAngle();
	double getYAngle();
	
protected:
	double m_oldX, m_oldY;
	float m_sensitivity;
	double m_theta, m_phi, m_radius;
	double angle;

	glm::vec3 m_movementVector;
	glm::vec3 m_viewDirection;
};