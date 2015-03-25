#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <glm/ext.hpp>
#include <GeKo_Gameplay/AI_Pathfinding/GraphNode.h>

//class Path;

/** A GraphNode-class provides the possibility to create waypoints, which can be used by AI-Units and Pathfinding algorithms.
Every Node has a Name and knows its distance to a goal-Waypoint. It knows, which paths are connected with it and will recognize when a AI-Unit passes over it.
Over all it has a position on the playground.*/
class AStarNode : public GraphNode<AStarNode>
{

public: 
	///Every GraphNode needs a name
	/**/
	AStarNode(std::string name, AStarNode *defaultNode);
	AStarNode();
	AStarNode(std::string name, AStarNode *defaultNode, glm::vec3 position, GraphNodeType type);
	~AStarNode();
	
	///Sets the m_distanceToGoal to distance
	/**/
	void setDistanceToGoal(float distance);
	///Returns m_distanceToGoal
	/**/
	float getDistanceToGoal();

	///Returns m_distanceTravelled
	/**/
	float getDistanceTravelled();
	///Sets m_distanceTravelled to distance
	/**/
	void setDistanceTravelled(float distance);

	///Sets m_wasVisitedBy to visitor
	/**/
	void setVisitor(AStarNode* visitor);
	///Return m_wasVisitedBy
	/**/
	AStarNode* getVisitor();

	///Sets m_temporaryTravelled to temp
	/**/
	void setTemporary(float temp);
	///Returns m_temporaryTravelled 
	/**/
	float getTemporary();

	AStarNode* getDefault();
	void setDefault(AStarNode* d);
	
protected:
	float m_distanceToGoal;

	float m_distanceTravelled;
	float m_temporaryTravelled;

	AStarNode* m_wasVisitedBy;

	AStarNode* m_default;
	
};