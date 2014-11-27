#pragma once
//#include "GeKo_Graphics/include.h"
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class PointLight 
{
public:
	PointLight();
	PointLight(glm::vec4 position, glm::vec3 color, bool isActive, double radius);
	~PointLight();

	glm::vec3 m_color;
	glm::vec4 m_position;
	bool m_isActive;
	float m_radius;

	glm::vec3 m_direction = glm::vec3(0.0, 0.0, 0.0);
	float m_exponent = 0;
	int m_angle = 0;
};