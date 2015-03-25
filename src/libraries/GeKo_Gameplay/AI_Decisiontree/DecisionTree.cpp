#include <GeKo_Gameplay/AI_DecisionTree/DecisionTree.h>

DecisionTree::DecisionTree(){}

DecisionTree::DecisionTree(DecisionTreeNode* root){
	m_rootNode = root;
	m_currentNode = root;
}

DecisionTree::~DecisionTree(){

}

TreeOutput DecisionTree::decide(std::vector<std::pair<States, bool>> states){
	//std::cout << "Current Node: " << m_currentNode->getID() << std::endl;
	//Check current is not a leaf
	if (!m_currentNode->getIsLeaf()){
		//is not a leaf
		//std::cout << "In Tree: no Leaf" << std::endl;
		//Hole aus dem Objekt True/False mit der StateID
		bool stateCondition = NULL;
		if (m_currentNode->getStateID() != States::DEFAULTSTATE){
			stateCondition = getStates(states, m_currentNode->getStateID());
		}
		//std::cout << "Actual Condition: " << stateCondition << std::endl;
		//Hole die Boolean für linkes und rechtes Kind
		bool leftCondition = NULL;
		if (m_currentNode->getLeftNode()->getCondition() != NULL){
			leftCondition = m_currentNode->getLeftNode()->getCondition();
		}
	
		bool rightCondition = NULL;
		if (m_currentNode->getRightNode()->getCondition() != NULL){
			rightCondition = m_currentNode->getRightNode()->getCondition();
		}
		//Vergleiche State mit Kindern
		if (stateCondition == leftCondition){
			//std::cout << "In Tree: go to LeftNode" << std::endl;

			m_currentNode = m_currentNode->getLeftNode();
			return decide(states);
		}
		else if (stateCondition == rightCondition){

			//std::cout << "In Tree: go to RightNode" << std::endl;

			m_currentNode = m_currentNode->getRightNode();
			return decide(states);
		}
		else {
			//TODO: Fehlerausgabe
			//Weder linkes, noch rechtes Kind
			//std::cout << "FATAL ERROR: Neither left child, nor right child" << std::endl;
		}
	}
		//is a Leaf
		TreeOutput target = m_currentNode->getTarget();
		//Baum ist durchlaufen. Methode ist aufgerufen. Also current wieder auf Anfang für nächstes Mal setzten
		m_currentNode = m_rootNode;
		/*std::cout << "Das aktuelle Ziel ist: ";
		switch (target){
		case TreeOutput::HOME: std::cout << " Home!" << std::endl; break;
		case TreeOutput::FOOD: std::cout << " Food!" << std::endl; break;
		case TreeOutput::PLAYER: std::cout << " Player!" << std::endl; break;
		}*/
		
		return target;
}

void DecisionTree::setRootNode(DecisionTreeNode &root){
	m_rootNode = &root;
}

DecisionTreeNode* DecisionTree::getRootNode(){
	return m_rootNode;
}

void DecisionTree::setCurrentNode(DecisionTreeNode &current){
	m_currentNode = &current;
}

DecisionTreeNode* DecisionTree::getCurrentNode(){
	return m_currentNode;
}

bool DecisionTree::getStates(std::vector<std::pair<States, bool>> list, States state){
	for (int i = 0; i < list.size(); i++){
		if (list.at(i).first == state) {
			return list.at(i).second;
		};
	}
	return NULL;
}

void DecisionTree::setStates(std::vector<std::pair<States, bool>> list, States state, bool b){
	for (int i = 0; i < list.size(); i++){
		if (list.at(i).first == state){
			list.at(i).second = b;
		}
	}
}

void DecisionTree::setAntTreeAfraid(){
	DecisionTreeNode defaultNode;
	m_rootNode = new DecisionTreeNode(1, &defaultNode);
	DecisionTreeNode* lView = new DecisionTreeNode(2, &defaultNode);
	DecisionTreeNode* rView = new DecisionTreeNode(3, &defaultNode);
	DecisionTreeNode* lHunger = new DecisionTreeNode(4, &defaultNode);
	DecisionTreeNode* rHunger = new DecisionTreeNode(5, &defaultNode);

	m_rootNode->setStateID(States::VIEW);

	m_rootNode->setLeftNode(lView);
	lView->setCondition(true);
	lView->setLeaf(true);
	lView->setTarget(TreeOutput::HOME); //Spawn für Ängstlicher Flick, Player für aggressiver Flick

	m_rootNode->setRightNode(rView);
	rView->setCondition(false);
	rView->setStateID(States::HUNGER);

	rView->setLeftNode(lHunger);
	lHunger->setCondition(true);
	lHunger->setLeaf(true);
	lHunger->setTarget(TreeOutput::FOOD);

	rView->setRightNode(rHunger);
	rHunger->setCondition(false);
	rHunger->setLeaf(true);
	rHunger->setTarget(TreeOutput::HOME);

	m_currentNode = m_rootNode;
}

void DecisionTree::setAntTreeAggressiv(){
	DecisionTreeNode defaultNode;
	m_rootNode = new DecisionTreeNode(1, &defaultNode);
	DecisionTreeNode* lView = new DecisionTreeNode(2, &defaultNode);
	DecisionTreeNode* rView = new DecisionTreeNode(3, &defaultNode);
	DecisionTreeNode* lHunger = new DecisionTreeNode(4, &defaultNode);
	DecisionTreeNode* rHunger = new DecisionTreeNode(5, &defaultNode);

	m_rootNode->setStateID(States::VIEW);

	m_rootNode->setLeftNode(lView);
	lView->setCondition(true);
	lView->setLeaf(true);
	lView->setTarget(TreeOutput::PLAYER); //Spawn für Ängstlicher Flick, Player für aggressiver Flick

	m_rootNode->setRightNode(rView);
	rView->setCondition(false);
	rView->setStateID(States::HUNGER);

	rView->setLeftNode(lHunger);
	lHunger->setCondition(true);
	lHunger->setLeaf(true);
	lHunger->setTarget(TreeOutput::FOOD);

	rView->setRightNode(rHunger);
	rHunger->setCondition(false);
	rHunger->setLeaf(true);
	rHunger->setTarget(TreeOutput::PATROL);

	m_currentNode = m_rootNode;
}