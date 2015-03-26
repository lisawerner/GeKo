#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "GeKo_Gameplay/Questsystem/QuestGraphNode.h"
#include "GeKo_Gameplay/Questsystem/Goal_Collect.h"

class QuestGraph 
{
public: 
	QuestGraph();
	~QuestGraph();

	std::vector<QuestGraphNode*> getNodes();
	void addNode(QuestGraphNode* n);

	QuestGraph* setExampleGraph();

	QuestGraphNode* search(Quest* quest);

	bool hasChildren();

protected:
	std::vector<QuestGraphNode*> m_nodes;

	bool m_hasChildren;
		
};