//#include <TinyXML/src/TinyXML/tinyxml2.h>
#include <vector>
#include <GL/glew.h>
#include "GeKo_Graphics/ParticleSystem/ParticleSystem.h"
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>

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
	Texture* fireTex = new Texture((char*)RESOURCES_PATH "/ParticleSystem/fire/Fire1_XL.png");
	Texture* fireTex1 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/fire/Flame1_L.png");
	Texture* fireTex2 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/fire/Flame3_XL.png");
	Texture* fireTex3 = new Texture((char*)RESOURCES_PATH "/ParticleSystem/fire/Flame2_L.png");

	//Emitter Fire
	Emitter* fire = new Emitter(0, glm::vec3(0, -1.0, 0.0), 0.0, 0.25, 1, 8.0, true);
	fire->setVelocity(3);
	fire->usePhysicDirectionGravity(glm::vec4(0.0, -1.0, 0.0, -0.3), 0.4f);
	fire->addTexture(fireTex, 1.0);
	//fire->addTexture(fireTex2, 0.6);
	//fire->addTexture(fireTex3, 0.3);
	std::vector<float> sizeF{ 0.2f, 1.0f };
	std::vector<float> timeF{ 0.0f, 1.0f };
	fire->defineLook(true, sizeF, timeF, 1.0, 4.0, true, 0.5);
	fire->switchToGeometryShader();

	
	Effect* effect = new Effect();

	/*effect->addEmitter(smoke);
	effect->addEmitter(snow);*/

	effect->addEmitter(fire);

	//Effect* effect = new Effect(RESOURCES_PATH "/XML/ComicCloudEffect.xml");
	//ParticleSystem* ps = new ParticleSystem(glm::vec3(0, 0, 0), effect);
	ParticleSystem* ps = new ParticleSystem(glm::vec3(0.0, 0.0, 0.0), RESOURCES_PATH "/XML/ComicCloudEffect.xml");

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