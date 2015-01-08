#include <GeKo_Gameplay/AI_Pathfinding/GraphNode.h>

GraphNode::GraphNode(std::string name)
{
	m_name = name;
	m_distanceToGoal = 0;
	m_distanceTravelled = 0;
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

float GraphNode::getDistanceTravelled()
{
	return m_distanceTravelled;
}

void GraphNode::setDistanceTravelled(float distance)
{
	m_distanceTravelled += distance;
}

void GraphNode::setVisitor(GraphNode* visitor)
{
	m_wasVisitedBy = visitor;
}

GraphNode* GraphNode::getVisitor()
{
	return m_wasVisitedBy;
}


void GraphNode::setName(std::string name)
{
	m_name = name;
}

void GraphNode::setPathList(std::vector<Path*> paths)
{
	m_paths = paths;
}

void GraphNode::setTemporary(float temp)
{
	m_temporaryTravelled = temp;
}

float GraphNode::getTemporary()
{
	return m_temporaryTravelled;
}

void GraphNode::setPosition(glm::vec3 position)
{
	posX = position.x;
	posY = position.y;
	posZ = position.z;

	m_position = position;
}

glm::vec3 GraphNode::getPosition()
{
	return m_position;
}