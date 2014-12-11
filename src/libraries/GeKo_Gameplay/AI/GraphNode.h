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
	
protected:
	std::vector<Path*> m_paths;
	float m_distanceToGoal;
	std::string m_name;
	
};