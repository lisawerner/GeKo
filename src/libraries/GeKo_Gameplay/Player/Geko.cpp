#include <GeKo_Gameplay/Player/Geko.h>

Geko::Geko(std::string gekoName)
	: Player(gekoName)
{
	m_movementVector = glm::vec3(0.0f);
	m_viewDirection = glm::vec3(1.0f, 0.0f, 0.0f);

	m_speed = 8.0f;
}

Geko::Geko(std::string gekoName, glm::vec3 spawnPoint)
	: Player(spawnPoint, gekoName)
{
	m_movementVector = glm::vec3(0.0f);
	m_viewDirection = glm::vec3(1.0f, 0.0f, 0.0f);

	m_speed = 8.0f;
}

Geko::~Geko()
{

}

void Geko::moveForward()
{
	m_movementVector += m_viewDirection;
}

void Geko::moveBackward()
{
	m_movementVector -= m_viewDirection;
}

void Geko::moveRight()
{
	m_movementVector += glm::cross(m_viewDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Geko::moveLeft()
{
	m_movementVector -= glm::cross(m_viewDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Geko::rotateView(float leftRight, float upDown)
{
	m_viewDirection = glm::rotate(m_viewDirection, upDown, glm::cross(m_viewDirection, glm::vec3(0.0f, -1.0f, 0.0f)));
	m_viewDirection = glm::rotate(m_viewDirection, leftRight, glm::vec3(0.0f, -1.0f, 0.0f));
	m_viewDirection.y = glm::clamp(m_viewDirection.y, -0.5f, 0.5f);
}

void Geko::update(float deltaTime)
{

	if (glm::length(m_movementVector))
	{
		glm::vec2 newPos = glm::vec2(m_currentPosition.x, m_currentPosition.z) + glm::normalize(glm::vec2(m_movementVector.x, m_movementVector.z))* m_speed * deltaTime;
		changePosition(glm::vec3(newPos.x, m_currentPosition.y, newPos.y));
	}
	m_movementVector = glm::vec3(0.0f);

	glm::mat4 modelMatrix = glm::mat4(1);
	m_geometryPlayer->setModelMatrix(glm::translate(modelMatrix, m_currentPosition));

	glm::vec3 axisX = m_viewDirection;
	glm::vec3 axisZ = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), axisX));
	glm::vec3 axisY = glm::normalize(glm::cross(axisX, axisZ));

	m_geometryPlayer->setModelMatrix(m_geometryPlayer->getModelMatrix() * glm::mat4(
		axisX.x, axisX.y, axisX.z, 0,
		axisY.x, axisY.y, axisY.z, 0,
		axisZ.x, axisZ.y, axisZ.z, 0,
		0, 0, 0, 1));
}