//===================================================================//
//==================Your Includes===================================//
//==================================================================//
#include <GL/glew.h>

#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/GeometryInclude.h>
#include <GeKo_Graphics/Camera/StrategyCamera.h>
#include <GeKo_Graphics/Camera/Pilotview.h>
#include <GeKo_Graphics/ShaderInclude.h>

#include <GeKo_Graphics/AIInclude.h>
#include <GeKo_Gameplay/AI_Decisiontree/DecisionTree.h>
#include <GeKo_Gameplay/Object/Geko.h>
#include <GeKo_Gameplay/Object/AI.h>

#include <GeKo_Graphics/Geometry/AntMesh.h>
#include <GeKo_Graphics/Geometry/TreeMesh.h>
#include <GeKo_Graphics/Geometry/GekoMesh.h>
#include <GeKo_Graphics/Geometry/Plane.h>

#include <GeKo_Graphics/Geometry/Terrain.h>

#include <GeKo_Physics/CollisionTest.h>

#include <GeKo_Graphics/Observer/ObjectObserver.h>
#include <GeKo_Graphics/Observer/CollisionObserver.h>
#include <GeKo_Graphics/Observer/GravityObserver.h>
#include <GeKo_Graphics/Observer/SoundObserver.h>
#include <GeKo_Graphics/Observer/QuestObserver.h>
#include <GeKo_Graphics/Geometry/ForestData.h>

#include <GeKo_Gameplay/Questsystem/ItemReward.h>
#include <GeKo_Gameplay/Questsystem/ExpReward.h>
#include <GeKo_Gameplay/Questsystem/Goal_Kill.h>
#include <GeKo_Gameplay/Questsystem/Goal_Eaten.h>

#include <GeKo_Graphics/GUI/GUI.h>
#include <GeKo_Graphics/GUI/GUIComponents.hpp>


//===================================================================//
//==================Things you need globally==========================//
//==================================================================//
InputHandler iH;
StrategyCamera cam("StrategyCam");
Geko geko("Geko", glm::vec3(10.0f, 3.0, -5.0));
Renderer *renderer;
GUI *gui;
SoundFileHandler sfh = SoundFileHandler(1000);

//===================================================================//
//==================Callbacks for the Input==========================//
//==================================================================//

void playKey_callback(GLFWwindow* window)
{
	//Recognizing if the player wants to move its character
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		geko.moveForward();
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		geko.moveBackward();
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		geko.moveRight();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		geko.moveLeft();
	}

}

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

