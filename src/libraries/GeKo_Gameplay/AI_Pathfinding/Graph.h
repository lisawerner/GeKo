#pragma once
#include <GeKo_Gameplay/AI_Pathfinding/GraphNode.h>
#include <vector>

/** The Graph-class provides a "bucket" for GraphNodes, which cann be added to the vector-list ot the Graph. A Graph represents one closed path-system on which a AI-Unit can run.
For example one Graph could represent the search for food or the area, which the AI should protect.*/
class Graph 
{
public: 
	Graph();
	~Graph();
	
	///Adds a GraphNode-Object to the vector-list m_nodes
	/**/
	 void addGraphNode(GraphNode* node);
	 
	 ///Returns the vector-list m_nodes completely
	 /**/
	 std::vector<GraphNode*>* getGraph();
	
protected:
	  std::vector<GraphNode*> m_nodes;
	 
};