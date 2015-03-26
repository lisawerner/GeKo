#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Goal.h"
#include "GeKo_Gameplay/Object/AI.h"

class Goal_Escort : public Goal
{
public: 
	Goal_Escort(int id);
	Goal_Escort();
	~Goal_Escort();

	void setAiId(int id);
	void setPosition(glm::vec3 m_position);
	void completed();


	protected:
		int m_AiId;
		glm::vec3 m_position;
};