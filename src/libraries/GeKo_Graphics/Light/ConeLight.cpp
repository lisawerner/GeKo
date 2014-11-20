#include "ConeLight.h"

ConeLight::ConeLight(glm::vec4 direction, int angle, double exponent)
{
	m_direction = direction;
	m_angle = angle;
	m_exponent = exponent;
}

ConeLight::~ConeLight()
{
}