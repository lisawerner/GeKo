#pragma once
#include "Light.h"

class DirectionLight : public Light
{
public:
	DirectionLight(glm::vec4 direction);
	~DirectionLight();

	glm::vec4 m_direction;
};

