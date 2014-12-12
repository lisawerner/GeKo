#include <GeKo_Gameplay/AI/GraphNode.h>

GraphNode::GraphNode(std::string name)
{
	m_name = name;
}
GraphNode::~GraphNode()
{

}

void GraphNode::addPath(Path* path)
{
	m_paths.push_back(path);
}

void GraphNode::setDistanceToGoal(float distance)
{
	m_distanceToGoal = distance;
}

float GraphNode::getDistanceToGoal()
{
	return m_distanceToGoal;
}

std::vector<Path*>* GraphNode::getPaths()
{
	return &m_paths;
}

std::string GraphNode::getName()
{
	return m_name;
}