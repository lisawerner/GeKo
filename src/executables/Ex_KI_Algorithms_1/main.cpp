#include <GL/glew.h>
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/MaterialInclude.h>
#include <GeKo_Graphics/ObjectInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>
#include <GeKo_Graphics/AIInclude.h>
#include <list>
#include <queue>
#include <stack>


InputHandler iH;
Trackball cam("Trackball");

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			activeMap.at(key)();
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}
}

void firstBasicMethod(GraphNode* s, GraphNode* g)
{
	std::cout << "FIRST BASIC METHOD WILL BE STARTED!" << std::endl;

	std::list<GraphNode*> pathList;
	std::cout << "S GO INTO THE LIST!" << std::endl;
	pathList.push_front(s);

	std::vector<GraphNode*> wastedList;

	GraphNode* tmp;
	bool wasIn = false;

	//Solange der Zielknoten nicht vorne in der Liste steht und die Liste nicht leer ist
	while (pathList.front()->getName() != g->getName() && pathList.size() != 0)
	{
		std::cout << "FRONT ELEMENT OF THE LIST GOES OUT: " << pathList.front()->getName() << std::endl;

		//Nehmen wir das vorderste Element raus 
		tmp = pathList.front();
		pathList.pop_front();
		//speichern es für später
		wastedList.push_back(tmp);

		for (int i = 0; i < tmp->getPaths()->size(); i++)
		{
			//Nachschauen ob ein Children-Node irgendwann mal in der Liste war (Loops verhindern)
			for (int  j= 0; j < wastedList.size(); j++)
			{
				if (tmp->getPaths()->at(i)->getEndNode()->getName() == wastedList.at(j)->getName())
				{
					std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...COULD CAUSE A LOOP! WILL NOT BE IN THE LIST!" << std::endl;
					wasIn = true;
				}
			}
			//Falls das Children-Node noch nie in der Liste war, wird es der Liste hinzugefügt
			if (!wasIn)
			{
				std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
				pathList.push_front(tmp->getPaths()->at(i)->getEndNode());
			}
			wasIn = false;
		}
	}

	std::string test = pathList.front()->getName();
	std::cout << "CONTROLL CHECK, G IS GOAL: " << test << std::endl;
}

void bfsMethod(GraphNode* s, GraphNode* g)
{
	std::cout << "BFS METHOD WILL BE STARTED!" << std::endl;

	std::queue<GraphNode*> pathList;
	std::cout << "S GO INTO THE QUEUE!" << std::endl;
	pathList.push(s);

	std::vector<GraphNode*> wastedList;

	GraphNode* tmp;
	bool wasIn = false;

	while (pathList.front()->getName() != g->getName() && !pathList.empty())
	{
		std::cout << "FRONT ELEMENT OF THE LIST GOES OUT: " << pathList.front()->getName() << std::endl;
		tmp = pathList.front();
		pathList.pop();
		wastedList.push_back(tmp);

		for (int i = 0; i < tmp->getPaths()->size(); i++)
		{
			for (int j = 0; j < wastedList.size(); j++)
			{
				if (tmp->getPaths()->at(i)->getEndNode()->getName() == wastedList.at(j)->getName())
				{
					std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...COULD CAUSE A LOOP! WILL NOT BE IN THE LIST!" << std::endl;
					wasIn = true;
				}
			}

			if (!wasIn)
			{
				std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
				pathList.push(tmp->getPaths()->at(i)->getEndNode());

			}
			wasIn = false;
		}
	}

	std::string test = pathList.front()->getName();
	std::cout << "CONTROLL CHECK, G IS GOAL: " << test << std::endl;
}

