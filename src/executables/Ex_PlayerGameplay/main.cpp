#include <GL/glew.h>

#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/MaterialInclude.h>
#include <GeKo_Graphics/GeometryInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>

#include <GeKo_Graphics/AIInclude.h>

#include <GeKo_Graphics/Scenegraph/BoundingSphere.h>
#include <GeKo_Physics/CollisionTest.h>

#include "GeKo_Graphics/Camera/Trackball.h"

#include <GeKo_Gameplay/Object/Object.h>
#include <GeKo_Gameplay/Object/AI.h>
#include <GeKo_Gameplay/Object/Geko.h>
#include <GeKo_Gameplay/Object/StaticObject.h>

#include <GeKo_Graphics/Geometry/TreeMesh.h>
#include <GeKo_Graphics/Geometry/AntMesh.h>
#include <GeKo_Graphics/Geometry/AntHomeMesh.h>

#include <GeKo_Gameplay/AI_Decisiontree/DecisionTree.h>
#include <GeKo_Gameplay/FightSystem/FightSystem.h>

#include <GeKo_Gameplay/Item/Item.h>

#include <GeKo_Gameplay/Questsystem/Quest.h>
#include <GeKo_Gameplay/Questsystem/Goal_Collect.h>

#include <GeKo_Graphics/Camera/StrategyCamera.h>

#include <GeKo_Graphics/Observer/ObjectObserver.h>
#include <GeKo_Graphics/Observer/CollisionObserver.h>
#include <GeKo_Graphics/Observer/GravityObserver.h>

#include <list>
#include <queue>
#include <stack>


InputHandler iH;
StrategyCamera cam("Trackball");


Geko geko("Geko", glm::vec3(10.0, 10.0, 10.0));

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	iH.getActiveInputMap()->setGLFWwindow(window);

	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			activeMap.at(key)();
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}
}

void mouse_callback(GLFWwindow* window)
{
	int i = 0;
	if (glfwGetMouseButton(window, i) == GLFW_PRESS)
	{
		std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

		iH.getActiveInputMap()->setGLFWwindow(window);

		for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
			if (it->first == i)
				activeMap.at(i)();
			if (it == activeMap.end())
				std::cout << "Key is not mapped to an action" << std::endl;
		}
	}
	else{
		cam.updateCursor(window);
	}
}

void mouseScroll_callback(GLFWwindow* window, double offsetX, double offSetY)
{

	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	iH.getActiveInputMap()->setGLFWwindow(window);

	if (offSetY < 0)
	{
		for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
			if (it->first == 001)
				activeMap.at(001)();
			if (it == activeMap.end())
				std::cout << "Key is not mapped to an action" << std::endl;
		}
	}
	else{
		for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
			if (it->first == 002)
				activeMap.at(002)();
			if (it == activeMap.end())
				std::cout << "Key is not mapped to an action" << std::endl;
		}
	}
}

//Mouse Move Callback for rotating the view
double lastX, lastY;
void mouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
	geko.rotateView(xPos - lastX, yPos - lastY);
	lastX = xPos;
	lastY = yPos;
}



