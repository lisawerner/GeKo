#include "GeKo_Gameplay/Object/AI.h"
#include <stdexcept>

AI::AI(){
	m_id = 0;
	m_type = ObjectType::DEFAULTOBJECT;
	m_name = "defaultObject";

	m_myNodeName = "NULL";

	m_hunger = 10;
	m_hungerMax = 10;
	m_health = 10;
	m_healthMax = 10;
	m_strength = 0.5;
	m_hasDied = false;

	m_decisionTree = new DecisionTree();

	std::pair<States, bool> s(States::HUNGER, false);
	m_states.push_back(s); 
	s.first = States::VIEW;
	s.second = false;
	m_states.push_back(s); 
	s.first = States::HEALTH;
	s.second = true;
	m_states.push_back(s); 

	m_speed = 0.01;
	m_epsilon = 0.1;

	m_position = glm::vec3(0.0);

	AStarNode* defaultNode = new AStarNode();
	
	m_lastTarget = defaultNode;
	m_target = defaultNode;
	m_nextTarget = defaultNode;
	m_lastTargetOnGraph = defaultNode;

	m_homeNode = defaultNode;
	m_foodNodes.push_back(defaultNode);
	m_graph = new Graph<AStarNode, AStarAlgorithm>();

	m_viewRadius = 1.0f;

	m_inventory = new Inventory();
	
	m_targetType = TreeOutput::HOME;

	m_class = ClassType::AI;
}

AI::~AI(){}

AStarNode* AI::getPosHome(){
	return m_homeNode;
}

void AI::setPosHome(AStarNode* pos){
	m_homeNode = pos;
	m_lastTarget = pos;
	m_target = pos;
}

Graph<AStarNode, AStarAlgorithm>* AI::getGraph(){
	return m_graph;
}

void AI::setGraph(Graph<AStarNode, AStarAlgorithm>* graph){
	m_graph = graph;
}

DecisionTree* AI::getDecisionTree(){
	return m_decisionTree;
}

void AI::setDecisionTree(DecisionTree* tree){
	m_decisionTree = tree;
}

float AI::getViewRadius(){
	return m_viewRadius;
}

void AI::addFoodNodes(){
	std::vector<AStarNode*>* nodes = m_graph->getGraph();
	for (int i = 0; i < nodes->size(); i++){
		if (nodes->at(i)->getNodeType() == GraphNodeType::FOOD){
			m_foodNodes.push_back(nodes->at(i));
		}
	}
}

void AI::update(){
	if (m_health <= 0){
		std::cout << "Object" << m_name << ": is dead!" << std::endl;

		if (!m_hasDied)
		{
			notify(*this, Object_Event::OBJECT_STOPPED);
			notify(*this, Object_Event::OBJECT_DIED);
			m_hasDied = true;
		}
		
		setStates(States::HEALTH, false);
	}

	if (getStates(States::HEALTH)){ 
		std::cout << "<<<<<<<< UpdateMethod <<<<<<<<" << std::endl;
		updateStates();

		GraphNodeType lastNodeType = m_target->getNodeType();
		decide2();
		
		float eps = m_epsilon + m_speed;
		if(!checkPosition(m_position, m_target->getPosition())){
			move();
		}
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
	}
	
}

void AI::move(){
	float eps = m_epsilon + m_speed;
	if(checkPosition(m_position, m_nextTarget->getPosition())){
		if (m_path.size() > 0){
			m_nextTarget = m_path.back();
			m_path.pop_back();
			std::cout << "Move to: " << m_nextTarget->getName() << std::endl;
			m_lastTarget = m_nextTarget;
		}
	}

	glm::vec3 diff = m_position - m_nextTarget->getPosition();
	if (diff.x > 0){
		m_position.x -= m_speed;
	}
	if (diff.y > 0){
		m_position.y -= m_speed;
	}
	if (diff.z > 0){
		m_position.z -= m_speed;
	}
	if (diff.x < 0){
		m_position.x += m_speed;
	}
	if (diff.y < 0){
		m_position.y += m_speed;
	}
	if (diff.z < 0){
		m_position.z += m_speed;
	}
	
	notify(*this, Object_Event::OBJECT_MOVED);

	std::cout << "Aktuelle Position: x_" << m_position.x << " y_" << m_position.y << " z_" << m_position.z << std::endl;
}

void AI::viewArea(bool state)
{
	setStates(States::VIEW, state);
}

