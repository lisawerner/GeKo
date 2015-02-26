#include <GL/glew.h>
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/MaterialInclude.h>
#include <GeKo_Graphics/ObjectInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>
#include "GeKo_Graphics/Camera/Pilotview.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

InputHandler iH;
Pilotview cam("Pilotview");

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			activeMap.at(key)();
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}
}

int main()
{
	glfwInit();

	Window testWindow(50, 50, WINDOW_WIDTH, WINDOW_HEIGHT, "Graphic Showcase");
	glfwMakeContextCurrent(testWindow.getWindow());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
  // You have to set a camera name
  cam.setName("PilotviewCam");
  cam.setPosition(glm::vec4(0.0, 0.5, 3.0, 1.0));
  cam.setNearFar(0.01f, 100.0f);

  // Set all InputMaps and set one InputMap active
  iH.setAllInputMaps(cam);
  iH.changeActiveInputMap("Pilotview");

	//Callback
	glfwSetKeyCallback(testWindow.getWindow(), key_callback);

	glewInit();

	//our renderer
	OpenGL3Context context;
	Renderer renderer(context);

  //our object
	Cube cube;
	Teapot teapot;
	
  Rect plane;
  plane.setTcoords(
    glm::vec2(0, 0),
    glm::vec2(4, 0),
    glm::vec2(0, 4),
    glm::vec2(4, 4)
  );

	//our textures
  Texture bricks((char*)RESOURCES_PATH "/bricks_diffuse.png");
  Texture bricks_normal((char*)RESOURCES_PATH "/bricks_normal.png");
  Texture bricks_height((char*)RESOURCES_PATH "/bricks_height.png");

  Texture stone((char*)RESOURCES_PATH "/diffusemap_stone.png");
  Texture stone_normal((char*)RESOURCES_PATH "/normalmap_stone.png");
  Texture stone_height((char*)RESOURCES_PATH "/heightmap_stone.png");

	Texture marble((char*)RESOURCES_PATH "/seamless_marble.jpg");
	Texture chrome((char*)RESOURCES_PATH "/chrome.jpg");

	//Scene creation 
	Level testLevel("testLevel");
	Scene testScene("testScene");
	testLevel.addScene(testScene);
	testLevel.changeScene("testScene");

	//Add Camera to scenegraph
	testScene.getScenegraph()->addCamera(&cam);
	testScene.getScenegraph()->getCamera("PilotviewCam");
  testScene.getScenegraph()->setActiveCamera("PilotviewCam");

	Node cube1("cube1");
	cube1.addGeometry(&cube);
  cube1.addTexture(&bricks);
  cube1.addNormalMap(&bricks_normal);
  cube1.addHeightMap(&bricks_height,0.07,0.1,true);
	cube1.setModelMatrix(glm::translate(cube1.getModelMatrix(), glm::vec3(-0.7, 0.35, 0.5)));
  cube1.setModelMatrix(glm::scale(cube1.getModelMatrix(), glm::vec3(0.5, 0.5, 0.5)));

	Node cube2("cube2");
	cube2.addGeometry(&cube);
	cube2.addTexture(&bricks);
  cube2.addNormalMap(&bricks_normal);
  cube2.addHeightMap(&bricks_height,0.07, 0.1, true);
	cube2.setModelMatrix(glm::translate(cube2.getModelMatrix(), glm::vec3(0.8, 0.35, 0.5)));
  cube2.setModelMatrix(glm::scale(cube2.getModelMatrix(), glm::vec3(0.5, 0.5, 0.5)));


	Node wallNode1("wall1");
	wallNode1.addGeometry(&plane);
  wallNode1.addTexture(&marble);
	wallNode1.setModelMatrix(glm::translate(wallNode1.getModelMatrix(), glm::vec3(0.0, 0.1, 0.2)));
	wallNode1.setModelMatrix(glm::rotate(wallNode1.getModelMatrix(), -90.0f, glm::vec3(1.0, 0.0, 0.0)));
	wallNode1.setModelMatrix(glm::scale(wallNode1.getModelMatrix(), glm::vec3(1.5, 1.5, 1.5)));
  

	Node wallNode2("wall2");
	wallNode2.addGeometry(&plane);
  wallNode2.addTexture(&stone);
  wallNode2.addNormalMap(&stone_normal);
  wallNode2.addHeightMap(&stone_height, 0.07, 0.1);
	wallNode2.setModelMatrix(glm::translate(wallNode2.getModelMatrix(), glm::vec3(0.0, 1.0, -0.2)));
	wallNode2.setModelMatrix(glm::scale(wallNode2.getModelMatrix(), glm::vec3(1.5, 1.5, 1.5)));


	Node teaNode("teaNode");
	teaNode.addGeometry(&teapot);
	teaNode.addTexture(&chrome);
	teaNode.setModelMatrix(glm::translate(teaNode.getModelMatrix(), glm::vec3(0.2, 0.3, 1.0)));
	teaNode.setModelMatrix(glm::scale(teaNode.getModelMatrix(), glm::vec3(0.3, 0.3, 0.3)));


	//Creating a scenegraph
	testScene.getScenegraph()->getRootNode()->addChildrenNode(&wallNode1);
	//testScene.getScenegraph()->getRootNode()->addChildrenNode(&wallNode2);
	testScene.getScenegraph()->getRootNode()->addChildrenNode(&cube1);
	testScene.getScenegraph()->getRootNode()->addChildrenNode(&cube2);
	testScene.getScenegraph()->getRootNode()->addChildrenNode(&teaNode);

  Node lights = Node("Root");
  Sphere lightSphere = Sphere();

  for (int i = 0; i < 1; i++)
    for (int j = 0; j < 3; j++)
    {
      Node *newLight = new Node(std::string("Node_" + std::to_string(i) + std::to_string(j)));
      newLight->addGeometry(&lightSphere);
      newLight->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(i*1.5, 1.0f, j*1.5)));
      //newLight.setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 1, 1.0f)));
      newLight->setModelMatrix(glm::scale(newLight->getModelMatrix(), glm::vec3(2.0, 2.0, 2.0)));
      lights.addChildrenNode(newLight);
    }

  renderer.useDeferredShading(true,&lights,new glm::fvec3(1.0,1.0,0.8));
  renderer.useSSAO(true);        
  //renderer.useReflections(true); 
  renderer.useBloom(true);
  renderer.useAntiAliasing(true);
	
	double startTime = glfwGetTime();
	//Renderloop
  int outputFPS = 0;
	while (!glfwWindowShouldClose(testWindow.getWindow()))
	{
    // You have to compute the delta time
    cam.setSensitivity(glfwGetTime() - startTime);

    if (!(outputFPS % 20))
      std::cout <<  "FPS: " << static_cast<int> (1 / (glfwGetTime() - startTime)) << std::endl;

    outputFPS++;

    startTime = glfwGetTime();
		renderer.renderScene(testScene,testWindow);
	}

	glfwDestroyWindow(testWindow.getWindow());
	glfwTerminate();

	return 0;
}