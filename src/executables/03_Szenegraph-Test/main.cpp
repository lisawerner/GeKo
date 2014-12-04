#include <GeKo_Graphics/include.h>

InputHandler iH;
Trackball cam("Trackball");

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::map<int, std::function<void()>> activeMap = iH.getActiveInputMap()->getMap();

	for (std::map<int, std::function<void()>>::iterator it = activeMap.begin(); it != activeMap.end(); it++){
		if (it->first == key)
			activeMap.at(key)();
		if (it == activeMap.end())
			std::cout << "Key is not mapped to an action" << std::endl;
	}
}

int main()
{
	glfwInit();

	//our window
	//GLFWwindow* window;
	//window = glfwCreateWindow(800, 600, "Camera Test", NULL, NULL);
	//glfwMakeContextCurrent(window);

	Window testWindow(50, 50, 800, 600, "testWindow");
	glfwMakeContextCurrent(testWindow.getWindow());


	//Set Camera to another position
	cam.setPosition(glm::vec4(0.0,0.0,10.0,1.0));
	cam.setName("TrackballCam");
	
	//Set all InputMaps and set one InputMap active
	iH.setAllInputMaps(cam);
	iH.changeActiveInputMap("Trackball");

	//Callback
	glfwSetKeyCallback(testWindow.getWindow(), key_callback);

    glewInit();

	//our shader
    VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.vert")));
    FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.frag")));
	ShaderProgram shader(vs, fs);

	//our renderer
    OpenGL3Context context;
    Renderer renderer(context);

	//our object
	 Cube cube;
	 Teapot tea;
	 Rect rect;
	 rect.loadBufferData();
	// Skybox skybox;

	 //our textures
	 Texture texCV((char*)RESOURCES_PATH "/cv_logo.bmp");
	 Texture tex((char*)RESOURCES_PATH "/brick.bmp");
	// Texture skyboxTex((char*)RESOURCES_PATH "/himmel.jpg");

	 //Scene creation 
	 Level testLevel("testLevel");
	 Scene testScene("testScene");
	 testLevel.addScene(testScene);
	 testLevel.changeScene("testScene");

	//Add Camera to scenegraph
	 testScene.getScenegraph()->addCamera(cam);
	 testScene.getScenegraph()->getCamera("TrackballCam");
	 testScene.getScenegraph()->setActiveCamera("TrackballCam");

	 //Create Nodes with geometry and texture
	 Node testNode("testNode");
	 testNode.addGeometry(&tea);
	 testNode.addTexture(&texCV);
	 testNode.setModelMatrix(glm::translate(testNode.getModelMatrix(), glm::vec3(0.0, 0.0, 0.0)));

	 Node testNodeChild("child1");
     testNodeChild.addGeometry(&cube);
	 testNodeChild.addTexture(&tex);
	 testNodeChild.setModelMatrix(glm::translate(testNodeChild.getModelMatrix(), glm::vec3(3.0, 0.0, 0.0)));
	
	/* Node skyboxNode("skybox");
	 skyboxNode.addGeometry(&skybox);
	 skyboxNode.addTexture(&skyboxTex);*/


	 //Creating a scenegraph
	 /*testScene.getScenegraph()->getRootNode()->addChildrenNode(&skyboxNode);
	 skyboxNode.addChildrenNode(&testNode);
	 testNode.addChildrenNode(&testNodeChild);
*/
	 testScene.getScenegraph()->getRootNode()->addChildrenNode(&testNode);
	 testNode.addChildrenNode(&testNodeChild);

    //Renderloop
    while (!glfwWindowShouldClose(testWindow.getWindow()))
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		shader.bind();
		shader.sendMat4("viewMatrix", cam.getViewMatrix());
		shader.sendMat4("projectionMatrix", cam.getProjectionMatrix());

		testNode.setModelMatrix(glm::rotate(testNode.getModelMatrix(), 0.02f, glm::vec3(0.0, 1.0, 0.0)));
		testScene.render(shader);

		
		
		//	testNode.render();
			////TODO: The Texture should be send to the shader automatically when the node should be rendered and if it has a Texture 
			//shader.sendSampler2D("testTexture", testNode.getTexture()->getTexture());
			//testNode.setModelMatrix(glm::rotate(testNode.getModelMatrix(), 0.02f, glm::vec3(0.0, 1.0, 0.0)));
			////TODO: The Node should send its Modelmatrix automatically, just one Method for Rendering and modelMatrix sending/updatin
			//shader.sendMat4("modelMatrix", testNode.updateModelMatrix());
			//testNode.render();
			//
			////TODO: The Texture should be send to the shader automatically when the node should be rendered and if it has a Texture 
			//shader.sendSampler2D("testTexture", testNodeChild.getTexture()->getTexture());
			////TODO: The Node should send its Modelmatrix automatically, just one Method for Rendering and modelMatrix sending/updatin
			//shader.sendMat4("modelMatrix", testNodeChild.updateModelMatrix());
			//testNodeChild.render();

			shader.unbind();
        glfwSwapBuffers(testWindow.getWindow());
        glfwPollEvents();
    }

	glfwDestroyWindow(testWindow.getWindow());
	glfwTerminate();

    return 0;
}