#include "Pilotview.h"

Pilotview::Pilotview(int width, int height)
{
	m_position = glm::vec4(0.0f, 0.0f, 10.0f, 1.0f);
	m_direction = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	m_up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

	m_width = width;
	m_height = height;

	m_fov = 60.0f;
	m_near = 0.001f;
	m_far = 10.0f;

	m_theta = glm::pi<float>() / 2.0f;
	m_phi = glm::pi<float>() / 2.0f;

	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));
	m_projectionMatrix = glm::perspective(m_fov, m_width / (float)m_height, m_near, m_far);

	m_oldX = width / 2;
	m_oldY = height / 2;
}

Pilotview::~Pilotview()
{
}

void Pilotview::moveForward(){
	m_position.z -= 0.1f;
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

}

void Pilotview::moveBackward(){
	m_position.z += 0.1f;
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

}

void Pilotview::moveLeft(){
	m_oldX = -0.01f + m_oldX;
	m_phi -= 0.01;
	if (m_phi < 0) m_phi += 2 * glm::pi<float>();
	else if (m_phi > 2 * glm::pi<float>()) m_phi -= 2 * glm::pi<float>();

	m_direction.x = sin(m_theta) * cos(m_phi);
	m_direction.y = cos(m_theta);
	m_direction.z = -sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

}
void Pilotview::moveRight(){
	m_oldX = 0.01f + m_oldX;
	m_phi += 0.01;
	if (m_phi < 0) m_phi += 2 * glm::pi<float>();
	else if (m_phi > 2 * glm::pi<float>()) m_phi -= 2 * glm::pi<float>();

	m_direction.x = sin(m_theta) * cos(m_phi);
	m_direction.y = cos(m_theta);
	m_direction.z = -sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));
}

void Pilotview::moveUp(){
	m_oldY = -0.01f + m_oldX;
	m_theta -= 0.01;
	if (m_theta < 0.01f) m_theta = 0.01f;
	else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

	m_direction.x = sin(m_theta) * cos(m_phi);
	m_direction.y = cos(m_theta);
	m_direction.z = -sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));
}

void Pilotview::moveDown(){
	m_oldY = 0.01f + m_oldX;
	m_theta += 0.01;
	if (m_theta < 0.01f) m_theta = 0.01f;
	else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

	m_direction.x = sin(m_theta) * cos(m_phi);
	m_direction.y = cos(m_theta);
	m_direction.z = -sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));
}