void dfsMethod(GraphNode* s, GraphNode* g)
{
	std::cout << "DFS METHOD WILL BE STARTED!" << std::endl;

	std::stack<GraphNode*> pathList;
	std::cout << "S GO ONTO THE STACK!" << std::endl;
	pathList.push(s);

	std::vector<GraphNode*> wastedList;

	GraphNode* tmp;
	bool wasIn = false;

	while (pathList.top()->getName() != g->getName() && !pathList.empty())
	{
		std::cout << "FRONT ELEMENT OF THE LIST GOES OUT: " << pathList.top()->getName() << std::endl;
		tmp = pathList.top();
		pathList.pop();
		wastedList.push_back(tmp);

		for (int i = 0; i < tmp->getPaths()->size(); i++)
		{
			for (int j = 0; j < wastedList.size(); j++)
			{
				if (tmp->getPaths()->at(i)->getEndNode()->getName() == wastedList.at(j)->getName())
				{
					std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...COULD CAUSE A LOOP! WILL NOT BE IN THE LIST!" << std::endl;
					wasIn = true;
				}
			}

			if (!wasIn)
			{
				std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
				pathList.push(tmp->getPaths()->at(i)->getEndNode());

			}
			wasIn = false;
		}
	}

	std::string test = pathList.top()->getName();
	std::cout << "CONTROLL CHECK, G IS GOAL: " << test << std::endl;

}

void hillClimbing(GraphNode* s, GraphNode* g)
{
	std::cout << "HILL CLIMBING (DFS) WILL BE STARTED!" << std::endl;

	std::stack<GraphNode*> pathList;
	std::cout << "S GO ONTO THE STACK!" << std::endl;
	pathList.push(s);

	std::vector<GraphNode*> wastedList;
	std::list<GraphNode*> priorityList;

	GraphNode* tmp;
	bool wasIn = false;

	while (pathList.top()->getName() != g->getName() && !pathList.empty())
	{
		std::cout << "FRONT ELEMENT OF THE LIST GOES OUT: " << pathList.top()->getName() << std::endl;
		tmp = pathList.top();
		pathList.pop();
		wastedList.push_back(tmp);

		for (int i = 0; i < tmp->getPaths()->size(); i++)
		{
			for (int j = 0; j < wastedList.size(); j++)
			{
				if (tmp->getPaths()->at(i)->getEndNode()->getName() == wastedList.at(j)->getName())
				{
					std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...COULD CAUSE A LOOP! WILL NOT BE IN THE LIST!" << std::endl;
					wasIn = true;
				}
			}

			if (!wasIn)
			{
				std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
				//Die Objekte müssen sortiert in die priority liste
				//Erste Node, der noch nie in der liste war und die priority liste ist noch leer : direkt vorne einfügen
				if (priorityList.empty())
				{
					priorityList.push_front(tmp->getPaths()->at(i)->getEndNode());
				}
				else
				{
					//Ansonsten kopieren wir die Elemente aus der priority liste solange in eine andere liste, bis wir eine Einfügeposition für den aktuell einzufügenden Node gefunden haben
					std::list<GraphNode*> tmp2;
					while (!priorityList.empty())
					{
						if (priorityList.front()->getDistanceToGoal() < tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal())
						{
							break;
						}
						else
						{
							tmp2.push_front(priorityList.front());
							priorityList.pop_front();
						}
					}
					//Der einzufügende Node wird in die Liste getan
					priorityList.push_front(tmp->getPaths()->at(i)->getEndNode());
					//Alle anderen, ausgeschnittenen Nodes, werden wieder zurück in die liste getan
					while (!tmp2.empty())
					{
						priorityList.push_front(tmp2.front());
						tmp2.pop_front();
					}
					tmp2.clear();
				}

			}
			wasIn = false;

		
		}
		//Wir updaten die Liste mit den neuen Pfaden
		while (!priorityList.empty())
		{
			pathList.push(priorityList.front());
			std::cout << priorityList.front()->getName() << "...is the Node who will be add to the Stack! " << std::endl;
			priorityList.pop_front();
		}

	}

	std::string test = pathList.top()->getName();
	std::cout << "CONTROLL CHECK, G IS GOAL: " << test << std::endl;
}

