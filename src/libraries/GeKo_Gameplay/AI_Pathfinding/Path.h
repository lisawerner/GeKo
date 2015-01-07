#pragma once 
#include <GeKo_Gameplay/AI_Pathfinding/GraphNode.h>

/** The Path-Class provides the possibility to connect waypoints, referred to as endNode and startNode. Each Path has a variable which determines how long it will take to
travel this path!*/
class Path 
{
public: 
	///Each Path needs a travel-time, a start- and end point
	/**/
	Path(int timeToTravel, GraphNode* startNode, GraphNode* endNode);
	~Path();
	
	///Returns m_timeToTravel
	/**/
	int getTimeToTravel();
	
	///Returns m_endNode
	/**/
	GraphNode* getEndNode();

	///Returns m_startNode
	/**/
	GraphNode* getStartNode();

	
protected:
	int m_timeToTravel;
	GraphNode* m_endNode;
	GraphNode* m_startNode;

};