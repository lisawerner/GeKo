//#include <TinyXML/src/TinyXML/tinyxml2.h>
#include "tinyxml2.h"
#include <vector>
#include <GL/glew.h>
#include "GeKo_Graphics/ParticleSystem/ParticleSystem.h"
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>

using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

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

int main()
{
	glfwInit();

	//our window
	GLFWwindow* window;
	window = glfwCreateWindow(800, 600, "TinyXML 2", NULL, NULL);
	glfwMakeContextCurrent(window);
	
	//CAM
	cam.setPosition(glm::vec4(0.0, 0.0, 2.5, 1.0));
	cam.setKeySpeed(2.0);
	iH.setAllInputMaps(cam);
	glfwSetKeyCallback(window, key_callback);

	//SCENE 
	Level testLevel("testLevel");
	Scene testScene("testScene");
	testLevel.addScene(&testScene);
	testLevel.changeScene("testScene");
	testScene.getScenegraph()->addCamera(&cam);
	testScene.getScenegraph()->getCamera("PilotviewCam");
	testScene.getScenegraph()->setActiveCamera("PilotviewCam");
	iH.setAllInputMaps(*(testScene.getScenegraph()->getActiveCamera()));
	iH.changeActiveInputMap("Pilotview");

	glewInit();

	//PS Test
	Texture* smokeTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/smoke1_L.png");
	Texture* snowTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/particle.png");
	
	//EMITTER SMOKE
	Emitter* smoke = new Emitter(0, glm::vec3(0, -0.5, 0.0), 0.0, 0.25, 4, 8.0, true);
	smoke->setVelocity(3);
	smoke->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.1), 0.4f);
	smoke->addTexture(smokeTex, 0.0);
	std::vector<float> size{ 0.2f, 1.0f, 2.5f };
	std::vector<float> time{ 0.0f, 0.2f, 1.0f };
	smoke->useTexture(true, size, time, 2.0, 3.0, false, 0.3);
	smoke->switchToGeometryShader();

	//EMITTER SNOW, needs better texture
	Emitter* snow = new Emitter(0, glm::vec3(0.0, 3.0, 0.0), 0.0, 0.166, 100, 30.0, true);
	snow->setVelocity(0);
	snow->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, 1.0), 0.5f);
	snow->setAreaEmitting(false, true, 10.0, 10000);
	snow->addTexture(snowTex, 0.0);
	snow->useTexture(true, 1.0, 2.0);

	/*Effect* effect = new Effect();
	effect->addEmitter(smoke);
	effect->addEmitter(snow);*/
	Effect* effect = new Effect(RESOURCES_PATH "/XML/EffectTest.xml");
	ParticleSystem* ps = new ParticleSystem(glm::vec3(0, 0, 0), effect);

	//effect->saveEffect(RESOURCES_PATH "/XML/EffectTest.xml");

	double startCamTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ps->update();
		ps->render(cam);
		
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