void beamSearch(GraphNode* s, GraphNode* g, int w)
{
	std::cout << "BEAM SEARCH (BFS) WILL BE STARTED!" << std::endl;

	std::queue<GraphNode*> pathList;
	std::cout << "S GO ONTO THE QUEUE!" << std::endl;
	pathList.push(s);

	std::vector<GraphNode*> wastedList;
	std::list<GraphNode*> priorityList;

	GraphNode* tmp;
	bool wasIn = false;

	while (pathList.front()->getName() != g->getName() && !pathList.empty())
	{
		std::cout << "FRONT ELEMENT OF THE LIST GOES OUT: " << pathList.front()->getName() << std::endl;
		tmp = pathList.front();
		pathList.pop();
		wastedList.push_back(tmp);

		for (int i = 0; i < tmp->getPaths()->size(); i++)
		{
			for (int j = 0; j < wastedList.size(); j++)
			{
				if (tmp->getPaths()->at(i)->getEndNode()->getName() == wastedList.at(j)->getName())
				{
					std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...COULD CAUSE A LOOP! WILL NOT BE IN THE LIST!" << std::endl;
					wasIn = true;
				}
			}

			if (!wasIn)
			{
				std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
				//Die Objekte müssen sortiert in die priority liste
				//Erste Node, der noch nie in der liste war und die priority liste ist noch leer : direkt vorne einfügen
				if (priorityList.empty())
				{
					priorityList.push_front(tmp->getPaths()->at(i)->getEndNode());
				}
				else
				{
					//Ansonsten kopieren wir die Elemente aus der priority liste solange in eine andere liste, bis wir eine Einfügeposition für den aktuell einzufügenden Node gefunden haben
					std::list<GraphNode*> tmp2;
					while (!priorityList.empty())
					{
						if (priorityList.front()->getDistanceToGoal() < tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal())
						{
							break;
						}
						else
						{
							tmp2.push_front(priorityList.front());
							priorityList.pop_front();
						}
					}
					//Der einzufügende Node wird in die Liste getan
					priorityList.push_front(tmp->getPaths()->at(i)->getEndNode());
					//Alle anderen, ausgeschnittenen Nodes, werden wieder zurück in die liste getan
					while (!tmp2.empty())
					{
						priorityList.push_front(tmp2.front());
						tmp2.pop_front();
					}
					tmp2.clear();
				}

			}
			wasIn = false;


		}
		//Wir updaten die Liste mit den neuen Pfaden, aber nur die w-nächsten Pfade werden übernommen, nicht alle 
		int wtmp = 0;
		while (!priorityList.empty() && wtmp <= w )
		{
			pathList.push(priorityList.back());
			std::cout << priorityList.back()->getName() << "...is the Node who will be add to the Queue! " << std::endl;
			priorityList.pop_back();
			w++;
		}

	}

	std::string test = pathList.front()->getName();
	std::cout << "CONTROLL CHECK, G IS GOAL: " << test << std::endl;
}


void bestFirstSearcch(GraphNode* s, GraphNode* g)
{

	std::cout << "BEST FIRST SEARCH  WILL BE STARTED!" << std::endl;

	std::vector<GraphNode*> pathList;
	std::cout << "S GO INTO THE LIST!" << std::endl;
	pathList.push_back(s);

	std::vector<GraphNode*> wastedList;
	std::list<GraphNode*> priorityList;

	GraphNode* tmp;
	bool wasIn = false;

	//Wir gehen über die Liste, solange bis der Zielknoten vorne (in diesem Falle hinten) in der Liste steht
	while (pathList.back()->getName() != g->getName() && !pathList.empty())
	{
		std::cout << "FRONT ELEMENT OF THE LIST GOES OUT: " << pathList.back()->getName() << std::endl;
		tmp = pathList.back();
		pathList.pop_back();
		wastedList.push_back(tmp);

		//wir gehen alle Nachbarn vom vordersten Element, was nun raus ist, durch
		for (int i = 0; i < tmp->getPaths()->size(); i++)
		{
			//Wir schauen, ob wir eine Loop gefunden haben, also das Kind schon mal als Parent aufgetreten ist
			for (int j = 0; j < wastedList.size(); j++)
			{
				if (tmp->getPaths()->at(i)->getEndNode()->getName() == wastedList.at(j)->getName())
				{
					std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...COULD CAUSE A LOOP! WILL NOT BE IN THE LIST!" << std::endl;
					wasIn = true;
				}
			}

			//Wen der Nachbar keine Loop erzeugt, wird er der Liste hinzugefügt
			if (!wasIn)
			{
				std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
				pathList.push_back(tmp->getPaths()->at(i)->getEndNode());

			}
			wasIn = false;
		}

		//Die pathList wird komplett sortiert, so dass an der back()-Stelle der kürzeste Weg steht
		GraphNode* save;
		for (int k = 1; k < pathList.size(); k++)
		{
			for (int l = 0; l < pathList.size() - k; l++)
			{
				if (pathList.at(l)->getDistanceToGoal() < pathList.at(l + 1)->getDistanceToGoal())
				{
					save = pathList.at(l + 1);
					pathList.at(l + 1) = pathList.at(l);
					pathList.at(l) = save;
				}
			}
		}

	}

	std::string test = pathList.back()->getName();
	std::cout << "CONTROLL CHECK, G IS GOAL: " << test << std::endl;
}

