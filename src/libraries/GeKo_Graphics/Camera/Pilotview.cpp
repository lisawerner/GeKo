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

	m_speed = 0.1f;
	m_sensitivity = 0.01f;
}

Pilotview::~Pilotview()
{
}

void Pilotview::setPosition(glm::vec4 position){
	m_position = position;
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));
}

void Pilotview::setSpeed(float speed){
	m_speed = speed;
}

void Pilotview::setSensitivity(float sensitivity){
	m_sensitivity = sensitivity;
}

void Pilotview::moveForward(){
	m_position += (m_speed* m_direction);
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "moveForward()" << std::endl;
}

void Pilotview::moveBackward(){
	m_position -= (m_speed * m_direction);
	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "moveBackward()" << std::endl;
}

void Pilotview::moveLeft(){
		// Rotates a copy of m_direction about 90 degrees
		glm::vec4 directionCopy = m_direction;
		glm::mat4 rotateLeft = glm::rotate(glm::mat4(1), 90.0f, glm::vec3(0, 1, 0));
		directionCopy = rotateLeft*directionCopy;
		// Moves right on the axis, which is orthogonal to the direction
		m_position += (m_speed * directionCopy);
		m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));
	
		std::cout << "moveLeft()" << std::endl;
	}
	
void Pilotview::moveRight(){
		// Rotates a copy of m_direction about 270 degrees
		glm::vec4 directionCopy = m_direction;
		glm::mat4 rotateLeft = glm::rotate(glm::mat4(1), 270.0f, glm::vec3(0, 1, 0));
		directionCopy = rotateLeft*directionCopy;
		// Moves left on the axis, which is orthogonal to the direction
		m_position += (m_speed * directionCopy);
		m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

		std::cout << "moveRight()" << std::endl;
	}

void Pilotview::moveUp(){
	m_oldY = (-m_speed + m_oldY)*m_sensitivity;
	m_theta -= m_speed;
	if (m_theta < 0.01f) m_theta = 0.01f;
	else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

	m_direction.x = sin(m_theta) * cos(m_phi);
	m_direction.y = cos(m_theta);
	m_direction.z = -sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "moveUp()" << std::endl;
}

void Pilotview::moveDown(){
	m_oldY = (m_speed + m_oldY)*m_sensitivity;
	m_theta += m_speed;
	if (m_theta < 0.01f) m_theta = 0.01f;
	else if (m_theta > glm::pi<float>() - 0.01f) m_theta = glm::pi<float>() - 0.01f;

	m_direction.x = sin(m_theta) * cos(m_phi);
	m_direction.y = cos(m_theta);
	m_direction.z = -sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "moveDown()" << std::endl;
}

void Pilotview::moveDiagonalFwdL(){
	moveForward();
	moveLeft();
	std::cout << "moveDiagonalFwdL()" << std::endl;
}

void Pilotview::moveDiagonalFwdR(){
	moveForward();
	moveRight();

	std::cout << "moveDiagonalFwdR()" << std::endl;
}

void Pilotview::moveDiagonalBwdL(){
	moveBackward();
	moveLeft();

	std::cout << "moveDiagonalBwdL()" << std::endl;
}

void Pilotview::moveDiagonalBwdR(){
	moveBackward();
	moveRight();

	std::cout << "moveDiagonalBwdR()" << std::endl;
}

void Pilotview::turnLeft(){
	m_oldX = (m_speed + m_oldX)*m_sensitivity;
	m_phi += m_speed;
	if (m_phi < 0) m_phi += 2 * glm::pi<float>();
	else if (m_phi > 2 * glm::pi<float>()) m_phi -= 2 * glm::pi<float>();

	m_direction.x = sin(m_theta) * cos(m_phi);
	m_direction.y = cos(m_theta);
	m_direction.z = -sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "turnLeft()" << std::endl;
}


void Pilotview::turnRight(){
	m_oldX = (-m_speed + m_oldX)*m_sensitivity;
	m_phi -= m_speed;
	if (m_phi < 0) m_phi += 2 * glm::pi<float>();
	else if (m_phi > 2 * glm::pi<float>()) m_phi -= 2 * glm::pi<float>();

	m_direction.x = sin(m_theta) * cos(m_phi);
	m_direction.y = cos(m_theta);
	m_direction.z = -sin(m_theta) * sin(m_phi);

	m_viewMatrix = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + glm::vec3(m_direction), glm::vec3(m_up));

	std::cout << "turnRight()" << std::endl;
}
