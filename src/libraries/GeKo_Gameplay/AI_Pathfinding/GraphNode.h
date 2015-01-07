#pragma once
#include <string>
#include <vector>
#include <glm/ext.hpp>

class Path;

/** A GraphNode-class provides the possibility to create waypoints, which can be used by AI-Units and Pathfinding algorithms.
Every Node has a Name and knows its distance to a goal-Waypoint. It knows, which paths are connected with it and will recognize when a AI-Unit passes over it.
Over all it has a position on the playground.*/
class GraphNode
{

public: 
	///Every GraphNode needs a name
	/**/
	GraphNode(std::string name);
	~GraphNode();
	
	///Adds a Path to the m_paths vector-list
	/**/
	void addPath(Path* path);
	///Sets the m_distanceToGoal to distance
	/**/
	void setDistanceToGoal(float distance);
	///Returns m_distanceToGoal
	/**/
	float getDistanceToGoal();
	
	///Returns all the Paths of m_paths list
	/**/
	std::vector<Path*>* getPaths();
	///Returns the Name of the Node
	/**/
	std::string getName();

	///Returns m_distanceTravelled
	/**/
	float getDistanceTravelled();
	///Sets m_distanceTravelled to distance
	/**/
	void setDistanceTravelled(float distance);

	///Sets m_wasVisitedBy to visitor
	/**/
	void setVisitor(GraphNode* visitor);
	///Return m_wasVisitedBy
	/**/
	GraphNode* getVisitor();

	///Sets m_name to name
	/**/
	void setName(std::string name);
	///Sets m_paths to paths
	/**/
	void setPathList(std::vector<Path*> paths);

	///Sets m_temporaryTravelled to temp
	/**/
	void setTemporary(float temp);
	///Returns m_temporaryTravelled 
	/**/
	float getTemporary();

	///Sets m_position to position
	/**/
	void setPosition(glm::vec3 position);
	///Returns the position on the playground
	/**/
	glm::vec3 getPosition();
	
protected:
	std::vector<Path*> m_paths;
	float m_distanceToGoal;
	std::string m_name;

	float m_distanceTravelled;
	float m_temporaryTravelled;

	GraphNode* m_wasVisitedBy;

	glm::vec3 m_position;
	float posX;
	float posY;
	float posZ;
	
};