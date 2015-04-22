#include "GeKo_Gameplay/Object/Geko.h"

Geko::Geko(std::string gekoName){
	Geko(gekoName, glm::vec3(0.0f));
}

Geko::Geko(std::string gekoName, glm::vec3 spawnPoint){

	m_type = ObjectType::PLAYER;
	m_class = ClassType::PLAYER;

	m_movementVector = glm::vec3(0.0f);
	m_viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	m_speed = 8.0f;

	m_spawnPoint = spawnPoint;
	m_position = spawnPoint;
	m_name = gekoName;

	m_hunger = 10;
	m_hungerMax = 10;
	m_health = 10;
	m_health = 10;
	m_strength = 1;

	m_inventory = new Inventory();
}

Geko::Geko(){}

Geko::~Geko(){
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

void Geko::update(float deltaTime)
{
	updateStates();

	if (glm::length(m_movementVector))
	{
		glm::vec2 newPos = glm::vec2(m_position.x, m_position.z) + glm::normalize(glm::vec2(m_movementVector.x, m_movementVector.z))* m_speed * deltaTime;
		move(glm::vec3(newPos.x, m_position.y, newPos.y));
		notify(*this, Object_Event::OBJECT_MOVED);
	}
	else
	{
		notify(*this, Object_Event::OBJECT_STOPPED);
	}
	m_movementVector = glm::vec3(0.0f);
}

glm::vec3 Geko::getPosition()
{
	return m_position;
}