#include "Camera.h"

Camera::Camera()
{
	setOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 0.01f, 1.0f);
	m_useOrtho = false;
	//m_position = glm::vec4(0.0, 0.0, 10.0, 1.0);
}

Camera::Camera(std::string cameraName)
{
	m_name = cameraName;
	setOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 0.01f, 1.0f);
	m_useOrtho = false;
}
Camera::~Camera()
{
}

void Camera::getView(glm::mat4 *view)
{
	*view = m_viewmatrix;
}

void Camera::getPerspective(glm::mat4 *perspective)
{
	*perspective = m_perspective;
}

void Camera::getOrtho(glm::mat4 *ortho)
{
	*ortho = m_ortho;
}

void Camera::setOrtho(float left, float right, float bottom, float top, float near, float far)
{

	m_ortho = glm::ortho(left, right, bottom, top, near, far);
	m_useOrtho = true;
}

void Camera::getProjection(glm::mat4 *projection)
{
	if (m_useOrtho)
		*projection = m_ortho;
	else
		*projection = m_perspective;
}

void Camera::setNearFar(float near, float far)
{
	m_znear = near;
	m_zfar = far;
	m_perspective = glm::perspective(m_fov, m_width / (float)m_height, m_znear, m_zfar);
	m_useOrtho = false;
}

void Camera::getNearFar(float *near, float *far)
{
	*near = m_znear;
	*far = m_zfar;
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



void Camera::moveForward(){
	m_position.z -= 0.1f;
	std::cout << "move fwd " << m_position.z << std::endl;
}


void Camera::moveBackward(){
	m_position.z += 0.1f;
	std::cout << "move bwd " << m_position.z << std::endl;
}

std::string Camera::getName()
{
	return m_name;
}

void Camera::setName(std::string n){
	m_name = n;
}