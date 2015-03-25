#pragma once 

#include <iostream>
#include <glm/glm.hpp>

#include "GeKo_Gameplay/AI_Pathfinding/GraphNode.h"
#include "GeKo_Gameplay/AI_Pathfinding/AStarNode.h"
#include "GeKo_Gameplay/AI_Pathfinding/AStarAlgorithm.h"

#include "TreeOutput.h"
#include <GeKo_Gameplay/Object/States.h>


class DecisionTreeNode
{
public: 
	DecisionTreeNode(int nodeID, DecisionTreeNode* defaultNode);
	DecisionTreeNode();
	~DecisionTreeNode();

	int getID();

	bool getIsLeaf();
	void setLeaf(bool isLeaf);

	States getStateID();
	void setStateID(States id);

	DecisionTreeNode* getLeftNode();
	void setLeftNode(DecisionTreeNode* left);

	DecisionTreeNode* getRightNode();
	void setRightNode(DecisionTreeNode* right);

	bool getCondition();
	void setCondition(bool con);

	TreeOutput getTarget();
	void setTarget(TreeOutput target);

protected:
	//ID vom Node
	int m_idNode;

	//std::vector<DecisionTreeNode> m_nodes;
	DecisionTreeNode* m_leftNode;
	DecisionTreeNode* m_rightNode;

	bool m_isLeaf;
	
	//Target wird im Leaf gespeichert und ausgegeben
	//GraphNode<AStarNode>* m_target;
	//std::vector<AStarNode*> m_target;
	TreeOutput m_target;

	//"ID" oder Referenz auf die Entscheidung, also z.B. Objekt->Hunger
	States m_stateID;

	//Ein Child ist true und eines false
	//bool m_condition;
	bool m_condition;
};