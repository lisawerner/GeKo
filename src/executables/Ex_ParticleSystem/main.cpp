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
	Texture* particleBlackTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/particleBlack.png");

	Texture* particleWhiteTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/particle.png");

	Texture* rainTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/rain.png"); //TODO

	Texture* snowTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/snowflake.png");

	Texture* smokeWhiteTex1 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/smokeWhite1.png");
	Texture* smokeWhiteTex2 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/smokeWhite2.png");
	Texture* smokeBlackTex1 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/smokeBlack1.png");
	Texture* smokeBlackTex2 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/smokeBlack2.png");

	Texture* smokeTex1 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/smoke1_L.png");
	Texture* smokeTex2 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/Smoke2_XL.png");
	Texture* smokeTex3 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/Smoke3_L.png");
	Texture* smokeTex4 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/Smoke4_L.png");

	Texture* comicCloudTex1 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/comicCloud.png");
	Texture* comicSymbolTex1 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/comicSymbol1.png");
	Texture* comicSymbolTex2 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/comicSymbol2.png");
	Texture* comicSymbolTex3 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/comicSymbol3.png");
	Texture* comicSymbolTex4 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/comicSymbol4.png");

	Texture* fireTex1 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/Flame1_L.png");
	Texture* fireTex2 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/Flame2_L.png");
	Texture* fireTex3 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/Flames3_L.png");

	Texture* flyTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/Fly.png"); //TODO

	Texture* fireWorkYellowTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/starYellow.png");
	Texture* fireWorkOrangeTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/starPink.png");
	Texture* fireWorkRedTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/starRed.png");
	Texture* fireWorkBlueTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/starBlue.png");
	Texture* fireWorkGreenTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/starGreen.png");

	///////////////////////////////////////FINAL EMITTER///////////////////////////////////////

	//FINAL EMITTER SNOW
	Emitter* snow = new Emitter(0, glm::vec3(0.0, 3.0, 0.0), 0.0, 0.166, 100, 30.0, true);
	snow->setVelocity(0);
	snow->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, 1.0), 0.5f);
	snow->setAreaEmitting(false,true, 10.0, 10000);
	snow->addTexture(snowTex, 0.0);
	snow->useTexture(true, 1.0, 2.0);

	//FINAL EMITTER STRONG SNOW
	Emitter* snowStrong = new Emitter(0, glm::vec3(-3.5, 4.0, 0.0), 0.0, 0.166, 100, 20.0, true);
	snowStrong->setVelocity(2);
	snowStrong->usePhysicDirectionGravity(glm::vec4(0.6, -1.5, 0.0, 1.0), 2.6f);
	snowStrong->setAreaEmitting(false, true, 8.0, 10000);
	snowStrong->addTexture(snowTex, 0.0);
	snowStrong->useTexture(true, 0.8, 1.0, 3.0);

	//FINAL EMITTER WHITE SMOKE
	Emitter* smokeWhite = new Emitter(0, glm::vec3(0, -1.0, 0.0), 0.0, 0.4, 1, 8.0, true);
	smokeWhite->setVelocity(2);
	smokeWhite->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.8), 0.3f);
	smokeWhite->addTexture(smokeWhiteTex1, 1.0);
	smokeWhite->addTexture(smokeWhiteTex2, 0.25);
	std::vector<float> smokeWhiteSize{ 0.05f, 0.5f, 0.75f, 1.2f };
	std::vector<float> smokeWhiteTime{ 0.0f, 0.4f, 0.75f, 1.0f };
	smokeWhite->useTexture(true, smokeWhiteSize, smokeWhiteTime, 1.0, 4.0, false, 0.3);
	smokeWhite->switchToGeometryShader();

	//FINAL EMITTER BLACK SMOKE
	Emitter* smokeBlack = new Emitter(0, glm::vec3(0, -1.0, 0.0), 0.0, 0.4, 1, 8.0, true);
	smokeBlack->setVelocity(2);
	smokeBlack->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.8), 0.3f);
	smokeBlack->addTexture(smokeBlackTex1, 1.0);
	smokeBlack->addTexture(smokeBlackTex2, 0.08);
	std::vector<float> smokeBlackSize{ 0.1f, 0.4f, 0.8f, 1.2f };
	std::vector<float> smokeBlackTime{ 0.0f, 0.2f, 0.75f, 1.0f };
	smokeBlack->useTexture(true, smokeBlackSize, smokeBlackTime, 1.0, 4.0, false, 0.3);
	smokeBlack->switchToGeometryShader();

	//FINAL EMITTER RAIN
	Emitter* rain = new Emitter(0, glm::vec3(0.0, 3.0, 0.0), 0.0, 0.166, 200, 5.0, true);
	rain->setVelocity(0);
	rain->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, 1.0), 5.0f);
	rain->setAreaEmitting(false, true, 8.0, 10000);
	rain->addTexture(rainTex, 0.0);
	rain->useTexture(true, 0.8, 1.0, 0.0);

	//FINAL EMITTER FRUITFLIES
	Emitter* fruitFlies = new Emitter(0, glm::vec3(cam.getPosition()), 0.0, 0.166, 50, 10.0, true);
	fruitFlies->setVelocity(0);
	fruitFlies->usePhysicSwarmCircleMotion(true, true, true);
	fruitFlies->setAreaEmitting(true, true, 8.0, 10000);
	fruitFlies->addTexture(particleBlackTex, 0.0);
	fruitFlies->useTexture(true, 0.6, 1.0, 2.0);

	////////////////////////////////WAITING FOR TEXTURES EMITTER////////////////////////////////

	//EMITTER STRONG RAIN, need velo
	Emitter* rainStrong = new Emitter(0, glm::vec3(0.0, 3.0, 0.0), 0.0, 0.166, 200, 5.0, true);
	rainStrong->setVelocity(0);
	rainStrong->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, 1.0), 5.0f);
	rainStrong->setAreaEmitting(false, true, 8.0, 10000);
	rainStrong->addTexture(rainTex, 0.0);
	rainStrong->useTexture(true, 0.8, 1.0, 0.0);

	//!EMITTER COMIC CLOUD TODO
	/*Emitter* cloud = new Emitter(0, glm::vec3(0, -0.5, 0.0), 0.0, 0.7, 1, 10.0, true);
	cloud->setVelocity(3);
	cloud->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.12), 0.3f);
	cloud->addTexture(comicCloudTex1, 0.0);
	std::vector<float> cloudSize{ 0.4f, 2.0f };
	std::vector<float> cloudTime{ 0.0f, 1.0f };
	cloud->useTexture(true, cloudSize, cloudTime, 1.0, 1.0, false, 0.3);
	cloud->switchToGeometryShader();

	Emitter* cloud1 = new Emitter(0, glm::vec3(0.2, 0.7, 0.0), 0.0, 5.0, 1, 5.0, true);
	cloud1->setVelocity(0);
	cloud1->setAreaEmitting(true, false, 1.0, 10);
	std::vector<float> cloud1Size{ 0.5f, 0.5f };
	std::vector<float> cloud1Time{ 0.0f, 1.0f };
	cloud1->addTexture(comicSymbolTex1, 1.0);
	cloud1->useTexture(true, cloud1Size, cloud1Time, 1.0, 2.0);
	cloud1->switchToGeometryShader();

	Emitter* cloud2 = new Emitter(0, glm::vec3(0.2, 0.7, 0.0), 0.0, 5.0, 1, 5.0, true);
	cloud2->setVelocity(0);
	cloud2->setAreaEmitting(true, false, 1.0, 10);
	cloud2->addTexture(comicSymbolTex2, 1.0);
	cloud2->useTexture(true, cloud1Size, cloud1Time, 1.0, 2.0);
	cloud2->switchToGeometryShader();

	Emitter* cloud3 = new Emitter(0, glm::vec3(-0.2, 0.7, 0.0), 0.0, 5.0, 1, 5.0, true);
	cloud3->setVelocity(0);
	cloud3->setAreaEmitting(true, false, 1.0, 10);
	cloud3->addTexture(comicSymbolTex3, 1.0);
	cloud3->useTexture(true, cloud1Size, cloud1Time, 1.0, 2.0);
	cloud3->switchToGeometryShader();

	Emitter* cloud4 = new Emitter(0, glm::vec3(-0.2, 0.7, 0.0), 0.0, 5.0, 1, 5.0, true);
	cloud4->setVelocity(0);
	cloud4->setAreaEmitting(true, false, 1.0, 10);
	cloud4->addTexture(comicSymbolTex4, 1.0);
	cloud4->useTexture(true, cloud1Size, cloud1Time, 1.0, 2.0);
	cloud4->switchToGeometryShader();*/

	//!EMITTER FIRE
	Emitter* fireMiddle = new Emitter(0, glm::vec3(0.0, 0.0, 0.0), 0.0, 1.0, 3.0, 4.0, true);
	fireMiddle->setVelocity(3);
	fireMiddle->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.5), 0.2);
	fireMiddle->addTexture(fireTex1, 1.0);
	//fireMiddle->addTexture(fireTex2, 0.5);
	fireMiddle->addTexture(fireTex3, 0.0);
	fireMiddle->useTexture(true, 0.5, 1.0, 2.0);
	fireMiddle->switchToGeometryShader();
	Emitter* fireSmoke = new Emitter(0, glm::vec3(0, -1.0, 0.0), 0.0, 0.4, 1, 8.0, true);
	fireSmoke->setVelocity(2);
	fireSmoke->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.8), 0.3f);
	fireSmoke->addTexture(smokeBlackTex1, 1.0);
	fireSmoke->addTexture(smokeBlackTex2, 0.08);
	std::vector<float> fireSmokeSize{ 0.1f, 0.4f, 0.8f, 1.2f };
	std::vector<float> fireSmokeTime{ 0.0f, 0.2f, 0.75f, 1.0f };
	fireSmoke->useTexture(true, fireSmokeSize, fireSmokeTime, 1.0, 4.0, false, 0.3);
	fireSmoke->switchToGeometryShader();

	//!EMITTER SWARM
	Emitter* swarm = new Emitter(0, glm::vec3(0.0, 2.0, 0.0), 0.0, 0.166, 10, 30.0, true);

	//!EMITTER FIREWORK
	Emitter* firework = new Emitter(0, glm::vec3(0.6, 0.6, 0.0), 0.0, 0.5, 5, 1.0, true);
	firework->setVelocity(4);
	firework->usePhysicDirectionGravity(glm::vec4(0.0,-1.0,0.0,0.1), 1.0f);
	//firework->addTexture(*fireWorkYellowTex, 0.0);
	//firework->useTexture(true, 0.8, 0.1, 0.2);
	Emitter* firework2 = new Emitter(0, glm::vec3(-0.6, -0.6, 0.0), 0.0, 0.5, 5, 1.0, true);
	firework2->setVelocity(4);
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

		///////////////////////////////////////FINAL EMITTER///////////////////////////////////////
		snow->generateParticle(glm::vec3(cam.getPosition()));
		snow->update(glm::vec3(cam.getPosition()));
		//snow->render(cam);

		snowStrong->generateParticle(glm::vec3(cam.getPosition()));
		snowStrong->update(glm::vec3(cam.getPosition()));
		//snowStrong->render(cam);

		smokeWhite->generateParticle();
		smokeWhite->update();
		//smokeWhite->render(cam);

		smokeBlack->generateParticle();
		smokeBlack->update();
		smokeBlack->render(cam);

		rain->generateParticle(glm::vec3(cam.getPosition()));
		rain->update(glm::vec3(cam.getPosition()));
		//rain->render(cam);

		fruitFlies->generateParticle(glm::vec3(cam.getPosition()));
		fruitFlies->update(glm::vec3(cam.getPosition()));
		//fruitFlies->render(cam);

		////////////////////////////////WAITING FOR TEXTURES EMITTER////////////////////////////////

		rainStrong->generateParticle(glm::vec3(cam.getPosition()));
		rainStrong->update(glm::vec3(cam.getPosition()));
		//rainStrong->render(cam);

		//shitty comic cloud
//		cloud->generateParticle();
//		cloud->update();
//		cloud->render(cam);
//		cloud1->generateParticle();
//		cloud1->update();
//		cloud1->render(cam);
//		cloud2->generateParticle();
//		cloud2->update();
//		cloud2->render(cam);
//		cloud3->generateParticle();
//		cloud3->update();
//		cloud3->render(cam);
//		cloud4->generateParticle();
//		cloud4->update();
//		cloud4->render(cam);

		//TODO EMITTER

		fireMiddle->generateParticle();
		fireMiddle->update();
		//fireMiddle->render(cam);
		fireSmoke->generateParticle();
		fireSmoke->update();
		//fireSmoke->render(cam);

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