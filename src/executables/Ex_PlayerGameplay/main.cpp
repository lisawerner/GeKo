#include <GL/glew.h>
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/MaterialInclude.h>
#include <GeKo_Graphics/ObjectInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>
#include <GeKo_Graphics/AIInclude.h>
#include <GeKo_Gameplay/Player/Geko.h>
#include <list>
#include <queue>
#include <stack>


InputHandler iH;
Trackball cam("Trackball");

//Our player object, starting at position 0, 0, 0
Geko geko("Geko", glm::vec3(0.0));

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			activeMap.at(key)();
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}
}

//Mouse Move Callback for rotating the view
double lastX, lastY;
void mouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
	geko.rotateView(xPos - lastX, yPos - lastY);
	lastX = xPos; 
	lastY = yPos;
}

int main()
{
	glfwInit();

	Window testWindow(50, 50, 800, 600, "testWindow");
	glfwMakeContextCurrent(testWindow.getWindow());
	
	//Set Camera to another position
	cam.setPosition(glm::vec4(0.0, 0.0, 5.0, 1.0));
	cam.setName("TrackballCam");
	cam.setKeySpeed(2.0);

	//Callback for Camera and Player
	glfwSetKeyCallback(testWindow.getWindow(), key_callback);
	glfwSetCursorPosCallback(testWindow.getWindow(), mouseMoveCallback);

	glewInit();

	//our shader
	VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.vert")));
	FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.frag")));
	ShaderProgram shader(vs, fs);

	//our renderer
	OpenGL3Context context;
	Renderer renderer(context);

	//our object
	Teapot tea;
	//our textures
	Texture texCV((char*)RESOURCES_PATH "/cv_logo.bmp");

	//Scene creation 
	Level testLevel("testLevel");
	Scene testScene("testScene");
	testLevel.addScene(testScene);
	testLevel.changeScene("testScene");

	//Add Camera to scenegraph
	testScene.getScenegraph()->addCamera(&cam);
	testScene.getScenegraph()->getCamera("TrackballCam");
	testScene.getScenegraph()->setActiveCamera("TrackballCam");

	//Set all InputMaps and set one InputMap active
	iH.setAllInputMaps(*(testScene.getScenegraph()->getActiveCamera()));
	iH.changeActiveInputMap("Trackball");

	//Create Nodes with geometry and texture
	Node testNode("testNode");
	testNode.addGeometry(&tea);
	testNode.addTexture(&texCV);
	//testNode.setModelMatrix(glm::translate(testNode.getModelMatrix(), glm::vec3(0.0, 0.0, 0.0)));
	testNode.setModelMatrix(glm::translate(testNode.getModelMatrix(), geko.getCurrentPosition()));
	//Creating a scenegraph
	testScene.getScenegraph()->getRootNode()->addChildrenNode(&testNode);

	//The player will be getting the Node, so the player is visualized by its geometry!
	geko.setNode(&testNode);
	
	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(testWindow.getWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//Recognizing if the player wants to move its character
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_UP))
		{
			geko.moveForward();
		}
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_DOWN))
		{
			geko.moveBackward();
		}
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_RIGHT))
		{
			geko.moveRight();
		}
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_LEFT))
		{
			geko.moveLeft();
		}

		//Update the position of the Player
		geko.update(deltaTime);
		
		//Render the Player
		glEnable(GL_DEPTH_TEST);

		shader.bind();
		shader.sendMat4("viewMatrix", cam.getViewMatrix());
		shader.sendMat4("projectionMatrix", cam.getProjectionMatrix());

		testScene.render(shader);
		shader.unbind();

		glfwSwapBuffers(testWindow.getWindow());
		glfwPollEvents();
	}

	glfwDestroyWindow(testWindow.getWindow());
	glfwTerminate();

	return 0;
}