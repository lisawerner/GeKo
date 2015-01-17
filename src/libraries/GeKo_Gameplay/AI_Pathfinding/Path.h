#pragma once 
//#include <GeKo_Gameplay/AI_Pathfinding/GraphNode.h>
//#include <GeKo_Gameplay/AI_Pathfinding/AStarNode.h>

/** The Path-Class provides the possibility to connect waypoints, referred to as endNode and startNode. Each Path has a variable which determines how long it will take to
travel this path!*/
 template<class T>

class Path 
{
public: 
	///Each Path needs a travel-time, a start- and end point
	/**/
	Path(int timeToTravel, T* startNode, T* endNode)
	{
		m_timeToTravel = timeToTravel;
		m_endNode = endNode;
		m_startNode = startNode;
	}
	~Path(){};
	
	///Returns m_timeToTravel
	/**/
	int getTimeToTravel(){ 
		return m_timeToTravel;}
	
	///Returns m_endNode
	/**/
	T* getEndNode(){
		return m_endNode;
	}

	///Returns m_startNode
	/**/
	T* getStartNode(){
		return m_startNode;
	}

	
protected:
	int m_timeToTravel;
	T* m_endNode;
	T* m_startNode	;

};