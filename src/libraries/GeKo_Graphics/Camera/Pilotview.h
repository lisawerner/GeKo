#pragma once

#include "GeKo_Graphics/Defs.h"
#include "Camera.h"


class Pilotview : public Camera
{
public:
	Pilotview(int width, int height);
	~Pilotview();

	// changes the positon in direction of the z axis
	void moveForward();
	void moveBackward();
	
	// changes the positon on the x axis
	void moveLeft();
	void moveRight();

	// changes the positon on the y axis
	void moveUp();
	void moveDown();


protected:

	glm::vec4 m_direction;
	// Remember the last x and y position
	double m_oldX, m_oldY;
	// Angles in x and y direction
	double m_phi, m_theta;
};