//===================================================================//
//==================Main Method=====================================//
//==================================================================//
int main()
{

	//===================================================================//
	//==================Things you need to start with====================//
	//==================================================================//
	glfwInit();

	Window testWindow(500, 50, 800, 600, "testWindow");
	glfwMakeContextCurrent(testWindow.getWindow());

	cam.setCenter(glm::vec4(40.0, 40.0, 40.0, 1.0));
	cam.setName("StrategyCam");
	cam.setKeySpeed(2.0);
	cam.setNearFar(0.01, 100);

	glfwSetKeyCallback(testWindow.getWindow(), key_callback);
	glfwSetScrollCallback(testWindow.getWindow(), mouseScroll_callback);

	glewInit();

	OpenGL3Context context;
	renderer = new Renderer(context);

	//===================================================================//
	//==================Shaders for your program========================//
	//==================================================================//
	VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/Vertex-Shaders/TextureShader3D.vert")));
	FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/Fragment-Shaders/TextureShader3D.frag")));
	ShaderProgram shader(vs, fs);

	//SHADER
	VertexShader vsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.vert")));
	FragmentShader fsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.frag")));
	ShaderProgram shaderSkybox(vsSkybox, fsSkybox);


	//===================================================================//
	//==================Object declarations - Geometry, Texture, Node=== //
	//==========================Object: Player===========================//
	Teapot teaPlayer;
	Texture texCV((char*)RESOURCES_PATH "/cv_logo.bmp");

	GekoMesh gekoMesh;
	geko.setExp(0.0);
	geko.setLevelThreshold(100.0);
	geko.setLevel(0);

	Node playerNode("Player");

	playerNode.addGeometry(&gekoMesh);
	playerNode.setObject(&geko);
	playerNode.addTexture(&texCV);

	geko.setSoundHandler(&sfh);
	geko.setSourceName(MOVESOUND, "SpielerFootsteps", RESOURCES_PATH "/Sound/Rascheln.wav");
	geko.setSourceName(BACKGROUNDMUSIC, "Hintergrund", RESOURCES_PATH "/Sound/jingle2.wav");
	geko.setSourceName(FIGHTSOUND, "Kampfsound", RESOURCES_PATH "/Sound/punch.wav");
	geko.setSourceName(EATSOUND, "Essen", RESOURCES_PATH "/Sound/Munching.wav");
	geko.setSourceName(QUESTSOUND, "Quest", RESOURCES_PATH "/Sound/jingle.wav");
	geko.setSourceName(ITEMSOUND, "Item", RESOURCES_PATH "/Sound/itempickup.wav");

	sfh.playSource("Hintergrund");
	sfh.setGain("Hintergrund", 0.5f);
	sfh.disableLooping("Essen");
	sfh.disableLooping("Quest");
	sfh.disableLooping("Item");

	playerNode.setCamera(&cam);


	//===================================================================//
	//==================Object declarations - Geometry, Texture, Node=== //
	//==========================Object: Terrain===========================//

	StaticObject terrainObject;
	terrainObject.setClassType(ClassType::TERRAIN);
	
	Texture terrainTex((char*)RESOURCES_PATH "/Grass2.jpg");

	Terrain terrain2((char*)RESOURCES_PATH "/heightmap.jpg", 0.0f, 0.0f);
	Node terrainNode2("Terrain");
	terrainNode2.addGeometry(&terrain2);
	terrainNode2.addTexture(&terrainTex);
	terrainNode2.setObject(&terrainObject);
	//terrainNode2.addTranslation(-50.0f, -50.0f, 35.0f);
	/*terrainNode2.addRotation(180, glm::vec3(0.0, 1.0, 0.0));*/

	//===================================================================//
	//==================Object declarations - Geometry, Texture, Node=== //
	//==========================Object: Skybox===========================//
	Cube cube;
	const char *textureNames[6] = {
		(char*)RESOURCES_PATH "/Skybox/PereaBeach1/posx.jpg",
		(char*)RESOURCES_PATH "/Skybox/PereaBeach1/negx.jpg",
		(char*)RESOURCES_PATH "/Skybox/PereaBeach1/posy.jpg",
		(char*)RESOURCES_PATH "/Skybox/PereaBeach1/negy.jpg",
		(char*)RESOURCES_PATH "/Skybox/PereaBeach1/posz.jpg",
		(char*)RESOURCES_PATH "/Skybox/PereaBeach1/negz.jpg"
		/*(char*)RESOURCES_PATH "/Color/testTex.png",
		(char*)RESOURCES_PATH "/Color/testTex.png",
		(char*)RESOURCES_PATH "/Color/testTex.png",
		(char*)RESOURCES_PATH "/Color/testTex.png",
		(char*)RESOURCES_PATH "/Color/testTex.png",
		(char*)RESOURCES_PATH "/Color/testTex.png"*/ };
	Skybox skybox(textureNames);
	Node skyboxNode("skybox");
	skyboxNode.addGeometry(&cube);

	//===================================================================//
	//==================Setting up the Level and Scene==================//
	//==================================================================//

	Level testLevel("testLevel");
	Scene testScene("testScene");
	testLevel.addScene(&testScene);
	testLevel.changeScene("testScene");
	testLevel.setTerrain(&terrain2);

	//===================================================================//
	//==================Generating Forest===============================//
	//==================================================================//

	TreeMesh tree;
	std::stringstream name;
	for (int i = 0; i<TreeData::forest1.size(); i++)
	{
		name << "Forest1Tree" << i;
		std::string stringname = name.str();
		StaticObject *treeStatic = new StaticObject();
		treeStatic->setTree(50 / TreeData::forest1.size());
		Node *treeNode = new Node(stringname);
		treeNode->addGeometry(&tree);
		treeNode->setObject(treeStatic);
		treeNode->addTranslation(TreeData::forest1[i].x, terrain2.getHeight(glm::vec2(TreeData::forest1[i].x, TreeData::forest1[i].z)), TreeData::forest1[i].z);
		treeNode->getBoundingSphere()->radius = 2.5;
		testScene.getScenegraph()->getRootNode()->addChildrenNode(treeNode);
		name.str("");

	}


	//==================Add Camera to Scene============================//
	testScene.getScenegraph()->addCamera(&cam);
	testScene.getScenegraph()->setActiveCamera("StrategyCam");

	//==================Set Input-Maps and activate one================//
	iH.setAllInputMaps(*(testScene.getScenegraph()->getActiveCamera()));
	iH.changeActiveInputMap("Strategy");

	//==================Add Objects to the Scene=======================//
	//==================Update the Bounding-Sphere 1st time============//

	testScene.getScenegraph()->getRootNode()->addChildrenNode(&playerNode);

	testScene.getScenegraph()->getRootNode()->addChildrenNode(&terrainNode2);

	//===================================================================//
	//==================Setting up the Collision=========================//
	//==================================================================//
	CollisionTest collision;
	collision.collectNodes(testScene.getScenegraph()->getRootNode());

	//===================================================================//
	//==================Setting up the Observers========================//
	//==================================================================//

	ObjectObserver playerObserver(&testLevel);
	SoundObserver soundPlayerObserver(&testLevel);
	geko.addObserver(&playerObserver);
	geko.addObserver(&soundPlayerObserver);

	CollisionObserver colObserver(&testLevel);
	collision.addObserver(&colObserver);
	collision.addObserver(&soundPlayerObserver);

	GravityObserver gravityObserver(&testLevel);
	collision.addObserver(&gravityObserver);



	//===================================================================//
	//==================Setting up the Gravity===========================//
	//==================================================================//
	Gravity gravity;
	playerNode.addGravity(&gravity);

	//===================================================================//
	//==================The Render-Loop==================================//
	//==================================================================//
	float lastTime = glfwGetTime();

	


	while (!glfwWindowShouldClose(testWindow.getWindow()))
	{
	

		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		
		mouse_callback(testWindow.getWindow());

		
		//===================================================================//
		//==================Update your Objects per Frame here =============//
		//==================================================================//
		collision.update();


		//===================================================================//
		//==================Input and update for the Player==================//
		//==================================================================//

		playKey_callback(testWindow.getWindow());
		geko.update(deltaTime);

		//===================================================================//
		//==================Render your Objects==============================//
		//==================================================================//

		//SKYBOX
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderSkybox.bind();
		glDisable(GL_DEPTH_TEST);
		shaderSkybox.sendMat4("viewMatrix", cam.getViewMatrix());
		shaderSkybox.sendMat4("projectionMatrix", cam.getProjectionMatrix());
		shaderSkybox.sendSkyboxTexture("testTexture", skybox.getSkyboxTexture());
		skyboxNode.render();
		shaderSkybox.unbind();

		glEnable(GL_DEPTH_TEST);
		renderer->renderScene(testScene, testWindow);

		

		//glEnable(GL_DEPTH_TEST);
	}



	glfwDestroyWindow(testWindow.getWindow());
	glfwTerminate();

	
	return 0;

}

