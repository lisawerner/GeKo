#include "GeKo_Graphics/ParticleSystem/Emitter.h" //TODO Delete this line
#include "GeKo_Graphics/ParticleSystem/Effect.h"  //TODO Delete this line
#include "GeKo_Graphics/ParticleSystem/ParticleSystem.h"

#include <GL/glew.h>
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/MaterialInclude.h>
#include <GeKo_Graphics/ObjectInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>

InputHandler iH;
Pilotview cam("PilotviewCam");

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			iH.getActiveInputMap()->checkMultipleMappedKeys(key, *window);
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}
}

//include data?
enum FLOW { UNUSED = -1, CONSTANT = 0, ONCE = 1 } output;

int main()
{
	glfwInit();

	//WINDOW
	GLFWwindow* window;
	window = glfwCreateWindow(800, 600, "ParticleSystem", NULL, NULL);
	glfwMakeContextCurrent(window);

	//CAM
	cam.setPosition(glm::vec4(0.0, 0.0, 2.5, 1.0));
	iH.setAllInputMaps(cam);
	glfwSetKeyCallback(window, key_callback);

	glewInit();

	//?
	//OpenGL3Context context;
	//Renderer renderer(context);

	//TEXTURES
	Texture* fireTex;
	Texture* flyTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/Fly.png");
	Texture* smokeTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/smoke.jpg");
	Texture* rainTex;
	Texture* snowTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/particle.bmp");
	Texture* brick = new Texture((char*)RESOURCES_PATH "/brick.bmp");

	//EMITTER SNOW
	Emitter* snow = new Emitter(0, glm::vec3(0.0, 2.0, 0.0), false, 0.166, 10, 30.0, true);
	snow->setVelocity(&Emitter::useVelocityZero);	//We set our Function, which we want to use later in Emitter::pushParticle and define the velocity for the particle
	snow->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, 1.0), 0.3f);
	snow->setAreaEmitting(false,true, 3.0, 10000);
	snow->addTexture(*snowTex, 0.0);
	snow->setUseTexture(true);
	snow->active();

	//EMITTER FLIES
	Emitter* flies = new Emitter(0, glm::vec3(0.0, 0.0, 0.0), false, 0.166, 3, 10.0, true);
	flies->setVelocity(&Emitter::useVelocityZero);	
	flies->usePhysicSwarmCircleMotion(true, true, false, 0.0f);
	flies->setAreaEmitting(true, false, 2.0, 10000);
	flies->addTexture(*flyTex, 0.0);
	flies->setUseTexture(true);
	flies->active();

	//EMITTER SMOKE
	Emitter* smoke = new Emitter(0, glm::vec3(0, -0.5, 0.0), false, 0.25, 5, 4.0, true);
	smoke->setVelocity(&Emitter::useVelocitySemiCircle);
	smoke->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.1), 0.4f);
	smoke->addTexture(*smokeTex, 0.0);
	smoke->setUseTexture(true);
	smoke->switchToGeometryShader();
	smoke->setRotationSpeed(0.5f);
	smoke->active();

	//EMITTER COMIC CLOUD

	//EMITTER RAIN

	//EMITTER SWARM

	//EMITTER FIRE

	//EMITTER FIREWORK

	//SHADER
	VertexShader vsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.vert")));
	FragmentShader fsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.frag")));
	ShaderProgram shaderSkybox(vsSkybox, fsSkybox);

	//SKYBOX
	Cube cube;
	const char *textureNames[6] = { 
		/*(char*)RESOURCES_PATH "/PereaBeach1/posx.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/negx.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/posy.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/negy.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/posz.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/negz.jpg"*/
		(char*)RESOURCES_PATH "/ParticleSystem/testTex.png",
		(char*)RESOURCES_PATH "/ParticleSystem/testTex.png",
		(char*)RESOURCES_PATH "/ParticleSystem/testTex.png",
		(char*)RESOURCES_PATH "/ParticleSystem/testTex.png",
		(char*)RESOURCES_PATH "/ParticleSystem/testTex.png",
		(char*)RESOURCES_PATH "/ParticleSystem/testTex.png" };
	Skybox skybox(textureNames);
	Node skyboxNode("skybox");
	skyboxNode.addGeometry(&cube);

	//SCENE 
	Level testLevel("testLevel");
	Scene testScene("testScene");
	testLevel.addScene(testScene);
	testLevel.changeScene("testScene");
	testScene.getScenegraph()->addCamera(&cam);
	testScene.getScenegraph()->getCamera("PilotviewCam");
	testScene.getScenegraph()->setActiveCamera("PilotviewCam");
	iH.setAllInputMaps(*(testScene.getScenegraph()->getActiveCamera()));
	iH.changeActiveInputMap("Pilotview");

	double startCamTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		//SKYBOX
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderSkybox.bind();
		glDisable(GL_DEPTH_TEST);
		shaderSkybox.sendMat4("viewMatrix", cam.getViewMatrix());
		shaderSkybox.sendMat4("projectionMatrix", cam.getProjectionMatrix());
		shaderSkybox.sendSkyboxTexture("testTexture", skybox.getSkyboxTexture());
		skyboxNode.render();
		shaderSkybox.unbind();

		//EMITTER
//		glEnable(GL_DEPTH_TEST);

		snow->generateParticle();
		snow->update();
		//snow->render(cam);

		flies->generateParticle();
		flies->update();
		flies->render(cam);

		smoke->generateParticle();
		smoke->update();
		smoke->render(cam);

		//CAM
		cam.setSensitivity((float)(glfwGetTime() - startCamTime));
		startCamTime = glfwGetTime();

		//WINDOW
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}