#include <GeKo_Gameplay/Player/GekoAI.h>

GekoAI::GekoAI(std::string gekoName)
	: Player(gekoName)
{
	m_movementVector = glm::vec3(0.0f);
	m_viewDirection = glm::vec3(1.0f, 0.0f, 0.0f);

	m_speed = 8.0f;

	m_algorithm = new AStarAlgorithm("pathfinding");
}

GekoAI::GekoAI(std::string gekoName, glm::vec3 spawnPoint)
	: Player(spawnPoint, gekoName)
{
	m_movementVector = glm::vec3(0.0f);
	m_viewDirection = glm::vec3(1.0f, 0.0f, 0.0f);

	m_speed = 1.0f;
}

GekoAI::~GekoAI()
{

}

void GekoAI::moveForward()
{
	m_movementVector += m_viewDirection;
}

void GekoAI::moveBackward()
{
	m_movementVector -= m_viewDirection;
}

void GekoAI::moveRight()
{
	m_movementVector += glm::cross(m_viewDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}

void GekoAI::moveLeft()
{
	m_movementVector -= glm::cross(m_viewDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}

void GekoAI::rotateView(float leftRight, float upDown)
{
	m_viewDirection = glm::rotate(m_viewDirection, upDown, glm::cross(m_viewDirection, glm::vec3(0.0f, -1.0f, 0.0f)));
	m_viewDirection = glm::rotate(m_viewDirection, leftRight, glm::vec3(0.0f, -1.0f, 0.0f));
	m_viewDirection.y = glm::clamp(m_viewDirection.y, -0.5f, 0.5f);
}

void GekoAI::update(float deltaTime)
{

	if (abs(m_currentPosition.x) < abs(m_endNode->getPosition().x))
	{
		glm::vec3 differenceTMP = m_nextPosition->getPosition() - m_currentPosition;
		if (abs(m_currentPosition.x) < abs(m_nextPosition->getPosition().x ) || abs(m_currentPosition.z) < abs(m_nextPosition->getPosition().z))
		{
			if (differenceTMP.x != 0 && differenceTMP.x > 0)
			{
				changePosition(m_currentPosition + glm::vec3(m_speed, 0.0, 0.0) * deltaTime);
				m_geometryPlayer->setModelMatrix(glm::translate(glm::mat4(1), m_currentPosition));
			}
			if (differenceTMP.z != 0 &&  differenceTMP.z > 0)
			{
				changePosition(m_currentPosition + glm::vec3(0.0, 0.0, m_speed) * deltaTime);
				m_geometryPlayer->setModelMatrix(glm::translate(glm::mat4(1), m_currentPosition));
			}
			if (differenceTMP.x != 0 && differenceTMP.x < 0)
			{
				changePosition(m_currentPosition + glm::vec3(-m_speed, 0.0, 0.0) * deltaTime);
				m_geometryPlayer->setModelMatrix(glm::translate(glm::mat4(1), m_currentPosition));
			}
			if (differenceTMP.z != 0 && differenceTMP.z < 0)
			{
				changePosition(m_currentPosition + glm::vec3(0.0, 0.0, -m_speed) * deltaTime);
				m_geometryPlayer->setModelMatrix(glm::translate(glm::mat4(1), m_currentPosition));
			}
		}
		else{
			m_lastVisited = m_nextPosition;
			m_nextPosition = m_algorithm->startAlgorithm(m_lastVisited, m_endNode);
		}
	}


	/*if (glm::length(m_movementVector))
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
		0, 0, 0, 1));*/
}


void GekoAI::setStartAndEndNode(AStarNode* start, AStarNode* end)
{
	m_startNode = start;
	m_currentPosition = m_startNode->getPosition();
	m_geometryPlayer->setModelMatrix(glm::translate(glm::mat4(1.0), m_currentPosition));

	m_endNode = end;

	m_lastVisited = m_startNode;

	m_nextPosition = m_algorithm->startAlgorithm(m_lastVisited, m_endNode);
}