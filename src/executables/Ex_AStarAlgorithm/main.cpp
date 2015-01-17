#include <GL/glew.h>
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/MaterialInclude.h>
#include <GeKo_Graphics/ObjectInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>
#include <GeKo_Graphics/AIInclude.h>
#include <GeKo_Gameplay/Player/GekoAI.h>
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

AStarNode* AStarAlgorithmReturn(AStarNode* s, AStarNode* g)
{
	std::cout << "A*-ALGORITHM WILL BE STARTED" << std::endl;

	std::vector<AStarNode*> pathList;
	std::cout << "S GOES INTO THE PATHLIST" << std::endl;
	pathList.push_back(s);

	std::vector<AStarNode*> wastedList;

	AStarNode* tmp;
	bool wasIn = false;
	bool shorterPathFound = false;

	int distanceTraveled = 0;

	bool secondOut = false;
	AStarNode* returnNode;

	while (pathList.back()->getName() != g->getName() && !pathList.empty())
	{
		std::cout << "FRONT ELEMENT OF THE LIST GOES OUT: " << pathList.back()->getName() << std::endl;
		tmp = pathList.back();
		wastedList.push_back(pathList.back());
		pathList.pop_back();

		if (secondOut)
		{
			std::cout << "THE RETURN ELEMENT IS FOUND!" << std::endl;
			returnNode = tmp;
			secondOut = false;
		}

		if (tmp->getName() == s->getName())
		{
			secondOut = true;
		}

		//Neue Pfade hinzufügen
		for (int i = 0; i < tmp->getPaths()->size(); i++)
		{

			std::cout << "NEIGHBOR OF..." << tmp->getName() << "...IS..." << tmp->getPaths()->at(i)->getEndNode()->getName() << std::endl;
			//Überprüfung, ob der aktuelle Endknoten des Pfades den man hinzufügen will, den Knoten vorher besucht hat, dann wäre dies ein Rückpfad, den wir nicht drin haben wollen
			if (tmp->getPaths()->at(i)->getEndNode()->getName() != tmp->getVisitor()->getName() && tmp->getPaths()->at(i)->getEndNode()->getName() != s->getName())
			{


				//Wir müssen nun schauen, ob ein Knoten mit dem selben Namen schon in unserer Pfadliste ist
				//Wenn ja, wollen wir eine Kopie erstellen, denn wir wollen mehrere Pfade zu einem Knoten speichern können
				AStarNode* copyNode = new AStarNode("COPY");
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


					std::cout << "TRAVELLED DISTANCE OF..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE RAISED BY..." << tmp->getPaths()->at(i)->getTimeToTravel() << "...+..." << tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() << "...!" << std::endl;
					tmp->getPaths()->at(i)->getEndNode()->setDistanceTravelled(tmp->getPaths()->at(i)->getTimeToTravel() + tmp->getDistanceTravelled());
					tmp->getPaths()->at(i)->getEndNode()->setTemporary(tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() + tmp->getPaths()->at(i)->getEndNode()->getDistanceTravelled());

					std::cout << "TRAVELLED DISTANCE OF..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...IS NOW..." << tmp->getPaths()->at(i)->getEndNode()->getTemporary() << "...!" << std::endl;


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
							std::cout << "THE NODE..." << pathList.at(n)->getName() << "...WILL BE DELETED, IT HAS A LONGER TRAVEL TIME THEN THE NEW ONE..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "!" << std::endl;
							pathList.erase(pathList.begin() + n);
						}
					}

					if (!shorterPathFound)
					{
						std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
						pathList.push_back(tmp->getPaths()->at(i)->getEndNode());
						tmp->getPaths()->at(i)->getEndNode()->setVisitor(tmp);
					}
					else{
						std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...WILL BE NOT ADD, SHORTER PATH FOUND!" << std::endl;
						shorterPathFound = false;
					}


				}
				//Falls der Node schon über einen anderen Pfad erreicht wurde, dann erstellen wir eine Kopie des Nodes und fügen diese Kopie zusätzlich in die Liste
				else{
					copyNode->setDistanceTravelled(-(copyNode->getDistanceTravelled()));
					std::cout << "TRAVELLED DISTANCE OF...NEW--" << copyNode->getName() << "...WILL BE RAISED BY..." << tmp->getPaths()->at(i)->getTimeToTravel() << "...+..." << tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() << "...!" << std::endl;
					copyNode->setDistanceTravelled(tmp->getPaths()->at(i)->getTimeToTravel() + tmp->getDistanceTravelled());
					copyNode->setTemporary(tmp->getPaths()->at(i)->getEndNode()->getDistanceToGoal() + copyNode->getDistanceTravelled());

					std::cout << "TRAVELLED DISTANCE OF...NEW--" << copyNode->getName() << "...IS NOW..." << copyNode->getTemporary() << "...!" << std::endl;


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
							std::cout << "THE NODE..." << pathList.at(n)->getName() << "...WILL BE DELETED, IT HAS A LONGER TRAVEL TIME THEN THE NEW ONE..." << copyNode->getName() << "!" << std::endl;
							pathList.erase(pathList.begin() + n);
						}
					}

					if (!shorterPathFound)
					{
						std::cout << "NEIGHBOUR...NEW--" << copyNode->getName() << "...WILL BE ADDED TO THE PATH LIST!" << std::endl;
						copyNode->setVisitor(tmp);
						pathList.push_back(copyNode);
					}
					else{
						std::cout << "NEIGHBOUR...NEW--" << copyNode->getName() << "...WILL NOT BE ADD, SHORTER PATH FOUND!" << std::endl;
						shorterPathFound = false;
					}
					wasIn = false;
				}

			}
			else{
				std::cout << "NEIGHBOUR..." << tmp->getPaths()->at(i)->getEndNode()->getName() << "...COULD CAUSE A LOOP! WILL NOT BE IN THE LIST!" << std::endl;
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
	std::cout << "CONTROLL CHECK, G IS GOAL: " << test << std::endl;
	std::cout << "TRAVELLED DISTANCE IS: " << pathList.back()->getDistanceTravelled() << std::endl;

	if (secondOut)
	{
		returnNode = g;
	}

	return returnNode;
}


