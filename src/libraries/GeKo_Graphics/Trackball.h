#pragma once

#include "GeKo_Graphics/Defs.h"
#include "Camera.h"
#include "GeKo_Graphics/Window.h"

class Trackball : public Camera
{
public:
	Trackball(int width, int height);
	~Trackball();

	// changes the positon in direction of the z axis
	void moveForward();
	void moveBackward();

	// moves the positon in a circle around the object
	void moveLeft();
	void moveRight();

	// moves the positon in a half-circle over the object
	void moveUp();
	void moveDown();


protected:

	double m_radius;
	// Remember the last x and y position
	double m_oldX, m_oldY;
	// Angle in x direction
	double m_phi;
	// Angle in y direction
	double m_theta;

};

