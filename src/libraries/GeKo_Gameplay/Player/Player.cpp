#include <GeKo_Gameplay/Player/Player.h>

Player::Player(std::string playerName)
{
	m_spawnPoint = glm::vec3(0.0f);
	m_currentPosition = m_spawnPoint;
	m_playerName = playerName;
}

Player::Player(glm::vec3 spawnPoint, std::string playerName)
{
	m_spawnPoint = spawnPoint;
	m_currentPosition = m_spawnPoint;
	m_playerName = playerName;
}

Player::~Player()
{

}

std::string Player::getName()
{
	return m_playerName;
}

glm::vec3 Player::getSpawnPoint()
{
	return m_spawnPoint;
}

glm::vec3 Player::getCurrentPosition()
{
	return m_currentPosition;
}

void Player::changePosition(glm::vec3 newPosition)
{
	m_currentPosition = newPosition;
}

void Player::setNode(Node* geometryNode)
{
	m_geometryPlayer = geometryNode;
}