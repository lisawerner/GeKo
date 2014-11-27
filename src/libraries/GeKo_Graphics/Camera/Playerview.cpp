#include "Playerview.h"

Playerview::Playerview(int width, int height)
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

	m_speed = 0.01f;
	m_sensitivity = 0.01f;
}

Playerview::~Playerview()
{
}

void Playerview::setPosition(glm::vec4 position){
	m_position = position;
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));
}

void Playerview::setSpeed(float speed){
	m_speed = speed;
}

double Playerview::getSpeed(){
	return m_speed;
}

void Playerview::setSensitivity(float sensitivity){
	m_sensitivity = sensitivity;
}

double Playerview::getSensitivity(){
	return m_sensitivity;
}

double Playerview::getOldX(){
	return m_oldX;
}

void Playerview::setOldX(double x){
	m_oldX = x;
}

double Playerview::getOldY(){
	return m_oldY;
}

void Playerview::setOldY(double y){
	m_oldY = y;
}

void Playerview::setChangeX(double x){
	m_changeX = x;
}

void Playerview::setChangeY(double y){
	m_changeY = y;
}

void Playerview::moveForward(){
	m_position += (m_speed* m_direction);
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "moveForward()" << std::endl;
}

void Playerview::moveBackward(){
	m_position -= (m_speed * m_direction);
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "moveBackward()" << std::endl;
}

void Playerview::moveLeft(){
	// Rotates a copy of m_direction about 270 degrees
	glm::vec4 directionCopy = m_direction;
	glm::mat4 rotateLeft = glm::rotate(glm::mat4(1), 90.0f, glm::vec3(0, 1, 0));
	directionCopy = rotateLeft*directionCopy;
	// Moves left on the axis, which is orthogonal to the direction
	m_position += (m_speed * directionCopy);
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "moveLeft()" << std::endl;
}

void Playerview::moveRight(){
	// Rotates a copy of m_direction about 90 degrees
	glm::vec4 directionCopy = m_direction;
	glm::mat4 rotateLeft = glm::rotate(glm::mat4(1), 270.0f, glm::vec3(0, 1, 0));
	directionCopy = rotateLeft*directionCopy;
	// Moves right on the axis, which is orthogonal to the direction
	m_position += (m_speed * directionCopy);
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "moveRight()" << std::endl;
}

void Playerview::turn(){
	
		m_theta -= m_changeY;

		if (m_theta < 0.01f) m_theta = 0.01f;
		else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

		m_phi -= m_changeX;

		if (m_phi < 0) m_phi += 2 * glm::pi<float>();
		else if (m_phi > 2 * glm::pi<float>()) m_phi -= 2 * glm::pi<float>();

		m_direction.x = sin(m_theta) * cos(m_phi);
		m_direction.y = cos(m_theta);
		m_direction.z = -sin(m_theta) * sin(m_phi);
		
		m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));
}


