#include "Light.h"

Light::Light()
{
	m_position = glm::vec4(0.0,0.0,0.0,1.0);
	m_color = glm::vec3(1.0,1.0,1.0);
	m_isActive = true;
}

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