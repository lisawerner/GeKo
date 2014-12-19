#include <GeKo_Gameplay/AI_Pathfinding/Graph.h>

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addGraphNode(GraphNode* node)
{
	m_nodes.push_back(node);
}

std::vector<GraphNode*>* Graph::getGraph()
{
	return &m_nodes;
}