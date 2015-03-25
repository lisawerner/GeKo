#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Goal.h"
#include "GeKo_Gameplay/Item/Item.h"


class Goal_Collect : public Goal
{
public: 
	Goal_Collect(int id);
	Goal_Collect();
	~Goal_Collect();

	void setActualCount(int actualC);
	void setGoalCount(int goalC);
	ItemType getItemType();
	void setItemType(ItemType iType);
	void increase();


	protected:
		int m_actualCount;
		int m_goalCount;
		ItemType m_itemType;
};