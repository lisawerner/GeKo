#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "GeKo_Gameplay/AI_Pathfinding/Graph.h"
#include "GeKo_Gameplay/AI_Pathfinding/AStarNode.h"
#include "GeKo_Gameplay/AI_Pathfinding/AStarAlgorithm.h"

#include "GeKo_Graphics/Scenegraph/BoundingSphere.h"

#include "GeKo_Gameplay/AI_Decisiontree/DecisionTree.h"
#include "GeKo_Gameplay/AI_Decisiontree/TreeOutput.h"

#include "Object.h"
#include "States.h"

class AI : public Object, public Subject<AI, Object_Event>
{
public: 
	//Eine Position: Objekt startet zu Hause! (Weiterer Konstrutkor, falls Objekt woanders starten soll)
	//AI(DecisionTree* decisionTree, AStarNode* defaultASNode, Node* defaultGeometry);
	AI();
	~AI();


	//GraphNode<AStarNode>* getPosHome();
	AStarNode* getPosHome();
	//void setPosHome(GraphNode<AStarNode>* pos);
	void setPosHome(AStarNode* pos);

	Graph<AStarNode, AStarAlgorithm>* getGraph();
	void setGraph(Graph<AStarNode, AStarAlgorithm>* graph);

	DecisionTree* getDecisionTree();
	void setDecisionTree(DecisionTree* tree);

	void addFoodNodes();

	//Per Frame
	void update();

	//Move Object on Terrain
	void move();

	//Methode: Update Fear
	//Abhängig von Sichtfeld oder so

	//Methode für jeden State, falls Entscheidung da was ändernt

	void viewArea(bool state);

	//Diese Methode prüft mit dem Abstand Epsilon, ob p1 "sehr Nah" an p2 liegt
	bool checkPosition(glm::vec3 p1, glm::vec3 p2);

	AStarNode* nearestFoodNode();

	float getViewRadius();

	void decide();
	void decide2();

	//void updateGraph(GraphNodeType &lastNodeType);
	void updatePath();
	void updatePathPlayer();
	void updatePathPatrol();

	AStarNode* nextNodeOnPatrol();

	void setAntAfraid();
	void setAntAggressiv();
	
protected:
	float m_epsilon;

	//Letztes Ziel
	AStarNode* m_lastTarget;
	//Letztes Ziel vor dem Kampf
	AStarNode* m_lastTargetOnGraph;
	//Hauptziel
	AStarNode* m_target;
	//Liste aller Zwischenziele und des Hauptziels
	std::vector<AStarNode*> m_path;
	//Patrol Path
	std::vector<AStarNode*> m_pathPatrol;
	//Zwischenziel
	AStarNode* m_nextTarget;


	//DecisionTree vom Objekt, nach dem es sich individuell entscheidet
	DecisionTree* m_decisionTree;

	Graph<AStarNode, AStarAlgorithm>* m_graph;

	BoundingSphere* m_view;
	float m_viewRadius;

	TreeOutput m_targetType;

	//Weis wo es wohnt
	//GraphNode<AStarNode>* m_homeNodes;
	AStarNode* m_homeNode;
	std::vector<AStarNode*> m_foodNodes;

};