int main()
{

	// Start Konifguration - Window, Context, Camera and Callbacks //
	glfwInit();

	Window testWindow(500, 50, 800, 600, "testWindow");
	glfwMakeContextCurrent(testWindow.getWindow());

	//Set Camera to another position
	//cam.setPosition(glm::vec4(0.0, 0.0, 20.0, 1.0));
	cam.setCenter(glm::vec4(0.0, 0.0, 20.0, 1.0));
	cam.setName("TrackballCam");
	cam.setKeySpeed(2.0);
	cam.setNearFar(0.0001, 100);

	//Callback for Camera and Player
	glfwSetKeyCallback(testWindow.getWindow(), key_callback);
//	glfwSetCursorPosCallback(testWindow.getWindow(), mouseMoveCallback);
	glfwSetScrollCallback(testWindow.getWindow(), mouseScroll_callback);

	glewInit();

	// Shader  and Renderer Initialization //
	//Shader for Objects
	VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/Vertex-Shaders/TextureShader3D.vert")));
	FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/Fragment-Shaders/TextureShader3D.frag")));
	ShaderProgram shader(vs, fs);

	//Shader for a Skybox
	VertexShader vsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.vert")));
	FragmentShader fsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.frag")));
	ShaderProgram shaderSkybox(vsSkybox, fsSkybox);

	//Renderer with context
	OpenGL3Context context;
	Renderer renderer(context);

	//Level and Scene
	Level testLevel("testLevel");
	Scene testScene("testScene");
	testLevel.addScene(&testScene);
	testLevel.changeScene("testScene");

	//Add Camera to scenegraph
	testScene.getScenegraph()->addCamera(&cam);
	testScene.getScenegraph()->getCamera("TrackballCam");
	testScene.getScenegraph()->setActiveCamera("TrackballCam");

	//Set all InputMaps and set one InputMap active
	iH.setAllInputMaps(*(testScene.getScenegraph()->getActiveCamera()));
	iH.changeActiveInputMap("Strategy");

	// ==============================================================
	// == Object (ant, afraid) ======================================
	// ==============================================================
	Teapot teaAnt; 
	Texture texCV((char*)RESOURCES_PATH "/cv_logo.bmp");
	//AntMesh antMesh;
	Node aiNodeFlick("Flick");

	aiNodeFlick.addGeometry(&teaAnt);
	aiNodeFlick.addTexture(&texCV);
	
	testScene.getScenegraph()->getRootNode()->addChildrenNode(&aiNodeFlick);
	
	AI ant_Flick;
	ant_Flick.setAntAfraid();
	aiNodeFlick.setObject(&ant_Flick);

	// ==============================================================
	// == Object (ant, aggressiv) ===================================
	// ==============================================================
	AntMesh antMesh;
	Node aiNodeFlack("Flack");

	//aiNodeFlack.addGeometry(&teaAnt);
	aiNodeFlack.addGeometry(&antMesh);
	aiNodeFlack.addTexture(&texCV);

	testScene.getScenegraph()->getRootNode()->addChildrenNode(&aiNodeFlack);

	AI ant_Flack;
	ant_Flack.setAntAggressiv();
	aiNodeFlack.setObject(&ant_Flack);

	// ==============================================================
	// == Object (Tree) =============================================
	// ==============================================================

	Texture texBrick((char*)RESOURCES_PATH "/brick.bmp");
	//TreeMesh treeMesh;
	Teapot teaTree;
	TreeMesh treeMesh;

	Node treeNode("CookieTree");
	StaticObject tree;
	tree.setTree();

	treeNode.setObject(&tree);
	treeNode.addTexture(&texCV);
	treeNode.addGeometry(&treeMesh);
	glm::vec3 posFood(10.0, 0.0, -5.0);
	treeNode.addTranslation(posFood);
	treeNode.getBoundingSphere()->radius = 2.0;

	testScene.getScenegraph()->getRootNode()->addChildrenNode(&treeNode);

	// ==============================================================
	// == Object (AntHome) ==========================================
	// ==============================================================

	//TreeMesh treeMesh;
	AntHomeMesh homeMesh;

	Node homeNode("AntHome");
	StaticObject home;
	//home.setTree();

	homeNode.setObject(&home);
	homeNode.addTexture(&texBrick);
	homeNode.addGeometry(&homeMesh);
	glm::vec3 posHome(1.0, 0.0, 1.0);
	homeNode.addTranslation(posHome);
	homeNode.getBoundingSphere()->radius = 0.5;

	testScene.getScenegraph()->getRootNode()->addChildrenNode(&homeNode);

	// ==============================================================
	// == Player ====================================================
	// ==============================================================

	Teapot teaPlayer;
//	Texture texBrick((char*)RESOURCES_PATH "/brick.bmp");

	Node playerNode("Player");
	playerNode.addGeometry(&teaPlayer);
	playerNode.addTexture(&texBrick);
	playerNode.setObject(&geko);
	geko.move(glm::vec3(10.0, 0.0, 10.0));

	//Add the node to the Scene
	testScene.getScenegraph()->getRootNode()->addChildrenNode(&playerNode);

	// ==============================================================
	// == Questsystem ====================================================
	// ==============================================================
	//QuestHandler questhandler;

	Quest questCollect(1);
	questCollect.setActive(true);
	Goal_Collect goalCollect(1);
	Goal_Collect goalCollect3(3);
	questCollect.addGoal(&goalCollect);
	questCollect.addGoal(&goalCollect3);

	Quest questCollect2(2);
	questCollect2.setActive(true);
	Goal_Collect goalCollect2(2);
	questCollect2.addGoal(&goalCollect2);
	
	goalCollect.setGoalCount(50);
	goalCollect2.setGoalCount(50);
	goalCollect3.setGoalCount(50);

	goalCollect.setItemType(ItemType::BRANCH);
	goalCollect2.setItemType(ItemType::BRANCH);
	goalCollect3.setItemType(ItemType::COOKIE);

	testLevel.getQuestHandler()->addQuest(&questCollect);
	testLevel.getQuestHandler()->addQuest(&questCollect2);
	/*questhandler.addQuest(&questCollect);
	questhandler.addQuest(&questCollect2);*/

	//std::cout << "GRÖßE DES QUESTHANDLERS : " << questhandler.getQuests().size() << std::endl;


	// ==============================================================
	// == Collision, FightSystem=====================================
	// ==============================================================

// Bounding Box creation for the objects and collision test //
	CollisionTest collision;
	collision.collectNodes(testScene.getScenegraph()->getRootNode());

	FightSystem fight;

	//===================================================================//
	//==================Setting up the Observers========================//
	//==================================================================//
	ObjectObserver aiObserver(&testLevel);
	ant_Flick.addObserver(&aiObserver);
	ant_Flack.addObserver(&aiObserver);

	ObjectObserver playerObserver(&testLevel);
	geko.addObserver(&playerObserver);

	CollisionObserver colObserver(&testLevel);
	collision.addObserver(&colObserver);

	GravityObserver gravityObserver(&testLevel);
	collision.addObserver(&gravityObserver);


		

	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(testWindow.getWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		mouse_callback(testWindow.getWindow());

		collision.update();
			//fight.gekoVSai(&geko, &ant_Flick);
			//fight.objectVSobject(&geko, &ant_Flick);
		
		ant_Flick.update();
		ant_Flack.update();

		//Recognizing if the player wants to move its character
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_UP))
		{
			geko.moveForward();
		}
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_DOWN))
		{
			geko.moveBackward();
		}
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_RIGHT))
		{
			geko.moveRight();
		}
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_LEFT))
		{
			geko.moveLeft();
		}

		geko.update(deltaTime);

		//Render the Player and AI
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
