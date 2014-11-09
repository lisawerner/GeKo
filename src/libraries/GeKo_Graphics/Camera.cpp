#include <GeKo_Graphics/Camera.h>

Camera::Camera()
{
	m_isActive = false;
}

Camera::Camera(std::string cameraName)
{
	m_cameraName = cameraName;
	m_isActive = false;
}

Camera::~Camera()
{

}

bool Camera::isActive()
{
	return m_isActive;
}

void Camera::setActive()
{
	m_isActive = true;
}

void Camera::setNotActive()
{
	m_isActive = false;
}

std::string Camera::getCameraName()
{
	return m_cameraName;
}