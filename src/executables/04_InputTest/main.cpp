#include "GL/glew.h"
#include "GeKo_Graphics/Camera.h"
#include "GeKo_Graphics/InputHandler.h"
#include "GeKo_Graphics/InputMap.h"

InputHandler iH;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			activeMap.at(key)();
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}
}

int main(void)
{
	// alibiCam, because here we have just output on the console
	Camera alibiCam;
	iH.setAllInputMaps(alibiCam);
	iH.changeActiveInputMap("Trackball");

	glfwInit();

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "InputTest", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window))
	{

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

}