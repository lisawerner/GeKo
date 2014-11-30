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

	m_speed = 0.1;
	m_sensitivity = 0.01;
}

Trackball::~Trackball()
{
}

void Trackball::setPosition(glm::vec4 position){
	m_position = position;
	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));
}

void Trackball::setSpeed(float speed){
	m_speed = speed;
}

void Trackball::setSensitivity(float sensitivity){
	m_sensitivity = sensitivity;
}

void Trackball::moveForward(){
	m_position.z -= m_speed;
	m_radius -= m_speed;

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "moveForward() " << std::endl;
}

void Trackball::moveBackward(){
	m_position.z += m_speed;
	m_radius += m_speed;

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "moveBackward() " << std::endl;
}

void Trackball::moveLeft(){
	
	m_oldX = (-m_speed + m_oldX)*m_sensitivity;
	m_phi -= m_speed;
	if (m_phi < 0) m_phi += 2 * glm::pi<float>();
	else if (m_phi > 2 * glm::pi<float>()) m_phi -= 2 * glm::pi<float>();

	m_position.x = m_radius * sin(m_theta) * cos(m_phi);
	m_position.y = m_radius * cos(m_theta);
	m_position.z = -m_radius * sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));
	
	std::cout << "moveLeft()" << std::endl;
}

void Trackball::moveRight(){
	m_oldX = (m_speed + m_oldX)*m_sensitivity;
	m_phi += m_speed;
	if (m_phi < 0) m_phi += 2 * glm::pi<float>();
	else if (m_phi > 2 * glm::pi<float>()) m_phi -= 2 * glm::pi<float>();

	m_position.x = m_radius * sin(m_theta) * cos(m_phi);
	m_position.y = m_radius * cos(m_theta);
	m_position.z = -m_radius * sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "moveRight()" << std::endl;
}

void Trackball::moveUp(){
	m_oldY = (-m_speed + m_oldX)*m_sensitivity;
	m_theta -= m_speed;
	if (m_theta < 0.01f) m_theta = 0.01f;
	else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

	m_position.x = m_radius * sin(m_theta) * cos(m_phi);
	m_position.y = m_radius * cos(m_theta);
	m_position.z = -m_radius * sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "moveUp()" << std::endl;
}

void Trackball::moveDown(){
	m_oldY = (m_speed + m_oldX)*m_sensitivity;
	m_theta += m_speed;
	if (m_theta < 0.01f) m_theta = 0.01f;
	else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

	m_position.x = m_radius * sin(m_theta) * cos(m_phi);
	m_position.y = m_radius * cos(m_theta);
	m_position.z = -m_radius * sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_center) + glm::vec3(m_position), glm::vec3(m_center), glm::vec3(m_up));

	std::cout << "moveDown()" << std::endl;
}