void branchAndBoundSearch(GraphNode* s, GraphNode* g)
{

}


int main()
{
	glfwInit();

	Window testWindow(50, 50, 800, 600, "testWindow");
	glfwMakeContextCurrent(testWindow.getWindow());

	std::cout << "THE GRAPH WILL BE INITIALIZED!" << std::endl;
	Scene kiScene("ki");

	//Test Cases, see the wiki page for the Link, where you can find the Examples I used here
	Graph testGraph();
	GraphNode nodeS("S");
	GraphNode nodeA("A");
	GraphNode nodeB("B");
	GraphNode nodeC("C");
	GraphNode nodeD("D");
	GraphNode nodeE("E");
	GraphNode nodeF("F");
	GraphNode nodeG("G");

	nodeS.setDistanceToGoal(20);
	nodeA.setDistanceToGoal(15);
	nodeB.setDistanceToGoal(9);
	nodeC.setDistanceToGoal(4);
	nodeD.setDistanceToGoal(10);
	nodeE.setDistanceToGoal(8);
	nodeF.setDistanceToGoal(3);
	nodeG.setDistanceToGoal(0);

	Path pathS1(3, &nodeS);
	Path pathS2(4, &nodeS);

	Path pathA1(3, &nodeA);
	Path pathA2(5, &nodeA);
	Path pathA3(4, &nodeA);

	Path pathB1(4, &nodeB);
	Path pathB2(5, &nodeB);

	Path pathC1(4, &nodeC);

	Path pathD1(4, &nodeD);
	Path pathD2(5, &nodeD);
	Path pathD3(2, &nodeD);

	Path pathE1(2, &nodeE);
	Path pathE2(5, &nodeE);
	Path pathE3(4, &nodeE);

	Path pathF1(4, &nodeF);
	Path pathF2(3, &nodeF);

	Path pathG1(3, &nodeG);

	//Schönerer Aufruf für die Übersicht wäre: nodeS.addPath(distanz, Endnode)
	//Klappt nicht wegen den gegeinseitigen Includes
	nodeS.addPath(&pathA1);
	nodeS.addPath(&pathD1);

	nodeA.addPath(&pathS1);
	nodeA.addPath(&pathD2);
	nodeA.addPath(&pathB1);

	nodeB.addPath(&pathA3);
	nodeB.addPath(&pathE2);
	nodeB.addPath(&pathC1);

	nodeC.addPath(&pathB1);

	nodeD.addPath(&pathS2);
	nodeD.addPath(&pathA2);
	nodeD.addPath(&pathE1);

	nodeE.addPath(&pathD3);
	nodeE.addPath(&pathB2);
	nodeE.addPath(&pathF1);
	
	nodeF.addPath(&pathE3);
	nodeF.addPath(&pathG1);

	nodeG.addPath(&pathF2);

	/*firstBasicMethod(&nodeS, &nodeG);
	std::cout << "------------------------" << std::endl;
	dfsMethod(&nodeS, &nodeG);
	std::cout << "------------------------" << std::endl;
	bfsMethod(&nodeS, &nodeG);
	std::cout << "------------------------" << std::endl;
	hillClimbing(&nodeS, &nodeG);
	std::cout << "------------------------" << std::endl;*/
	//beamSearch(&nodeS, &nodeG, 1);
	std::cout << "------------------------" << std::endl;
	bestFirstSearcch(&nodeS, &nodeG);

	while (!glfwWindowShouldClose(testWindow.getWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(testWindow.getWindow());
		glfwPollEvents();
	}

	glfwDestroyWindow(testWindow.getWindow());
	glfwTerminate();

	return 0;
}