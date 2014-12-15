#include <GeKo_Gameplay/AI/Path.h>

Path::Path(int timeToTravel, GraphNode* endNode)
{
	m_timeToTravel = timeToTravel;
	m_endNode = endNode;
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