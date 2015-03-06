#include <GL/glew.h>
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/MaterialInclude.h>
#include <GeKo_Graphics/ObjectInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>
#include "GeKo_Graphics/Camera/Pilotview.h"
#include "GeKo_Graphics/GUI/GUI.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

InputHandler iH;
Pilotview cam("Pilotview");


glm::fvec3 *dsLightColor;
float *ssaoQuality;
float *ssaoRadius;
float *reflectionStrength;
GUI *gui;
GuiElement::ToggleButton *useShadowMappingButton;
GuiElement::ToggleButton *usePCFButton;
GuiElement::ToggleButton *useDeferredShadingButton;
GuiElement::ToggleButton *deferredShadingRotationButton;
GuiElement::ToggleButton *useSSAOButton;
GuiElement::ToggleButton *useReflectionsButton;
GuiElement::ToggleButton *useBloomButton;
GuiElement::ToggleButton *useFXAAButton;

//our renderer
OpenGL3Context context;
Renderer *renderer;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			activeMap.at(key)();
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}

  if (glfwGetKey(window, GLFW_KEY_F10))
    if (gui->visible()) gui->hide(); else gui->show();
}


void initGUI()
{
  //INIT GUI
  gui = new GUI("Settings - Hide [F10]", 400, 400);

  GuiElement::Header *shadowMappingHeader = new GuiElement::Header("Shadow Mapping");
  shadowMappingHeader->addElement(new GuiElement::Text("Use Shadow Mapping"));
  shadowMappingHeader->addElement(new GuiElement::SameLine);
  useShadowMappingButton = new GuiElement::ToggleButton(false, "on", "off");
  shadowMappingHeader->addElement(useShadowMappingButton);
  shadowMappingHeader->addElement(new GuiElement::Spacing);

  //TODO ADD FUNCTIONALITY
  shadowMappingHeader->addElement(new GuiElement::Text("Use PCF Soft Shadows"));
  shadowMappingHeader->addElement(new GuiElement::SameLine);
  usePCFButton = new GuiElement::ToggleButton(false, "on", "off");
  shadowMappingHeader->addElement(usePCFButton);
  shadowMappingHeader->addElement(new GuiElement::Spacing);

  //TODO add Light Position
  gui->addElement(shadowMappingHeader);
  //===============================================================================================


  GuiElement::Header *deferredShadingHeader = new GuiElement::Header("Deferred Shading");
  deferredShadingHeader->addElement(new GuiElement::Text("Use Deferred Shading"));
  deferredShadingHeader->addElement(new GuiElement::SameLine);
  useDeferredShadingButton = new GuiElement::ToggleButton(false, "on", "off");
  deferredShadingHeader->addElement(useDeferredShadingButton);
  deferredShadingHeader->addElement(new GuiElement::Spacing);

  GuiElement::ColorEditRGB *deferredShadingLightColorEdit = new GuiElement::ColorEditRGB("Lightcolor", dsLightColor);
  deferredShadingHeader->addElement(deferredShadingLightColorEdit);
  deferredShadingHeader->addElement(new GuiElement::Spacing);

  deferredShadingHeader->addElement(new GuiElement::Text("Rotate Lights"));
  deferredShadingHeader->addElement(new GuiElement::SameLine);
  deferredShadingRotationButton = new GuiElement::ToggleButton(false, "on", "off");
  deferredShadingHeader->addElement(deferredShadingRotationButton);
  deferredShadingHeader->addElement(new GuiElement::Spacing);

  gui->addElement(deferredShadingHeader);

  //===============================================================================================


  GuiElement::Header *ssaoHeader = new GuiElement::Header("Screen Space Ambient Occlusion");
  ssaoHeader->addElement(new GuiElement::Text("Use SSAO"));
  ssaoHeader->addElement(new GuiElement::SameLine);

  useSSAOButton = new GuiElement::ToggleButton(false, "on", "off");
  ssaoHeader->addElement(useSSAOButton);
  ssaoHeader->addElement(new GuiElement::Spacing);
  ssaoHeader->addElement(new GuiElement::SliderFloat("Quality", ssaoQuality, 0.0f, 100.0f));
  ssaoHeader->addElement(new GuiElement::Spacing);
  ssaoHeader->addElement(new GuiElement::SliderFloat("Radius", ssaoRadius, 0.0f, 0.5f));
  ssaoHeader->addElement(new GuiElement::Spacing);

  gui->addElement(ssaoHeader);

  //===============================================================================================
  GuiElement::Header *reflectionsHeader = new GuiElement::Header("Screen Space Reflections");
  reflectionsHeader->addElement(new GuiElement::Text("Use Screen Space Reflections"));
  reflectionsHeader->addElement(new GuiElement::SameLine);

  useReflectionsButton = new GuiElement::ToggleButton(false, "on", "off");
  reflectionsHeader->addElement(useReflectionsButton);
  reflectionsHeader->addElement(new GuiElement::Spacing);
  reflectionsHeader->addElement(new GuiElement::SliderFloat("Reflection Strength", reflectionStrength, 0.0f, 0.4f));
  reflectionsHeader->addElement(new GuiElement::Spacing);
  
  gui->addElement(reflectionsHeader);
  //===============================================================================================

  //===============================================================================================
  GuiElement::Header *postProcessingHeader = new GuiElement::Header("Postprocessing");

  //BLOOM
  postProcessingHeader->addElement(new GuiElement::Text("Use Bloom"));
  postProcessingHeader->addElement(new GuiElement::SameLine);

  useBloomButton = new GuiElement::ToggleButton(false, "on", "off");
  postProcessingHeader->addElement(useBloomButton);
  postProcessingHeader->addElement(new GuiElement::Spacing);


  //TODO ADD BLOOM STRENGTH SLIDER

  //FXAA
  postProcessingHeader->addElement(new GuiElement::Text("Use FXAA"));
  postProcessingHeader->addElement(new GuiElement::SameLine);

  useFXAAButton = new GuiElement::ToggleButton(false, "on", "off");
  postProcessingHeader->addElement(useFXAAButton);
  postProcessingHeader->addElement(new GuiElement::Spacing);


  gui->addElement(postProcessingHeader);
  //===============================================================================================

  renderer->addGui(gui);
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
  
  renderer = new Renderer(context);

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
	cube1.setModelMatrix(glm::translate(cube1.getModelMatrix(), glm::vec3(-0.7, 0.35, 0.0)));
  cube1.setModelMatrix(glm::scale(cube1.getModelMatrix(), glm::vec3(0.5, 0.5, 0.5)));

	Node cube2("cube2");
	cube2.addGeometry(&cube);
	cube2.addTexture(&bricks);
  cube2.addNormalMap(&bricks_normal);
  cube2.addHeightMap(&bricks_height,0.07, 0.1, false);
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
  ConeLight slight(glm::vec4(2.0, 2.5, 3.5, 1.0), glm::vec4(0.7, 0.7, 0.7, 1.0), true, glm::vec3(-1.0, -1.0, -1.0), 90.0f, 1.0f, 10.0f);
  
  dsLightColor = new glm::fvec3(1.0f, 1.0f, 1.0f);

  Node *newLight1 = new Node(std::string("Node_1"));
  newLight1->addGeometry(&lightSphere);
  newLight1->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-1,1,1)));
  newLight1->setModelMatrix(glm::scale(newLight1->getModelMatrix(), glm::vec3(3.0, 3.0, 3.0)));
  lights.addChildrenNode(newLight1);
  
  Node *newLight2 = new Node(std::string("Node_2"));
  newLight2->addGeometry(&lightSphere);
  newLight2->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(1,1,1)));
  newLight2->setModelMatrix(glm::scale(newLight2->getModelMatrix(), glm::vec3(3.0, 3.0, 3.0)));
  lights.addChildrenNode(newLight2);

  Node *newLight3 = new Node(std::string("Node_3"));
  newLight3->addGeometry(&lightSphere);
  newLight3->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, -1)));
  newLight3->setModelMatrix(glm::scale(newLight3->getModelMatrix(), glm::vec3(3.0, 3.0, 3.0)));
  lights.addChildrenNode(newLight3);

  Node *newLight4 = new Node(std::string("Node_4"));
  newLight4->addGeometry(&lightSphere);
  newLight4->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-1, 1, -1)));
  newLight4->setModelMatrix(glm::scale(newLight4->getModelMatrix(), glm::vec3(3.0, 3.0, 3.0)));
  lights.addChildrenNode(newLight4);

  ssaoQuality = new float(30.0f);
  ssaoRadius = new float(0.1f);

  reflectionStrength = new float(0.2f);

  initGUI();

 	
	double startTime = glfwGetTime();
	//Renderloop
  int outputFPS = 0;
	while (!glfwWindowShouldClose(testWindow.getWindow()))
	{

    renderer->useShadowMapping(useShadowMappingButton->isActive(), &slight);
    renderer->useDeferredShading(useDeferredShadingButton->isActive(), &lights, dsLightColor);
    renderer->useSSAO(useSSAOButton->isActive(), ssaoQuality, ssaoRadius);
    renderer->useReflections(useReflectionsButton->isActive(), reflectionStrength);
    renderer->useBloom(useBloomButton->isActive());
    renderer->useAntiAliasing(useFXAAButton->isActive());



    // You have to compute the delta time
    float dTime = glfwGetTime() - startTime;

    cam.setSensitivity(dTime/50);

    if (deferredShadingRotationButton->isActive())
      lights.setModelMatrix(glm::rotate(lights.getModelMatrix(), 10.0f * dTime, glm::vec3(0.0, 1.0, 0.0)));

    if (!(outputFPS % 20))
      std::cout << "FPS: " << static_cast<int> (1 / dTime) << std::endl;

    outputFPS++;

    startTime = glfwGetTime();
    renderer->renderScene(testScene, testWindow);
	}

	glfwDestroyWindow(testWindow.getWindow());
	glfwTerminate();

	return 0;
}