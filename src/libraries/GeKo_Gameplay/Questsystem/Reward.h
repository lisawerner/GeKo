#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include  <GeKo_Gameplay/Item/Item.h>

enum Type {
	REWARD, REWARD_ITEM, REWARD_EXP
};

class Reward 
{
public: 
	Reward(int id);
	Reward();
	~Reward();

	int getId();
	void setID(int id);

	float getExp();

	std::vector<Item*>* getItemList();

	Type getType();

	protected:
		int m_id;

		float m_exp;

		std::vector<Item*> m_itemList;

		Type m_type;
};