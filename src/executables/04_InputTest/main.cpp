#include "GL/glew.h"
#include "GeKo_Graphics/Camera/Trackball.h"
#include "GeKo_Gameplay/Input/InputHandler.h"
#include "GeKo_Gameplay/Input/InputMap.h"

/* To use the input system, you need an InputHandler, a camera and the key callback
InputHandler: has to set all InputMaps and activate one of them
Camera: just because the InputHandler needs to know which camera is active
Key Callback: has to be set
*/

InputHandler iH;
// alibiCam, because here we have just output on the console
Trackball alibiCam(800, 800);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	// The active InputMap is fetched
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	// You go over the active InputMap, if it's the key that is pressed, the mapped action is executed else the key is ignored
	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			activeMap.at(key)();
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}
}

int main(void)
{
	glfwInit();

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "InputTest", NULL, NULL);
	glfwMakeContextCurrent(window);

	iH.setAllInputMaps(alibiCam);
	// Setting an InputMap active so that action can be performed
	iH.changeActiveInputMap("Trackball");

	//Callback
	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

}