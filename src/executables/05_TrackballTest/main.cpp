//Test of Camera and Cube

#include "GeKo_Graphics/Defs.h"
#include "GeKo_Graphics/Renderer.h"
#include "GeKo_Graphics/Shader.h"
#include "GeKo_Graphics/Teapot.h"
#include "GeKo_Graphics/Camera.h"
#include "GeKo_Graphics/Trackball.h"
#include "GeKo_Graphics/InputHandler.h"
#include "GeKo_Graphics/InputMap.h"




InputHandler iH;
Trackball cam(800, 800);


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();
	activeMap.at(key)();
}



int main()
{
	glfwInit();

	//our window
	GLFWwindow* window;
	window = glfwCreateWindow(800, 600, "Camera Test", NULL, NULL);
	glfwMakeContextCurrent(window);

	//Set Scene
	//Scene scene("TestScene");

	//Set Camera to another position
	cam.setPosition(glm::vec4(0.0,0.0,10.0,1.0));
	cam.setName("TrackballCam");
	


	//Set all InputMaps and set one InputMap active
	iH.setAllInputMaps(cam);
	iH.changeActiveInputMap("Trackball");

	//Callback
	glfwSetKeyCallback(window, key_callback);


    glewInit();

	//our shader
    VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader3D/ColorShader3D.vert")));
    FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader3D/colorShader3D.frag")));
	ShaderProgram shader(vs, fs);
    
	//our renderer
    OpenGL3Context context;
    Renderer renderer(context);
	
	//our object
	Teapot teapot;
	teapot.loadBufferData();

	

    //Renderloop
    while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.bind();

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