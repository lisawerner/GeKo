#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Item.h"
#include "ItemType.h"



class Inventory
{
public: 
	Inventory();
	~Inventory();

	void addItem(Item* item);
	void addItem(ItemType typeId);
	void addItem(Item* item, int count);
	void print();
	ItemType getItemTypeIdAt(int position);
	//Delete: Löscht ALLE Items von einem Typ
	void deleteItem(int position);
	void deleteItem(Item* item);
	//Reduce: Löscht nur EIN Item von einem Typ
	void reduceItem(int position, int count);
	void reduceItem(ItemType typeId, int count);
	void clearInventory();
	//Gibt die Anzahl der Items zurück, die von dem ItemType vorhanden sind
	int countItem(ItemType typeId);

	protected:
		int m_id;
		//pair of int: count and int: itemTypID
		std::vector<std::pair<int, ItemType>> m_content;
	
};