int main()
{
	glfwInit();

	Window testWindow(50, 50, 800, 600, "testWindow");
	glfwMakeContextCurrent(testWindow.getWindow());
	//Set Camera to another position
	cam.setPosition(glm::vec4(0.0, 0.0, 5.0, 1.0));
	cam.setName("TrackballCam");
	cam.setKeySpeed(2.0);
	cam.setNearFar(0.0001, 100);
	//Callback for Camera and Player
	glfwSetKeyCallback(testWindow.getWindow(), key_callback);
//	glfwSetCursorPosCallback(testWindow.getWindow(), mouseMoveCallback);

	glewInit();

	//our shader
	VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.vert")));
	FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.frag")));
	ShaderProgram shader(vs, fs);

	VertexShader vsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.vert")));
	FragmentShader fsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.frag")));
	ShaderProgram shaderSkybox(vsSkybox, fsSkybox);

	//our renderer
	OpenGL3Context context;
	Renderer renderer(context);

	//our object
	Teapot tea;
	//our textures
	Texture texCV((char*)RESOURCES_PATH "/cv_logo.bmp");

	//Scene creation 
	Level testLevel("testLevel");
	Scene testScene("testScene");
	testLevel.addScene(testScene);
	testLevel.changeScene("testScene");

	//Add Camera to scenegraph
	testScene.getScenegraph()->addCamera(&cam);
	testScene.getScenegraph()->getCamera("TrackballCam");
	testScene.getScenegraph()->setActiveCamera("TrackballCam");

	//Set all InputMaps and set one InputMap active
	iH.setAllInputMaps(*(testScene.getScenegraph()->getActiveCamera()));
	iH.changeActiveInputMap("Trackball");
	//Create Nodes with geometry and texture
	Node testNode("testNode");
	testNode.addGeometry(&tea);
	testNode.addTexture(&texCV);

	std::cout << "THE GRAPH WILL BE INITIALIZED!" << std::endl;
	Scene kiScene("ki");

	//Test Cases, see the wiki page for the Link, where you can find the Examples I used here
	Graph<AStarNode, AStarAlgorithm> testGraph;

	AStarNode nodeS("S");
	AStarNode nodeA("A");
	AStarNode nodeB("B");
	AStarNode nodeC("C");
	AStarNode nodeD("D");
	AStarNode nodeE("E");
	AStarNode nodeF("F");
	AStarNode nodeG("G");

	AStarNode defaultNode("Default");

	nodeS.setPosition(glm::vec3(0.0, 0.0, 0.0));
	nodeA.setPosition(glm::vec3(-1.0, 0.0, -1.0));
	nodeB.setPosition(glm::vec3(-2.0, 0.0, -2.0));
	nodeC.setPosition(glm::vec3(-3.0, 0.0, -3.0));
	nodeD.setPosition(glm::vec3(-4.0, 0.0, -4.0));
	nodeE.setPosition(glm::vec3(-5.0, 0.0, -5.0));
	nodeF.setPosition(glm::vec3(-6.0, 0.0, -6.0));
	nodeG.setPosition(glm::vec3(-7.0, 0.0, -7.0));

	nodeS.setDistanceToGoal(11.0);
	nodeA.setDistanceToGoal(10.4);
	nodeB.setDistanceToGoal(6.7);
	nodeC.setDistanceToGoal(4.0);
	nodeD.setDistanceToGoal(8.9);
	nodeE.setDistanceToGoal(6.9);
	nodeF.setDistanceToGoal(3.0);
	nodeG.setDistanceToGoal(0.0);

	nodeS.setVisitor(&defaultNode);
	nodeA.setVisitor(&defaultNode);
	nodeB.setVisitor(&defaultNode);
	nodeC.setVisitor(&defaultNode);
	nodeD.setVisitor(&defaultNode);
	nodeE.setVisitor(&defaultNode);
	nodeF.setVisitor(&defaultNode);
	nodeG.setVisitor(&defaultNode);

	Path<AStarNode> pathSA(3, &nodeS, &nodeA);
	Path<AStarNode> pathSD(4, &nodeS, &nodeD);
	nodeS.addPath(&pathSA);
	nodeS.addPath(&pathSD);

	Path<AStarNode> pathAS(3, &nodeA, &nodeS);
	Path<AStarNode> pathAB(4, &nodeA, &nodeB);
	Path<AStarNode> pathAD(5, &nodeA, &nodeD);
	nodeA.addPath(&pathAS);
	nodeA.addPath(&pathAB);
	nodeA.addPath(&pathAD);

	Path<AStarNode> pathBA(4, &nodeB, &nodeA);
	Path<AStarNode> pathBC(4, &nodeB, &nodeC);
	Path<AStarNode> pathBE(5, &nodeB, &nodeE);
	nodeB.addPath(&pathBA);
	nodeB.addPath(&pathBC);
	nodeB.addPath(&pathBE);

	Path<AStarNode> pathCB(4, &nodeC, &nodeB);
	nodeC.addPath(&pathCB);

	Path<AStarNode> pathDS(4, &nodeD, &nodeS);
	Path<AStarNode> pathDA(5, &nodeD, &nodeA);
	Path<AStarNode> pathDE(2, &nodeD, &nodeE);
	nodeD.addPath(&pathDS);
	nodeD.addPath(&pathDA);
	nodeD.addPath(&pathDE);

	Path<AStarNode> pathED(2, &nodeE, &nodeD);
	Path<AStarNode> pathEB(5, &nodeE, &nodeB);
	Path<AStarNode> pathEF(4, &nodeE, &nodeF);
	nodeE.addPath(&pathED);
	nodeE.addPath(&pathEB);
	nodeE.addPath(&pathEF);

	Path<AStarNode> pathFE(4, &nodeF, &nodeE);
	Path<AStarNode> pathFG(3, &nodeF, &nodeG);
	nodeF.addPath(&pathFE);
	nodeF.addPath(&pathFG);


	Path<AStarNode> pathGF(3, &nodeG, &nodeF);
	nodeG.addPath(&pathGF);

	testGraph.addGraphNode(&nodeS);
	testGraph.addGraphNode(&nodeA);
	testGraph.addGraphNode(&nodeB);
	testGraph.addGraphNode(&nodeC);
	testGraph.addGraphNode(&nodeD);
	testGraph.addGraphNode(&nodeE);
	testGraph.addGraphNode(&nodeF);
	testGraph.addGraphNode(&nodeG);

	AStarAlgorithm pathfinding("pathfinding");
//	testGraph.setAlgorithm(&pathfinding);
//	testGraph.getAlgorithm()->startAlgorithm(&nodeS, &nodeG);



	//Now we have an Object represented by its currentPos on the field
	//The Object gets the position of the Spawnpoint S and starts to look for a new location
	//The Object also saves the last visited AStarNode

//	glm::vec3 currentPos = nodeS.getPosition();
////	std::cout << "CurrentPos_Start" << currentPos.x << " " << currentPos.y << " " << currentPos.z << std::endl;
//	AStarNode* lastVisited = &nodeS;
//
//	//We have a Listener which recognize changes on the Path on the field
//	//For demonstration, no changes will happening 
//	bool pathChanged = false;
////	std::cout << nodeG.getPosition().x << " " << nodeG.getPosition().y << " " << nodeG.getPosition().z << std::endl;
//
//	while (currentPos != nodeG.getPosition())
//	{
//		//std::cout << "CONTROLL CHECK 1" << std::endl;
//		AStarNode* nextPosition = AStarAlgorithmReturn(lastVisited, &nodeG);
//		std::cout << "CONTROLL CHECK NEXT POSITION : " << nextPosition->getName() << std::endl;
//		//We determine the difference between the currentPos of the Object and the Position of the next AStarNode
//		glm::vec3 differenceTMP = nextPosition->getPosition() - currentPos;
//		//As long as the Object did not have reached the nextPosition-Node, we want to let it go to the position in steps
//		while (currentPos != nextPosition->getPosition())
//		{
//
//			if (differenceTMP.x != 0)
//				currentPos.x += 0.5;
//			if (differenceTMP.y != 0)
//				currentPos.y += 0.5;
//			if (differenceTMP.z != 0){
//				currentPos.z += 0.5;
//				std::cout << "!!!!! CURRENT POS Z POSITION: " << currentPos.z << "!!!!!!!!" << std::endl;
//			}
//
//		}
//		//when he reached the nextPosition-Node, we change its lastVisited to this node an starting the search again
//		lastVisited = nextPosition;
//	}
//	std::cout << "THE AI-UNIT ARRIVED AT IT DESTINATION! " << std::endl;
	
	//AI Test with a basic class for movement and geometry!

	
	//GekoAI gekoAI("gekoAI", glm::vec3(nodeS.getPosition()));
	//testNode.setModelMatrix(glm::translate(testNode.getModelMatrix(), gekoAI.getCurrentPosition()));
	////testNode.setModelMatrix(glm::translate(testNode.getModelMatrix(), gekoAI.getCurrentPosition() + glm::vec3(3.0, 0.0, 0.0)));

	//testScene.getScenegraph()->getRootNode()->addChildrenNode(&testNode);
	//gekoAI.setNode(&testNode);

	//AStarNode* lastVisited = &nodeS;

	//while (gekoAI.getCurrentPosition().x < nodeG.getPosition().x)
	//{

	//	AStarNode* nextPosition = pathfinding.startAlgorithm(lastVisited, &nodeG);
	//	std::cout << nextPosition->getName() << std::endl;
	//	glm::vec3 differenceTMP = nextPosition->getPosition() - gekoAI.getCurrentPosition();

	//	while (gekoAI.getCurrentPosition().x < nextPosition->getPosition().x)
	//	{
	//		if (differenceTMP.x != 0){
	//			gekoAI.changePosition(gekoAI.getCurrentPosition() + glm::vec3(0.1, 0.0, 0.0));
	//			testNode.setModelMatrix(glm::translate(glm::mat4(1), gekoAI.getCurrentPosition()));
	//		}
	//	}
	//	lastVisited = nextPosition;
	//}
	//std::cout << "THE AI-UNIT ARRIVED AT IT DESTINATION! " << std::endl;


	GekoAI gekoAI("gekoAI", glm::vec3(nodeS.getPosition()));
	/*testNode.setModelMatrix(glm::translate(testNode.getModelMatrix(), gekoAI.getCurrentPosition()));*/
	//testNode.setModelMatrix(glm::translate(testNode.getModelMatrix(), gekoAI.getCurrentPosition() + glm::vec3(3.0, 0.0, 0.0)));

	testScene.getScenegraph()->getRootNode()->addChildrenNode(&testNode);
	gekoAI.setNode(&testNode);

	gekoAI.setStartAndEndNode(&nodeS, &nodeG);

	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(testWindow.getWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		gekoAI.update(deltaTime);
		//Render the Player
		glEnable(GL_DEPTH_TEST);

		shader.bind();
		shader.sendMat4("viewMatrix", cam.getViewMatrix());
		shader.sendMat4("projectionMatrix", cam.getProjectionMatrix());

		testScene.render(shader);
		shader.unbind();

		glfwSwapBuffers(testWindow.getWindow());
		glfwPollEvents();
	}

	glfwDestroyWindow(testWindow.getWindow());
	glfwTerminate();

	return 0;
}