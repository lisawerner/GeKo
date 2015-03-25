# include <GeKo_Gameplay/AI_Pathfinding/AStarAlgorithm.h>

AStarAlgorithm::AStarAlgorithm(std::string name) : Algorithm(name)
{

}

AStarAlgorithm::~AStarAlgorithm()
{

}

AStarNode* AStarAlgorithm::startAlgorithm(AStarNode* startNode, AStarNode* endNode)
{
	std::cout << "A*-ALGORITHM WILL BE STARTED" << std::endl;

	std::vector<AStarNode*> pathList;
	std::cout << startNode->getName() << " GOES INTO THE PATHLIST" << std::endl;
	pathList.push_back(startNode);

	std::vector<AStarNode*> wastedList;

	AStarNode* tmp;
	bool wasIn = false;
	bool shorterPathFound = false;

	int distanceTraveled = 0;

	bool secondOut = false;
	AStarNode* returnNode;
	returnNode = startNode;

	while (pathList.back()->getName() != endNode->getName() && !pathList.empty())
	{
		std::cout << "FRONT ELEMENT OF THE LIST GOES OUT: " << pathList.back()->getName()<< "(" << pathList.back()->getTemporary() << ")" << std::endl;
		tmp = pathList.back();
		wastedList.push_back(pathList.back());
		pathList.pop_back();


		std::cout << "THE OTHER ELEMENTS IN THE LIST ARE: ";
		for (int bb = 0; bb < pathList.size(); bb++)
		{
			std::cout << pathList.at(bb)->getName() << "(" << pathList.at(bb)->getTemporary() << ")";
		}
		std::cout << std::endl;

		if (secondOut)
		{
			//std::cout << "THE RETURN ELEMENT IS FOUND!" << std::endl;
			returnNode = tmp;
			secondOut = false;
		}

		if (tmp->getName() == startNode->getName())
		{
			secondOut = true;
		}

		//Neue Pfade hinzufügen
		for (int i = 0; i < tmp->getPaths()->size(); i++)
		{
			//std::cout << "Name von default: " << tmp->getVisitor()->getName() << std::endl;
			//std::cout << "NEIGHBOR OF..." << tmp->getName() << "...IS..." << tmp->getPaths()->at(i)->getEndNode()->getName() << std::endl;
			//Überprüfung, ob der aktuelle Endknoten des Pfades den man hinzufügen will, den Knoten vorher besucht hat, dann wäre dies ein Rückpfad, den wir nicht drin haben wollen
			if (tmp->getPaths()->at(i)->getEndNode()->getName() != tmp->getVisitor()->getName() && tmp->getPaths()->at(i)->getEndNode()->getName() != startNode->getName())
			{

				//Wir müssen nun schauen, ob ein Knoten mit dem selben Namen schon in unserer Pfadliste ist
				//Wenn ja, wollen wir eine Kopie erstellen, denn wir wollen mehrere Pfade zu einem Knoten speichern können
				AStarNode* copyNode = new AStarNode();
				for (int j = 0; j < pathList.size(); j++)
				{

					if (tmp->getPaths()->at(i)->getEndNode()->getName() == pathList.at(j)->getName())
					{
						wasIn = true;
						copyNode->setPathList(*pathList.at(j)->getPaths());
						copyNode->setName(pathList.at(j)->getName());
						break;
					}

				}
				for (int m = 0; m < wastedList.size(); m++)
				{

					if (tmp->getPaths()->at(i)->getEndNode()->getName() == wastedList.at(m)->getName())
					{
						wasIn = true;
						copyNode->setPathList(*wastedList.at(m)->getPaths());
						copyNode->setName(wastedList.at(m)->getName());
						break;
					}

				}

				//Wenn der Node noch nicht in der Pfad-Liste steht, dann wird er einfach normal eingefügt
				if (!wasIn){


					//std::cout << "TRAVELLED DISTANCE OF..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE RAISED BY..." << tmp->getPaths()->at(i)->getTimeToTravel() << "...+..." << tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() << "...!" << std::endl;
					tmp->getPaths()->at(i)->getEndNode()->setDistanceTravelled(tmp->getPaths()->at(i)->getTimeToTravel() + tmp->getDistanceTravelled());
					tmp->getPaths()->at(i)->getEndNode()->setTemporary(tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() + tmp->getPaths()->at(i)->getEndNode()->getDistanceTravelled());
					
					//std::cout << "TRAVELLED DISTANCE OF..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...IS NOW..." << tmp->getPaths()->at(i)->getEndNode()->getTemporary() << "...!" << std::endl;


					//Wir fügen den Pfad nur hinzu, wenn es keinen Pfad in der Liste gibt, der eine geringere Weglänge hat
					for (int n = 0; n < pathList.size(); n++)
					{
						//Es gibt einen Pfad, der eine kürzere travelledDistance hat
						if (pathList.at(n)->getName() == tmp->getPaths()->at(i)->getEndNode()->getName() && pathList.at(n)->getDistanceTravelled() < tmp->getPaths()->at(i)->getEndNode()->getDistanceTravelled())
						{
							//boolean Wert setzen 
							shorterPathFound = true;

						}
						//der Pfad, der schon vorhanden ist zu dem Node, hat eine größere distanceTravelled und wird aus der Liste gelöscht
						else if (pathList.at(n)->getName() == tmp->getPaths()->at(i)->getEndNode()->getName() && pathList.at(n)->getDistanceTravelled() >= tmp->getPaths()->at(i)->getEndNode()->getDistanceTravelled()){
							//std::cout << "THE NODE..." << pathList.at(n)->getName() << "...WILL BE DELETED, IT HAS A LONGER TRAVEL TIME THEN THE NEW ONE..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "!" << std::endl;
							pathList.erase(pathList.begin() + n);
						}
					}

					if (!shorterPathFound)
					{
						//std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
						pathList.push_back(tmp->getPaths()->at(i)->getEndNode());
						tmp->getPaths()->at(i)->getEndNode()->setVisitor(tmp);
					}
					else{
						//std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE NOT ADD, SHORTER PATH FOUND!" << std::endl;
						shorterPathFound = false;
					}


				}
				//Falls der Node schon über einen anderen Pfad erreicht wurde, dann erstellen wir eine Kopie des Nodes und fügen diese Kopie zusätzlich in die Liste
				else{
					copyNode->setDistanceTravelled(-(copyNode->getDistanceTravelled()));
					//std::cout << "TRAVELLED DISTANCE OF...NEW--" << copyNode->getName() << "...WILL BE RAISED BY..." << tmp->getPaths()->at(i)->getTimeToTravel() << "...+..." << tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() << "...!" << std::endl;
					copyNode->setDistanceTravelled(tmp->getPaths()->at(i)->getTimeToTravel() + tmp->getDistanceTravelled());
					copyNode->setTemporary(tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() + copyNode->getDistanceTravelled());

					//std::cout << "TRAVELLED DISTANCE OF...NEW--" << copyNode->getName() << "...IS NOW..." << copyNode->getTemporary() << "...!" << std::endl;


					//Wir fügen den Pfad nur hinzu, wenn es keinen Pfad in der Liste gibt, der eine geringere Weglänge hat
					for (int n = 0; n < pathList.size(); n++)
					{
						//Es gibt einen Pfad, der eine kürzere travelledDistance hat
						if (pathList.at(n)->getName() == copyNode->getName() && pathList.at(n)->getDistanceTravelled() < copyNode->getDistanceTravelled())
						{
							//boolean Wert setzen 
							shorterPathFound = true;

						}//der Pfad, der schon vorhanden ist zu dem Node, hat eine größere distanceTravelled und wird aus der Liste gelöscht
						else if (pathList.at(n)->getName() == tmp->getPaths()->at(i)->getEndNode()->getName() && pathList.at(n)->getDistanceTravelled() >= tmp->getPaths()->at(i)->getEndNode()->getDistanceTravelled()){
							//std::cout << "THE NODE..." << pathList.at(n)->getName() << "...WILL BE DELETED, IT HAS A LONGER TRAVEL TIME THEN THE NEW ONE..." << copyNode->getName() << "!" << std::endl;
							pathList.erase(pathList.begin() + n);
						}
					}

					if (!shorterPathFound)
					{
						//std::cout << "NEIGHBOUR...NEW--" << copyNode->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
						copyNode->setVisitor(tmp);
						pathList.push_back(copyNode);
					}
					else{
						//std::cout << "NEIGHBOUR...NEW--" << copyNode->getName() << "...WILL NOT BE ADD, SHORTER PATH FOUND!" << std::endl;
						shorterPathFound = false;
					}
					wasIn = false;
				}

			}
			else{
				//std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...COULD CAUSE A LOOP! WILL NOT BE IN THE LIST!" << std::endl;
			}

		}

		//Pfad-Liste muss neu sortiert werden 
		AStarNode* save;
		for (int k = 1; k < pathList.size(); k++)
		{
			for (int l = 0; l < pathList.size() - k; l++)
			{
				if (pathList.at(l)->getTemporary() < pathList.at(l + 1)->getTemporary())
				{
					save = pathList.at(l + 1);
					pathList.at(l + 1) = pathList.at(l);
					pathList.at(l) = save;
				}
			}
		}

	}
	std::string test = pathList.back()->getName();
	//std::cout << "CONTROLL CHECK, " << test << " IS GOAL: " << test << std::endl;
	//std::cout << "CONTROLL CHECK, Visitor of Goal IS: " << pathList.back()->getVisitor()->getName() << std::endl;
	//std::cout << "TRAVELLED DISTANCE IS: " << pathList.back()->getDistanceTravelled() << std::endl;

	if (secondOut)
	{
		returnNode = endNode;
	}

	return returnNode;
}


