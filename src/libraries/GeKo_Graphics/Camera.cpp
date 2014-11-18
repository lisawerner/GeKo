#include "Camera.h"

Camera::Camera()
{
	m_position = glm::vec4(0.0, 0.0, 10.0, 1.0);
}

Camera::Camera(std::string cameraName)
{
	m_name = cameraName;
	//m_position = glm::vec4(0.0, 0.0, 10.0, 1.0);
}
Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}

void Camera::setNearFar(float near, float far)
{
	m_near = near;
	m_far = far;
	m_projectionMatrix = glm::perspective(m_fov, m_width / (float)m_height, m_near, m_far);
}

float Camera::getNear(){
	return m_near;
}
float Camera::getFar(){
	return m_far;
}

void Camera::setWidthHeight(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Camera::setPosition(glm::vec4 position){
	m_position = position;
}

glm::vec4 Camera::getPosition(){
	return m_position;
}

std::string Camera::getName()
{
	return m_name;
}

void Camera::setName(std::string n){
	m_name = n;
}

void Camera::moveForward(){
	m_position.z -= 0.1f;
	std::cout << "Cam move fwd z " << m_position.z << std::endl;
	//fehlt aktualisierung der viewmatrix
}


void Camera::moveBackward(){
	m_position.z += 0.1f;
	std::cout << "Cam move bwd z " << m_position.z << std::endl;
	//fehlt aktualisierung der viewmatrix
}


void Camera::moveAroundLeft(){
	std::cout << "Cam move rndL x " << m_position.x << " z " << m_position.z << std::endl;
}

void Camera::moveAroundRight(){
	std::cout << "Cam move rndR x " << m_position.x << " z " << m_position.z << std::endl;
}
void Camera::moveOverForward(){
	std::cout << "Cam move oFwd y " << m_position.y << " z " << m_position.z << std::endl;
}
void Camera::moveOverBackward(){
	std::cout << "Cam move oBwd y " << m_position.y << " z " << m_position.z << std::endl;
}