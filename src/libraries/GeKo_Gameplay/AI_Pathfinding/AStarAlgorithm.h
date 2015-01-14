#pragma once
# include <GeKo_Gameplay/AI_Pathfinding/Algorithm.h>
#include <GeKo_Gameplay/AI_Pathfinding/AStarNode.h>
#include <iostream>


class AStarAlgorithm : public Algorithm<AStarNode>
{
public:

	AStarAlgorithm(std::string name);
	~AStarAlgorithm();

	 AStarNode* startAlgorithm (AStarNode* startNode, AStarNode* endNode);

};

