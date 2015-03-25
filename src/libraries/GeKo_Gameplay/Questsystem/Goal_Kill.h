#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Goal.h"
#include "GeKo_Gameplay/Object/AI.h"
#include "GeKo_Gameplay/Object/ObjectType.h"


class Goal_Kill : public Goal
{
public: 
	Goal_Kill(int id);
	Goal_Kill();
	~Goal_Kill();

	void setActualCount(int actualC);
	void setGoalCount(int goalC);
	void setAiTypeId(ObjectType id);
	void increase();

	protected:
		int m_actualCount;
		int m_goalCount;
		ObjectType m_AiTypeId;
};