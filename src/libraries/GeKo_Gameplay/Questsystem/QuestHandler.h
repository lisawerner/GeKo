#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Quest.h"
#include "GeKo_Gameplay/Questsystem/QuestGraph.h"

#include "Goal.h"

class QuestHandler
{
public: 
	QuestHandler();
	~QuestHandler();

	std::vector<Quest*> getQuests();
	void addQuest(Quest* q);

	std::vector<Quest*> getActiveAndNotFinished();
	//Impliziert Active and not finished!!!
	std::vector<Goal*> getQuests(GoalType gType);

	void setGraph(QuestGraph* g);
	QuestGraph* getGraph();

protected:
	std::vector<Quest*> m_questLog;
	QuestGraph* m_questGraph;
};