bool AI::checkPosition(glm::vec3 p1, glm::vec3 p2){

	bool rb = false;

	if (p1.x >= (p2.x - (m_epsilon / m_speed)) & p1.x <= (p2.x + (m_epsilon / m_speed)))
	{
		if ((p1.y >= (p2.y - (m_epsilon / m_speed)))& (p1.y <= (p2.y + (m_epsilon / m_speed))))
		{
			if ((p1.z >= (p2.z - (m_epsilon / m_speed)))& (p1.z <= (p2.z + (m_epsilon / m_speed))))
				rb = true;
		}
	}
	else{
		rb = false;
	}
	return rb;
}

AStarNode* AI::nearestFoodNode(){
	if (m_foodNodes.size() == 1){
		return m_foodNodes.at(0);
	}

	AStarNode* tempReturn;
	m_graph->getAlgorithm()->startAlgorithm2(m_lastTarget, m_foodNodes.at(0), m_path);
	tempReturn = m_path.at(m_path.size() - 1);

	for (int i = 0; i < m_foodNodes.size()-1; i++){
		m_graph->getAlgorithm()->startAlgorithm2(m_lastTarget, m_foodNodes.at(i+1), m_path);
		if (tempReturn->getDistanceTravelled() > m_path.at(m_path.size() - 1)->getDistanceTravelled()){
			tempReturn = m_path.at(m_path.size() - 1);
		}
	}

	return tempReturn;
}

void AI::decide(){
	std::cout << "********** DecideMethod **********" << std::endl;
	m_targetType = m_decisionTree->decide(m_states);

	switch (m_targetType) {
	case TreeOutput::HOME: m_target = m_homeNode; break;
	case TreeOutput::FOOD: m_target = nearestFoodNode(); break;
	case TreeOutput::PLAYER: m_target = m_graph->searchNode(GraphNodeType::OBJECT); break;
	case TreeOutput::PATROL: m_target = nextNodeOnPatrol(); break;
	}
	std::cout << "**********************************" << std::endl;
}

void AI::decide2(){
	std::cout << "********** DecideMethod **********" << std::endl;
	TreeOutput lastOutput = m_targetType;
	m_targetType = m_decisionTree->decide(m_states);

	switch (m_targetType) {
	case TreeOutput::HOME:	
		if (lastOutput != m_targetType){
			m_target = m_homeNode;
			updatePath();
		}
		break;
	case TreeOutput::FOOD:
		if (lastOutput != m_targetType){
			m_target = nearestFoodNode();
			updatePath();
		}
		break;
	case TreeOutput::PLAYER: 
		if (lastOutput != m_targetType){
			m_target = m_graph->searchNode(GraphNodeType::OBJECT);
			updatePathPlayer();
		}
		break;
	case TreeOutput::PATROL:
		if (lastOutput != m_targetType){
			m_target = nextNodeOnPatrol();
			updatePathPatrol();
		}
		if (checkPosition(m_position, m_target->getPosition())){
			//if (m_path.size() == 1){
				updatePathPatrol();
				//m_path = m_pathPatrol;
			//}
		}
		break;
	}
	std::cout << "**********************************" << std::endl;
}


void AI::updatePath(){
	m_graph->calculateDistanceToGoal(m_target);
	m_graph->getAlgorithm()->startAlgorithm2(m_lastTarget, m_target, m_path);
	AStarNode defaultNode;
	m_graph->resetAlgorithm(&defaultNode);
	m_nextTarget = m_path.back();
	m_path.pop_back();
	
	if (m_lastTarget->getNodeType() == GraphNodeType::OBJECT && m_target->getNodeType() != GraphNodeType::OBJECT){
		m_nextTarget = m_lastTargetOnGraph;
	}
}

void AI::updatePathPlayer(){
	m_path.clear();

	m_path.push_back(m_target);
	std::cout << "Laufe auf Player zu!!!" << std::endl;
	m_nextTarget = m_target;
	m_lastTargetOnGraph = m_lastTarget;
}

void AI::updatePathPatrol(){
	m_path.clear();
	std::vector<AStarNode*> tmp = m_pathPatrol;
	m_pathPatrol.clear();
	for (int i = 0; i < tmp.size()-1; i++){
		m_pathPatrol.push_back(tmp.at(i+1));
	}
	m_pathPatrol.push_back(tmp.at(0));
	m_path = m_pathPatrol;
	m_path.pop_back();
	m_nextTarget = m_path.back();
	m_target = m_path.at(0);
	std::cout << "Laufe auf Patrouille!!!" << " Next target at path: " << m_nextTarget->getName() << std::endl;
}

