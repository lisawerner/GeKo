#pragma once
#include "GeKo_Gameplay/Object/Object.h"
#include "GeKo_Gameplay/Object/Ai.h"
#include "GeKo_Graphics/Geometry/AntMesh.h"
#include "GeKo_Graphics/Scenegraph/Node.h"
#include "GeKo_Graphics/Material/Texture.h"
#include "GeKo_Graphics/Observer/ObjectObserver.h"
#include "GeKo_Gameplay/AI_Decisiontree/DecisionTree.h"
#include "GeKo_Gameplay/AI_Pathfinding/Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <vector>

class Anthome : public Object{
public :
	Anthome();
	Anthome(glm::vec3 position,AntMesh antMesh, DecisionTree *aggressiveDecisionTree, Graph<AStarNode, AStarAlgorithm> *aggressiveGraph, Texture *tex);
	~Anthome();
	void initAnts(ObjectObserver *objectObserver);
	void updateAnts();
	void addAntsToSceneGraph(Node *rootNode);
	//void putObserver();
protected :
	std::vector<Node*> m_ants;
	glm::vec3 m_position;
	AntMesh m_antMesh;
	Texture *m_antTexture;
	Graph<AStarNode, AStarAlgorithm> *m_aggressiveGraph;
	DecisionTree *m_aggressiveDecisionTree;
	int m_numberOfGuards;
	int m_numberOfWorkers;
};