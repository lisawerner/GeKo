#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>
#include  <GeKo_Gameplay/Questsystem/Reward.h>


class ItemReward: public Reward
{
public: 
	ItemReward(int id);
	ItemReward();
	~ItemReward();

	void addItem(Item* item);



protected:
	
};