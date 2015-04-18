#include "GeKo_Gameplay/Object/Anthome.h"

Anthome::Anthome(){

}

Anthome::Anthome(glm::vec3 position,AntMesh antMesh, DecisionTree *aggressiveDecisionTree, Graph<AStarNode, AStarAlgorithm> *aggressiveGraph, Texture *tex){
	m_position = position;
	m_antMesh = antMesh;
	//Texture texCV((char*)RESOURCES_PATH "/cv_logo.bmp");
	m_antTexture = tex;
	m_aggressiveGraph = aggressiveGraph;
	m_aggressiveDecisionTree = aggressiveDecisionTree;
	m_numberOfGuards = 1;
	m_numberOfWorkers = 1;
}

Anthome::~Anthome(){

}

void Anthome::initAnts(ObjectObserver *objectObserver){
	while (m_numberOfGuards <= 5){
		std::stringstream name;
		name << "Guard" << m_numberOfGuards;
		m_numberOfGuards++;
		Node *aiGuardNode = new Node(name.str());
		aiGuardNode->addGeometry(&m_antMesh);
		aiGuardNode->addTexture(m_antTexture);
		glm::vec4 position;
		time_t t;
		time(&t);
		srand((unsigned int)t);
		position.x = rand() / 32767.0;
		position.y = 0.0;
		position.z = rand() / 32767.0;
		position.w = 1.0;
		AI *antAI = new AI(glm::vec4(m_position,1.0) + position);
		//antAI.setAntAggressiv();
		antAI->setAntAggressiv(name.str(), m_aggressiveDecisionTree, m_aggressiveGraph);
		aiGuardNode->setObject(antAI);
		antAI->addObserver(objectObserver);
		name.str("");
		m_ants.push_back(aiGuardNode);
	}


}

void Anthome::addAntsToSceneGraph(Node *rootNode){
	for (Node* antNode : m_ants){
		rootNode->addChildrenNode(antNode);
	}
}

void Anthome::updateAnts(){
	/*for (Node antNode : m_ants){
		antNode.getAI()->update();
	}*/
	for (int i = 0; i < m_ants.size(); i++){
		m_ants.at(i)->getAI()->update();
		//m_ants.at(i)->getAI()->addExp(1.0);

	}
}