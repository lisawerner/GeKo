#pragma once
//#include "GeKo_Graphics/include.h"
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class DirectionLight
{
public:
	DirectionLight();
	DirectionLight(glm::vec4 position, glm::vec3 color, bool isActive, glm::vec3 direction, double radius);
	~DirectionLight();

	glm::vec3 m_color;
	glm::vec4 m_position;
	bool m_isActive;
	glm::vec3 m_direction;
	float m_radius;

	float m_exponent = 0;
	int m_angle = 0;
};

