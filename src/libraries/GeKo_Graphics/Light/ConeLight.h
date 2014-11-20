#pragma once
#include "Light.h"

class ConeLight : public Light
{
public:
	ConeLight(glm::vec4 m_direction, int m_angle, double m_exponent);
	~ConeLight();

	glm::vec4 m_direction;
	double m_exponent;
	int m_angle;
};