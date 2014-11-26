#pragma once

#include "GeKo_Graphics/Defs.h"
#include "Camera.h"


class Pilotview : public Camera
{
public:
	Pilotview(int width, int height);
	~Pilotview();

	void setPosition(glm::vec4 position);
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);

	// changes the positon in direction of the z axis
	void moveForward();
	void moveBackward();
	
	// changes the positon on the x axis
	void moveLeft();
	void moveRight();

	// changes the positon on the y axis
	void moveUp();
	void moveDown();

	// change the positons diagonal
	void moveDiagonalFwdL();
	void moveDiagonalFwdR();
	void moveDiagonalBwdL();
	void moveDiagonalBwdR();

	// changes viewing direction
	void turnLeft();
	void turnRight();



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

