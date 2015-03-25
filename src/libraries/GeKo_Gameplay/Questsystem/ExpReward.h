#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>
#include  <GeKo_Gameplay/Questsystem/Reward.h>



class ExpReward : public Reward
{
public: 
	ExpReward(int id);
	ExpReward();
	~ExpReward();

	void setExp(float exp);

};