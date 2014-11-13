#pragma once
#include "include.h"
#include "Shader.h"

class Light
{
public:
	Light(glm::vec4 position, glm::vec3 color, bool isActive);
	~Light();
	void sendUniform();

	glm::vec3 m_color;
	glm::vec4 m_position;
	bool m_isActive;
};