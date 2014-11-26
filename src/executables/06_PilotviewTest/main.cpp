#include "GeKo_Graphics/Defs.h"
#include "GeKo_Graphics/Renderer/Renderer.h"
#include "GeKo_Graphics/Shader/Shader.h"
#include "GeKo_Graphics/Object/Teapot.h"
#include "GeKo_Graphics/Camera/Camera.h"
#include "GeKo_Graphics/Camera/Pilotview.h"
#include "GeKo_Gameplay/Input/InputHandler.h"
#include "GeKo_Gameplay/Input/InputMap.h"
#include "GeKo_Gameplay/Input/MapPilotview.h"



/* To use the Pilotview camera which is based on the input system you need an InputHandler, the Pilotview camera and the key callback
InputHandler: has to set all InputMaps and activate one of them
Uniform matrices: have to be send to the shader in the render loop
Key Callback: has to be set
*/

InputHandler iH;
Pilotview cam(800, 800);


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
	window = glfwCreateWindow(800, 600, "PilotviewTest", NULL, NULL);
	glfwMakeContextCurrent(window);

	// You can set the Pilotview camera to another position and give it a name
	cam.setPosition(glm::vec4(1.0, 0.0, 5.0, 1.0));
	cam.setName("PilotviewCam");
	
	// Set all InputMaps and set one InputMap active
	iH.setAllInputMaps(cam);
	iH.changeActiveInputMap("Pilotview");

	// Callback
	glfwSetKeyCallback(window, key_callback);

	glewInit();

	// Shader
    VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader3D/ColorShader3D.vert")));
    FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader3D/colorShader3D.frag")));
	ShaderProgram shader(vs, fs);
    
	// Renderer
    OpenGL3Context context;
    Renderer renderer(context);
	
	// Object
	Teapot teapot;
	teapot.loadBufferData();


    while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.bind();

		// You have to send the uniform matrices of the Pilotview camera to the shader
		shader.sendMat4("viewMatrix", cam.getViewMatrix());
		shader.sendMat4("projectionMatrix", cam.getProjectionMatrix());
	
		teapot.renderGeometry();
		shader.unbind();
       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}