#pragma once

#include "GeKo_Graphics/Defs.h"
#include "Camera.h"


class Playerview : public Camera
{
public:
	Playerview(int width, int height);
	~Playerview();

	void setPosition(glm::vec4 position);
	void setSpeed(float speed);
	double getSpeed();
	void setSensitivity(float sensitivity);
	double getSensitivity();
	double getOldX();
	void setOldX(double x);
	double getOldY();
	void setOldY(double y);

	// changes the positon in direction of the z axis
	void moveForward();
	void moveBackward();
	
	// changes the positon on the x axis
	void moveLeft();
	void moveRight();

	// changes direction with the aid of the mouse position callback
	void turn(double &changeX, double &changeY);

protected:

	glm::vec4 m_direction;
	// Remember the last x and y position
	double m_oldX, m_oldY;
	// Angles in x and y direction
	double m_phi, m_theta;
	// Speed of movement
	float m_speed;
	float m_sensitivity;
};

