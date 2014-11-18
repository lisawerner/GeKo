#pragma once

#include "GeKo_Graphics/Defs.h"
#include "Camera.h"


class Pilotview : public Camera
{
public:
	Pilotview(int width, int height);
	~Pilotview();

	void moveForward();
	void moveBackward();
	
	void moveLeft();
	void moveRight();

	void moveUp();
	void moveDown();


protected:

	glm::vec4 m_direction;

	double m_oldX, m_oldY;
	double m_theta, m_phi;
};