std::vector<AStarNode*>* AStarAlgorithm::startAlgorithm2(AStarNode* startNode, AStarNode* endNode, std::vector<AStarNode*> &path)
{

	//std::cout << "A*-ALGORITHM WILL BE STARTED" << std::endl;

	std::vector<AStarNode*> pathList;
	//std::cout << startNode->getName() << " GOES INTO THE PATHLIST" << std::endl;
	pathList.push_back(startNode);

	std::vector<AStarNode*> wastedList;

	AStarNode* tmp;
	bool wasIn = false;
	bool shorterPathFound = false;

	int distanceTraveled = 0;

	bool secondOut = false;
	AStarNode* returnNode;
	returnNode = startNode;

	while (pathList.back()->getName() != endNode->getName() && !pathList.empty())
	{
		//std::cout << "FRONT ELEMENT OF THE LIST GOES OUT: " << pathList.back()->getName() << "(" << pathList.back()->getTemporary() << ")" << std::endl;
		tmp = pathList.back();
		wastedList.push_back(pathList.back());
		pathList.pop_back();


		//std::cout << "THE OTHER ELEMENTS IN THE LIST ARE: ";
		for (int bb = 0; bb < pathList.size(); bb++)
		{
			//std::cout << pathList.at(bb)->getName() << "(" << pathList.at(bb)->getTemporary() << ")";
		}
		//std::cout << std::endl;

		if (secondOut)
		{
			//std::cout << "THE RETURN ELEMENT IS FOUND!" << std::endl;
			returnNode = tmp;
			secondOut = false;
		}

		if (tmp->getName() == startNode->getName())
		{
			secondOut = true;
		}

		//Neue Pfade hinzufügen
		for (int i = 0; i < tmp->getPaths()->size(); i++)
		{
			//std::cout << "Name von default: " << tmp->getVisitor()->getName() << std::endl;
			//std::cout << "NEIGHBOR OF..." << tmp->getName() << "...IS..." << tmp->getPaths()->at(i)->getEndNode()->getName() << std::endl;
			//Überprüfung, ob der aktuelle Endknoten des Pfades den man hinzufügen will, den Knoten vorher besucht hat, dann wäre dies ein Rückpfad, den wir nicht drin haben wollen
			if (tmp->getPaths()->at(i)->getEndNode()->getName() != tmp->getVisitor()->getName() && tmp->getPaths()->at(i)->getEndNode()->getName() != startNode->getName())
			{

				//Wir müssen nun schauen, ob ein Knoten mit dem selben Namen schon in unserer Pfadliste ist
				//Wenn ja, wollen wir eine Kopie erstellen, denn wir wollen mehrere Pfade zu einem Knoten speichern können
				AStarNode* copyNode = new AStarNode();
				for (int j = 0; j < pathList.size(); j++)
				{

					if (tmp->getPaths()->at(i)->getEndNode()->getName() == pathList.at(j)->getName())
					{
						wasIn = true;
						copyNode->setPathList(*pathList.at(j)->getPaths());
						copyNode->setName(pathList.at(j)->getName());
						copyNode->setDistanceToGoal(pathList.at(j)->getDistanceToGoal());
						copyNode->setPosition(wastedList.at(j)->getPosition());
						break;
					}

				}
				for (int m = 0; m < wastedList.size(); m++)
				{

					if (tmp->getPaths()->at(i)->getEndNode()->getName() == wastedList.at(m)->getName())
					{
						wasIn = true;
						copyNode->setPathList(*wastedList.at(m)->getPaths());
						copyNode->setName(wastedList.at(m)->getName());
						copyNode->setDistanceToGoal(wastedList.at(m)->getDistanceToGoal());
						copyNode->setPosition(wastedList.at(m)->getPosition());
						break;
					}

				}

				//Wenn der Node noch nicht in der Pfad-Liste steht, dann wird er einfach normal eingefügt
				if (!wasIn){


					//std::cout << "TRAVELLED DISTANCE OF..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE RAISED BY..." << tmp->getPaths()->at(i)->getTimeToTravel() << "...+..." << tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() << "...!" << std::endl;
					tmp->getPaths()->at(i)->getEndNode()->setDistanceTravelled(tmp->getPaths()->at(i)->getTimeToTravel() + tmp->getDistanceTravelled());
					tmp->getPaths()->at(i)->getEndNode()->setTemporary(tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() + tmp->getPaths()->at(i)->getEndNode()->getDistanceTravelled());
					
					//std::cout << "TRAVELLED DISTANCE OF..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...IS NOW..." << tmp->getPaths()->at(i)->getEndNode()->getTemporary() << "...!" << std::endl;


					//Wir fügen den Pfad nur hinzu, wenn es keinen Pfad in der Liste gibt, der eine geringere Weglänge hat
					for (int n = 0; n < pathList.size(); n++)
					{
						//Es gibt einen Pfad, der eine kürzere travelledDistance hat
						if (pathList.at(n)->getName() == tmp->getPaths()->at(i)->getEndNode()->getName() && pathList.at(n)->getDistanceTravelled() < tmp->getPaths()->at(i)->getEndNode()->getDistanceTravelled())
						{
							//boolean Wert setzen 
							shorterPathFound = true;

						}
						//der Pfad, der schon vorhanden ist zu dem Node, hat eine größere distanceTravelled und wird aus der Liste gelöscht
						else if (pathList.at(n)->getName() == tmp->getPaths()->at(i)->getEndNode()->getName() && pathList.at(n)->getDistanceTravelled() >= tmp->getPaths()->at(i)->getEndNode()->getDistanceTravelled()){
							//std::cout << "THE NODE..." << pathList.at(n)->getName() << "...WILL BE DELETED, IT HAS A LONGER TRAVEL TIME THEN THE NEW ONE..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "!" << std::endl;
							pathList.erase(pathList.begin() + n);
						}
					}

					if (!shorterPathFound)
					{
						//std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
						pathList.push_back(tmp->getPaths()->at(i)->getEndNode());
						tmp->getPaths()->at(i)->getEndNode()->setVisitor(tmp);
					}
					else{
						//std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE NOT ADD, SHORTER PATH FOUND!" << std::endl;
						shorterPathFound = false;
					}


				}
				//Falls der Node schon über einen anderen Pfad erreicht wurde, dann erstellen wir eine Kopie des Nodes und fügen diese Kopie zusätzlich in die Liste
				else{
					copyNode->setDistanceTravelled(-(copyNode->getDistanceTravelled()));
					//std::cout << "TRAVELLED DISTANCE OF...NEW--" << copyNode->getName() << "...WILL BE RAISED BY..." << tmp->getPaths()->at(i)->getTimeToTravel() << "...+..." << tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() << "...!" << std::endl;
					copyNode->setDistanceTravelled(tmp->getPaths()->at(i)->getTimeToTravel() + tmp->getDistanceTravelled());
					copyNode->setTemporary(tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() + copyNode->getDistanceTravelled());

					//std::cout << "TRAVELLED DISTANCE OF...NEW--" << copyNode->getName() << "...IS NOW..." << copyNode->getTemporary() << "...!" << std::endl;


					//Wir fügen den Pfad nur hinzu, wenn es keinen Pfad in der Liste gibt, der eine geringere Weglänge hat
					for (int n = 0; n < pathList.size(); n++)
					{
						//Es gibt einen Pfad, der eine kürzere travelledDistance hat
						if (pathList.at(n)->getName() == copyNode->getName() && pathList.at(n)->getDistanceTravelled() < copyNode->getDistanceTravelled())
						{
							//boolean Wert setzen 
							shorterPathFound = true;

						}//der Pfad, der schon vorhanden ist zu dem Node, hat eine größere distanceTravelled und wird aus der Liste geupdated
						else if (pathList.at(n)->getName() == tmp->getPaths()->at(i)->getEndNode()->getName() && pathList.at(n)->getDistanceTravelled() >= tmp->getPaths()->at(i)->getEndNode()->getDistanceTravelled()){
							//std::cout << "THE NODE..." << pathList.at(n)->getName() << "...WILL BE DELETED, IT HAS A LONGER TRAVEL TIME THEN THE NEW ONE..." << copyNode->getName() << "!" << std::endl;
							pathList.at(n)->setDistanceTravelled(copyNode->getDistanceTravelled());
							pathList.at(n)->setVisitor(tmp);
						}
					}

					if (!shorterPathFound)
					{
						//std::cout << "NEIGHBOUR...NEW--" << copyNode->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
					}
					else{
						//std::cout << "NEIGHBOUR...NEW--" << copyNode->getName() << "...WILL NOT BE ADD, SHORTER PATH FOUND!" << std::endl;
						shorterPathFound = false;
					}
					wasIn = false;
				}

			}
			else{
				//std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...COULD CAUSE A LOOP! WILL NOT BE IN THE LIST!" << std::endl;
			}

		}

		//Pfad-Liste muss neu sortiert werden 
		AStarNode* save;
		for (int k = 1; k < pathList.size(); k++)
		{
			for (int l = 0; l < pathList.size() - k; l++)
			{
				if (pathList.at(l)->getTemporary() < pathList.at(l + 1)->getTemporary())
				{
					save = pathList.at(l + 1);
					pathList.at(l + 1) = pathList.at(l);
					pathList.at(l) = save;
				}
			}
		}

	}
	//std::string test = pathList.back()->getName();
	//std::cout << "CONTROLL CHECK, " << test << " IS GOAL: " << test << std::endl;
	//std::cout << "CONTROLL CHECK, Visitor of Goal IS: " << pathList.back()->getVisitor()->getName() << std::endl;
	//std::cout << "TRAVELLED DISTANCE IS: " << pathList.back()->getDistanceTravelled() << std::endl;

	if (secondOut)
	{
		returnNode = endNode;
	}

	//std::cout << "THE GOAL NODE WILL BE PUSHED ON THE RETURN PATH: " << test << std::endl;
	path.push_back(pathList.back());
	while (path.back()->getName() != startNode->getName())
	{
		//std::cout << "THE NODE : " << returnPath.back()->getVisitor()->getName() << " WILL BE ADDED TO THE RETURN PATH!" << std::endl;
		path.push_back(path.back()->getVisitor());
	}

	return &m_path;
}