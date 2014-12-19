#pragma once
#include <string>
#include <vector>

class Path;

class GraphNode
{

public: 
	GraphNode(std::string name);
	~GraphNode();
	
	void addPath(Path* path);
	void setDistanceToGoal(float distance);
	float getDistanceToGoal();
	
	std::vector<Path*>* getPaths();
	std::string getName();

	float getDistanceTravelled();
	void setDistanceTravelled(float distance);

	void setVisitor(GraphNode* visitor);
	GraphNode* getVisitor();

	void setName(std::string name);
	void setPathList(std::vector<Path*> paths);

	void setTemporary(float temp);
	float getTemporary();
	
protected:
	std::vector<Path*> m_paths;
	float m_distanceToGoal;
	std::string m_name;

	float m_distanceTravelled;
	float m_temporaryTravelled;

	GraphNode* m_wasVisitedBy;
	
};