#pragma once 
#include <GeKo_Gameplay/AI/GraphNode.h>

class Path 
{
public: 
	Path(int timeToTravel, GraphNode* endNode);
	~Path();
	
	int getTimeToTravel();
	GraphNode* getEndNode();
	
protected:
	int m_timeToTravel;
	GraphNode* m_endNode;

};