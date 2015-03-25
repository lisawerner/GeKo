#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "GeKo_Graphics/Observer/Subject.h"
#include "Goal.h"
#include "GeKo_Gameplay/Questsystem/Reward.h"

class Quest: public Subject<Quest, Quest_Event>
{
public: 
	Quest(int id);
	Quest();
	~Quest();

	std::vector<Goal*> getGoals();
	void addGoal(Goal* g);

	std::vector<Reward*> getRewards();
	void addReward(Reward* r);

	bool getActive();
	void setActive(bool activity);

	void isFinished();
	bool getFinished();

	int getID();

protected:
	//Quest* m_next;
	std::vector<Goal*> m_goals;
	std::vector<Reward*> m_rewards;
	bool m_active;
	int m_id;
	bool m_finished;
	std::string m_text;
	
};