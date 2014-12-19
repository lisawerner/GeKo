#include <GeKo_Gameplay/AI_Pathfinding/Path.h>

Path::Path(int timeToTravel, GraphNode* startNode, GraphNode* endNode)
{
	m_timeToTravel = timeToTravel;
	m_endNode = endNode;
	m_startNode = startNode;
}

Path::~Path()
{

}

int Path::getTimeToTravel()
{
	return m_timeToTravel;
}

GraphNode* Path::getEndNode()
{
	return m_endNode;
}

GraphNode* Path::getStartNode()
{
	return m_startNode;
}