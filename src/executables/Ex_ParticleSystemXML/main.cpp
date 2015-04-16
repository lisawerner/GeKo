//#include <TinyXML/src/TinyXML/tinyxml2.h>
#include <vector>
#include <GL/glew.h>
#include "GeKo_Graphics/ParticleSystem/ParticleSystem.h"
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>

InputHandler iH;
Pilotview cam("Pilotview");

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	// The active InputMap is fetched
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	// You go over the active InputMap, if it's the key that is pressed, a method is called and the mapped action is executed else the key is ignored
	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			iH.getActiveInputMap()->checkMultipleMappedKeys(key, *window);
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}
}

int main()
{
	glfwInit();

	//our window
	GLFWwindow* window;
	window = glfwCreateWindow(800, 600, "ParticleSystemXML", NULL, NULL);
	glfwMakeContextCurrent(window);
	
	//CAM
	cam.setKeySpeed(4.0);
	iH.setAllInputMaps(cam);
	glfwSetKeyCallback(window, key_callback);
	cam.setFOV(50);
	cam.setNearFar(1, 100);

	glewInit();

	//Textures
	Texture* fireTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/fire/Fire2_M.png");
	//Texture* fireTex1 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/fire/Flame1_L.png");
	//Texture* fireTex2 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/fire/Flame3_XL.png");
	//Texture* fireTex3 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/fire/Flame2_L.png");

	/*Emitter* test = new Emitter(0, glm::vec3(0.0, 0.0, 0.0), 0.0, 0.1, 1000000, 4.0, true);
	test->setVelocity(3);
	test->usePhysicDirectionGravity(glm::vec4(0.0, 1.0, 0.0, 0.8), 0.8f);
	Effect* testEff = new Effect();
	ParticleSystem* testPS = new ParticleSystem(glm::vec3(0, -1, 0), testEff);
	testEff->addEmitter(test);
	Node testNode("testNode");
	testNode.setCamera(&cam);
	testNode.addParticleSystem(testPS);*/

	//EmitterFire
	Emitter* fire = new Emitter(0, glm::vec3(0.0, 0.0, 0.0), 0.0, 0.25, 2, 8.0, true);
	fire->setVelocity(3);
	fire->usePhysicDirectionGravity(glm::vec4(0.0, 1.0, 0.0, 0.8), 0.8f);
	fire->addTexture(fireTex, 1.0);
	//fire->addTexture(fireTex2, 0.6);
	//fire->addTexture(fireTex3, 0.3);
	std::vector<float> sizeF{ 0.3f, 1.5f };
	std::vector<float> timeF{ 0.0f, 0.5f };
	fire->defineLook(true, sizeF, timeF, 1.0, 4.0, 4.0, true, 0.5);
	fire->switchToGeometryShader();

	//Effect* effect = new Effect(RESOURCES_PATH "/XML/ComicCloudEffect.xml");
	//ParticleSystem* ps = new ParticleSystem(glm::vec3(0.0, 0.0, 0.0), RESOURCES_PATH "/XML/ComicCloudEffect.xml");
	//effect->saveEffect(RESOURCES_PATH "/XML/EffectTest.xml");

	Effect* effect = new Effect();
	effect->addEmitter(fire);
	ParticleSystem* psFire = new ParticleSystem(glm::vec3(0, -1, 0), effect);
	Node fireNode("fireNode");
	fireNode.setCamera(&cam);
	fireNode.addParticleSystem(psFire);

	// Shader
	VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader3D/ColorShader3D.vert")));
	FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader3D/ColorShader3D.frag")));
	ShaderProgram shader(vs, fs);

	// Renderer
	OpenGL3Context context;
	Renderer renderer(context);

	//need scene here mainly because of input
	Level testLevel("testLevel");
	Scene testScene("testScene");
	testLevel.addScene(&testScene);
	testLevel.changeScene("testScene");

	//Add Camera to Scene
	testScene.getScenegraph()->addCamera(&cam);
	testScene.getScenegraph()->setActiveCamera("Pilotview");

	//Set Input-Maps and activate one
	iH.setAllInputMaps(*(testScene.getScenegraph()->getActiveCamera()));
	iH.changeActiveInputMap("Pilotview");

	testScene.getScenegraph()->getRootNode()->addChildrenNode(&fireNode);
	//testScene.getScenegraph()->getRootNode()->addChildrenNode(&testNode);
	

	double startTime = glfwGetTime();
	
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	while (!glfwWindowShouldClose(window))
	{
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0){ // If last prinf() was more than 1 sec ago
			// printf and reset timer
			//printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		cam.setSensitivity(glfwGetTime() - startTime);
		startTime = glfwGetTime();

		glEnable(GL_DEPTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.bind();
		shader.sendMat4("viewMatrix", cam.getViewMatrix());
		shader.sendMat4("projectionMatrix", cam.getProjectionMatrix());
		//testScene.render(shader);
		shader.unbind();
		
		psFire->update();
		psFire->render(cam);
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}