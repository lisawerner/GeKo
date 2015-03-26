#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Goal.h"

class Goal_Travel : public Goal
{
public: 
	Goal_Travel(int id);
	Goal_Travel();
	~Goal_Travel();

	void setPosition(glm::vec3 m_position);
	void completed();


	protected:
		glm::vec3 m_position;
};