#include "Trackball.h"

Trackball::Trackball(int width, int height)
{
	m_position = glm::vec4(0.0f, 0.0f, 10.0f, 1.0f);
	m_center = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	m_up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

	m_width = width;
	m_height = height;

	m_fov = 60.0f;
	m_near = 0.001f;
	m_far = 100.0f;

	m_radius = 10;

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));
	m_projectionMatrix = glm::perspective(m_fov, m_width / (float)m_height, m_near, m_far);

	m_oldX = width / 2;
	m_oldY = height / 2;
	m_theta = glm::pi<float>() / 2.0f;
	m_phi = -glm::pi<float>() / 2.0f;
}

Trackball::~Trackball()
{
}

void Trackball::moveForward(){
	m_position.z -= 0.1f;
	m_radius -= 0.1;

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "TBall move fwd z " << m_position.z << std::endl;
}

void Trackball::moveBackward(){
	m_position.z += 0.1f;
	m_radius += 0.1;

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "TBall move bwd z " << m_position.z << std::endl;
}


void Trackball::moveAroundLeft(){
	
	m_oldX = - 0.01f + m_oldX;
	m_phi -= 0.01;
	if (m_phi < 0) m_phi += 2 * glm::pi<float>();
	else if (m_phi > 2 * glm::pi<float>()) m_phi -= 2 * glm::pi<float>();

	m_position.x = m_radius * sin(m_theta) * cos(m_phi);
	m_position.y = m_radius * cos(m_theta);
	m_position.z = -m_radius * sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));
	
	std::cout << "TBall move rndL x " << m_position.x << " z " << m_position.z << std::endl;
}

void Trackball::moveAroundRight(){
	m_oldX = 0.01f + m_oldX;
	m_phi += 0.01;
	if (m_phi < 0) m_phi += 2 * glm::pi<float>();
	else if (m_phi > 2 * glm::pi<float>()) m_phi -= 2 * glm::pi<float>();

	m_position.x = m_radius * sin(m_theta) * cos(m_phi);
	m_position.y = m_radius * cos(m_theta);
	m_position.z = -m_radius * sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "TBall move rndR x " << m_position.x << " z " << m_position.z << std::endl;
}

void Trackball::moveOverForward(){
	m_oldY = -0.01f + m_oldX;
	m_theta -= 0.01;
	if (m_theta < 0.01f) m_theta = 0.01f;
	else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

	m_position.x = m_radius * sin(m_theta) * cos(m_phi);
	m_position.y = m_radius * cos(m_theta);
	m_position.z = -m_radius * sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "TBall move oFwd y " << m_position.y << " z " << m_position.z << std::endl;
}

void Trackball::moveOverBackward(){
	m_oldY = 0.01f + m_oldX;
	m_theta += 0.01;
	if (m_theta < 0.01f) m_theta = 0.01f;
	else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

	m_position.x = m_radius * sin(m_theta) * cos(m_phi);
	m_position.y = m_radius * cos(m_theta);
	m_position.z = -m_radius * sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "TBall move oBwd y " << m_position.y << " z " << m_position.z << std::endl;
}