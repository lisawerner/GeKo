#pragma once 
#include <GeKo_Gameplay/AI_Pathfinding/GraphNode.h>

class Path 
{
public: 
	Path(int timeToTravel, GraphNode* startNode, GraphNode* endNode);
	~Path();
	
	int getTimeToTravel();
	GraphNode* getEndNode();

	GraphNode* getStartNode();

	
protected:
	int m_timeToTravel;
	GraphNode* m_endNode;
	GraphNode* m_startNode;

};