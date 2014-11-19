#include "Camera.h"

Camera::Camera()
{
	m_position = glm::vec4(0.0, 0.0, 10.0, 1.0);
}

Camera::Camera(std::string cameraName)
{
	m_name = cameraName;
	m_position = glm::vec4(0.0, 0.0, 10.0, 1.0);
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

void Camera::moveForward(){}
void Camera::moveBackward(){}
void Camera::moveLeft(){}
void Camera::moveRight(){}
void Camera::moveUp(){}
void Camera::moveDown(){}