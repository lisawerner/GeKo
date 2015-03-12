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
	cam.setKeySpeed(2.0);
	iH.setAllInputMaps(cam);
	glfwSetKeyCallback(window, key_callback);

	glewInit();

	//?
	//OpenGL3Context context;
	//Renderer renderer(context);

	//TEXTURES

	Texture* fireTex;

	Texture* darkTex = new Texture((char*)RESOURCES_PATH "");

	Texture* flyTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/Fly.png");

	Texture* smokeTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/smoke.png");

	Texture* rainTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/rain.png");

	Texture* snowTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/particle.png");

	//Texture* fireWorkYellowTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/StarYellow.png");
	//Texture* fireWorkOrangeTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/StarOrange.png");
	//Texture* fireWorkRedTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/StarRed.png");
	//Texture* fireWorkBlueTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/StarBlue.png");
	//Texture* fireWorkGreenTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/StarGreen.png");

	//EMITTER SNOW, needs better texture
	Emitter* snow = new Emitter(0, glm::vec3(0.0, 3.0, 0.0), 0.0, 0.166, 100, 30.0, true);
	snow->setVelocity(&Emitter::useVelocityZero);
	snow->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, 1.0), 0.5f);
	snow->setAreaEmitting(false,true, 10.0, 10000);
	snow->addTexture(*snowTex, 0.0);
	snow->useTexture(true, 1.0, 2.0);

	//EMITTER STRONG SNOW, better with multiple emitter
	Emitter* snowStrong = new Emitter(0, glm::vec3(-3.5, 4.0, 0.0), 0.0, 0.166, 50, 20.0, true);
	snowStrong->setVelocity(&Emitter::useVelocityRightQuarterCircle);
	snowStrong->usePhysicDirectionGravity(glm::vec4(0.4, -1.5, 0.0, 1.0), 2.6f);
	snowStrong->setAreaEmitting(false, true, 5.0, 10000);
	snowStrong->addTexture(*snowTex, 0.0);
	snowStrong->useTexture(true, 0.2, 1.0, 3.0);

	//EMITTER RAIN, needs texture
	Emitter* rain = new Emitter(0, glm::vec3(0.0, 3.0, 0.0), 0.0, 0.166, 20, 5.0, true);
	rain->setVelocity(&Emitter::useVelocityZero);
	rain->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, 1.0), 5.0f);
	rain->setAreaEmitting(false, true, 3.0, 10000);
	rain->addTexture(*rainTex, 0.0);
	rain->useTexture(true, 0.6, 1.0, 0.0);

	//EMITTER COMIC CLOUD TODO
	Emitter* cloud = new Emitter(0, glm::vec3(0, -0.5, 0.0), 0.0, 0.25, 5, 4.0, true);
	cloud->setVelocity(&Emitter::useVelocitySemiCircle);
	cloud->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.1), 0.4f);
	cloud->addTexture(*smokeTex, 0.0);
	cloud->useTexture(true, 0.0);
	cloud->switchToGeometryShader();

	//EMITTER SMOKE, dont like it
	Emitter* smoke = new Emitter(0, glm::vec3(0, -0.5, 0.0), 0.0, 0.25, 4, 8.0, true);
	smoke->setVelocity(&Emitter::useVelocitySemiCircle);
	smoke->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.1), 0.4f);
	smoke->addTexture(*smokeTex, 0.0);
	std::vector<float> size{ 0.2f, 1.0f, 2.5f};
	std::vector<float> time{ 0.0f, 0.2f, 1.0f};
	smoke->useTexture(true, size, time, 2.0, 3.0, false, 0.3);
	smoke->switchToGeometryShader();

	//EMITTER FIRE
	Emitter* fire = new Emitter(0, glm::vec3(0.0, 2.0, 0.0), 0.0, 0.166, 10, 30.0, true);

	//EMITTER FRUITFLIES, should move with player
	Emitter* fruitFlies = new Emitter(0, glm::vec3(0.0, 0.0, 0.0), 0.0, 0.166*5, 5, 10.0, true);
	fruitFlies->setVelocity(&Emitter::useVelocityZero);
	fruitFlies->usePhysicSwarmCircleMotion(true, true, false, 0.0f);
	fruitFlies->setAreaEmitting(true, false, 2.0, 10000);
	fruitFlies->addTexture(*darkTex, 0.0);
	fruitFlies->useTexture(true, 0.1, 1.0, 2.0);

	//EMITTER FLIES, should move with player
	Emitter* flies = new Emitter(0, glm::vec3(0.0, 0.0, 0.0), 0.0, 0.166, 1, 10.0, true);
	flies->setVelocity(&Emitter::useVelocityZero);
	flies->usePhysicSwarmCircleMotion(true, true, false, 0.0f);
	flies->setAreaEmitting(true, false, 2.0, 10000);
	flies->addTexture(*flyTex, 0.0);
	flies->useTexture(true, 0.1, 1.0, 2.0);
	flies->switchToGeometryShader();

	//EMITTER SWARM
	Emitter* swarm = new Emitter(0, glm::vec3(0.0, 2.0, 0.0), 0.0, 0.166, 10, 30.0, true);

	//EMITTER FIREWORK
	Emitter* firework = new Emitter(0, glm::vec3(0.6, 0.6, 0.0), 0.0, 0.5, 5, 1.0, true);
	firework->setVelocity(&Emitter::useVelocityCircle);
	firework->usePhysicDirectionGravity(glm::vec4(0.0,-1.0,0.0,0.1), 1.0f);
	//firework->addTexture(*fireWorkYellowTex, 0.0);
	//firework->useTexture(true, 0.8, 0.1, 0.2);
	Emitter* firework2 = new Emitter(0, glm::vec3(-0.6, -0.6, 0.0), 0.0, 0.5, 5, 1.0, true);
	firework2->setVelocity(&Emitter::useVelocityCircle);
	firework2->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, 0.1), 1.0f);
	//firework2->addTexture(*fireWorkOrangeTex, 0.0);
	//firework2->useTexture(true, 0.8, 0.1, 0.2);

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

		snow->generateParticle(glm::vec3(cam.getPosition()));
		snow->update(glm::vec3(cam.getPosition()));
		//snow->render(cam);

		snowStrong->generateParticle(glm::vec3(cam.getPosition()));
		snowStrong->update(glm::vec3(cam.getPosition()));
		//snowStrong->render(cam);

		rain->generateParticle(glm::vec3(cam.getPosition()));
		rain->update(glm::vec3(cam.getPosition()));
		//rain->render(cam);

		//cloud->generateParticle();
		//cloud->update();
		//cloud->render(cam);

		smoke->generateParticle();
		smoke->update();
		//smoke->render(cam);

		//fire->generateParticle();
		//fire->update();
		//fire->render(cam);

		fruitFlies->generateParticle();
		fruitFlies->update();
		//fruitFlies->render(cam);

		flies->generateParticle();
		flies->update();
		flies->render(cam);

		//swarm->generateParticle();
		//swarm->update();
		//swarm->render(cam);

		firework->generateParticle();
		firework->update();
		//firework->render(cam);

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