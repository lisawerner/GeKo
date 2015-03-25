#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "GoalType.h"
#include <GeKo_Gameplay/Item/ItemType.h>
#include <GeKo_Gameplay/Object/ObjectType.h>
#include <Geko_Graphics/Observer/Subject.h>

class Goal : public Subject<Goal, Quest_Event>
{
public: 
	Goal(int id);
	Goal();
	~Goal();

	int getId();

	GoalType getGoalType();

	bool getFinished();

	 virtual void setActualCount(int actualC);

	 virtual void setGoalCount(int goaldC);

	 virtual ItemType getItemType();
	virtual void setItemType(ItemType iType);
	virtual void increase();

	virtual void setAiTypeId(ObjectType id);

	virtual void setAiID(int id);
	virtual void setPosition(glm::vec3 m_position);



	protected:
		int m_id;
		bool m_finished;
		GoalType m_goalType;

};