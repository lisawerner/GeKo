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

	 ///Returns the fastest path from Start to Goal
	 /**In the vector will be Nodes, the startNode at the back of the vector list!*/
	std::vector<AStarNode*>* startAlgorithm2(AStarNode* startNode, AStarNode* endNode, std::vector<AStarNode*> &path);

private:
	std::vector<AStarNode*> m_path;

//	AStarNode* copyNode;

};

