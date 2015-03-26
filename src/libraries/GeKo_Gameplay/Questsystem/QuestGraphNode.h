#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "GeKo_Gameplay/Questsystem/Quest.h"

class QuestGraphNode
{
public: 
	QuestGraphNode();
	~QuestGraphNode();

	void setParent(QuestGraphNode* p);
	QuestGraphNode* getParent();

	void addChild(QuestGraphNode* c);
	std::vector<QuestGraphNode*> getChildren();

	Quest* getQuest();
	void setQuest(Quest* q);

protected:
	QuestGraphNode* m_parent;
	std::vector<QuestGraphNode*> m_children;

	Quest* m_quest;

};