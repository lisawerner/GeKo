#pragma once
#include "PointLight.h"

PointLight::PointLight()
{
	m_position = glm::vec4(0.0, 0.0, 0.0, 1.0);
	m_color = glm::vec3(1.0,1.0,1.0);
	m_isActive = true;
	m_radius = 0;
}

PointLight::PointLight(glm::vec4 position, glm::vec3 color, bool isActive, double radius)
{
	m_position = position;
	m_color = color;
	m_isActive = isActive;
	m_radius = radius;
}

PointLight::~PointLight()
{
}