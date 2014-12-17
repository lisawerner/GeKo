#include "GeKo_Graphics/Renderer/Renderer.h"
#include "GeKo_Graphics/Shader/Shader.h"

#include "GeKo_Graphics/Camera/Pilotview.h"
#include "GeKo_Gameplay/Input/InputHandler.h"

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

	GLFWwindow* window;
	window = glfwCreateWindow(800, 600, "ComputeShader", NULL, NULL);
	glfwMakeContextCurrent(window);

	// You have to set a camera name
	cam.setName("PilotviewCam");
	cam.setPosition(glm::vec4(1.0, 0.0, 5.0, 1.0));
	cam.setNearFar(0.01f, 100.0f);

	// Set all InputMaps and set one InputMap active
	iH.setAllInputMaps(cam);
	iH.changeActiveInputMap("Pilotview");

	// Callback
	glfwSetKeyCallback(window, key_callback);

	glewInit();

	//Shader
	ComputeShader cs(loadShaderSource(SHADERS_PATH + std::string("/ComputeShader/simpleComputeShader.comp")));
	ShaderProgram computeShader(cs);

	// Renderer
	OpenGL3Context context;
	Renderer renderer(context);

	/*Now it starts*/

	// getting the start time
	float startTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// You have to compute the delta time
		cam.setSensitivity(glfwGetTime() - startTime);
		startTime = cam.getSensitivity();

		/*New stuff*/
		computeShader.bind();
		//glDispatchCompute(10, 1, 1);
		computeShader.unbind();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}