AStarNode* AI::nextNodeOnPatrol(){
	std::vector<AStarNode*>* temp = m_graph->getGraph();
	if (m_target->getNodeType() != GraphNodeType::DEFAULT){
		if (checkPosition(m_position, m_nextTarget->getPosition())){
			for (int i = 0; i < temp->size(); i++){
				if (m_lastTarget->getNodeType() == GraphNodeType::OBJECT || m_lastTarget->getNodeType() == GraphNodeType::FOOD){
					if (temp->at(i)->getNodeType() == GraphNodeType::OTHER){
						return temp->at(i);
					}
				}
				else { 
					if (m_lastTarget == temp->at(i)){
						int j = (i + 1) % temp->size();
						while (temp->at(j) != m_lastTarget){
							if (temp->at(j)->getNodeType() == GraphNodeType::OTHER){
								return temp->at(j);
							}
							j = (j + 1) % temp->size();
						}
					}
				}
			}
		}
	}
}

void AI::setAntAfraid(){
	m_type = ObjectType::ANT;
	m_name = "Flick";

	DecisionTree* tree = new DecisionTree();
	tree->setAntTreeAfraid();
	m_decisionTree = tree;

	m_speed = 0.3;

	m_position = glm::vec3(0.0);

	glm::vec3 posFood(10.0, 0.0, -5.0);
	glm::vec3 posSpawn(3.0, 0.0, 3.0);
	glm::vec3 posDefaultPlayer(0.0, 0.0, 0.0);
	Graph<AStarNode, AStarAlgorithm>* antGraph = new Graph<AStarNode, AStarAlgorithm>();
	antGraph->setExampleAntAfraid(posSpawn, posFood, posDefaultPlayer);
	m_graph = antGraph;

	m_lastTarget = antGraph->searchNode(GraphNodeType::HOME);
	m_target = antGraph->searchNode(GraphNodeType::HOME);

	m_position = posSpawn;
	m_homeNode = antGraph->searchNode(GraphNodeType::HOME);
	m_foodNodes.pop_back(); 
	addFoodNodes();
}

void AI::setAntAggressiv(){
	m_type = ObjectType::ANT;
	m_name = "Flack";

	DecisionTree* tree = new DecisionTree();
	tree->setAntTreeAggressiv();
	m_decisionTree = tree;

	m_speed = 0.1;
	m_strength = 1.2;

	m_position = glm::vec3(0.0);

	glm::vec3 posFood(10.0, 0.0, -5.0);
	glm::vec3 posSpawn(3.0, 0.0, 3.0);
	glm::vec3 posDefaultPlayer(0.0, 0.0, 0.0);
	Graph<AStarNode, AStarAlgorithm>* antGraph = new Graph<AStarNode, AStarAlgorithm>();
	antGraph->setExampleAntAggressiv(posSpawn, posSpawn, posDefaultPlayer);
	m_graph = antGraph;
	for (int i = 0; i < m_graph->getGraph()->size(); i++){
		if (m_graph->getGraph()->at(i)->getNodeType() == GraphNodeType::OTHER){
			m_pathPatrol.push_back(m_graph->getGraph()->at(i));
		}
	}

	m_lastTarget = antGraph->searchNode(GraphNodeType::FOOD);
	m_target = antGraph->searchNode(GraphNodeType::FOOD);

	m_position = posSpawn;
	m_homeNode = antGraph->searchNode(GraphNodeType::FOOD);
	m_foodNodes.pop_back(); //Delete DefaultNode
	m_foodNodes.push_back(antGraph->searchNode(GraphNodeType::FOOD));
}

std::string AI::getSourceName(SoundtypeAI type)
{
	try{
		return m_soundMap.at(type);
	}
	catch (const std::out_of_range& oor)
	{
		std::cout << "No Sound with this type was set!" << std::endl;
		return "oor";
	}

}

void AI::setSourceName(SoundtypeAI type, std::string sourceName, const char* filepath)
{
	m_sfh->generateSource(sourceName, m_position, filepath);
	m_soundMap.insert(std::pair<SoundtypeAI, std::string>(type, sourceName));
}

void AI::updateSourcesInMap()
{
	for (std::map<SoundtypeAI, std::string>::iterator i = m_soundMap.begin(); i != m_soundMap.end(); ++i)
	{
		m_sfh->updateSourcePosition(i->second, m_position);
	}
}

bool AI::hasDied()
{
	return m_hasDied;
}