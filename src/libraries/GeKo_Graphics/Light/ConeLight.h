#pragma once
#include "GeKo_Graphics/include.h"

class ConeLight
{
public:
	ConeLight();
	ConeLight(glm::vec4 position, glm::vec3 color, bool isActive, glm::vec3 direction, int angle, double exponent, double radius);
	~ConeLight();

	glm::vec3 m_color;
	glm::vec4 m_position;
	bool m_isActive;
	glm::vec3 m_direction;
	float m_exponent;
	int m_angle;
	float m_radius;
};