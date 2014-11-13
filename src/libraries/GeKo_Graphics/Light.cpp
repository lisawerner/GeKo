#include "Light.h"

Light::Light(glm::vec4 position, glm::vec3 color, bool isActive)
{
	m_position = position;
	m_color = color;
	m_isActive = isActive;
}

Light::~Light()
{
}

void Light::sendUniform(){
	//Todo
}