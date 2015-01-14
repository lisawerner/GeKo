#include <GL/glew.h>
#include <GeKo_Graphics/InputInclude.h>
#include <GeKo_Graphics/MaterialInclude.h>
#include <GeKo_Graphics/ObjectInclude.h>
#include <GeKo_Graphics/ShaderInclude.h>
#include <GeKo_Graphics/ScenegraphInclude.h>

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

	Window testWindow(50, 50, 800, 600, "testWindow");
	glfwMakeContextCurrent(testWindow.getWindow());


	//Set Camera to another position
	cam.setPosition(glm::vec4(0.0, 0.0, 10.0, 1.0));
	cam.setName("TrackballCam");

	//Callback
	glfwSetKeyCallback(testWindow.getWindow(), key_callback);

	glewInit();

	//our shader
	VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.vert")));
	FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.frag")));
	ShaderProgram shader(vs, fs);

	VertexShader vsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.vert")));
	FragmentShader fsSkybox(loadShaderSource(SHADERS_PATH + std::string("/SkyboxShader/SkyboxShader.frag")));
	ShaderProgram shaderSkybox(vsSkybox, fsSkybox);

	//our renderer
	OpenGL3Context context;
	Renderer renderer(context);

	//our object
	Cube cube;
	Teapot tea;

	//At this point you should load your own cubeMap-Jpg-Files until we have a online account for ressources
	/*const char *textureNames[6] = { (char*)RESOURCES_PATH "/PereaBeach1/posx.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/negx.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/posy.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/negy.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/posz.jpg",
		(char*)RESOURCES_PATH "/PereaBeach1/negz.jpg" };
	Skybox skybox(textureNames);*/

	//our textures
	Texture texCV((char*)RESOURCES_PATH "/cv_logo.bmp");
	Texture tex((char*)RESOURCES_PATH "/brick.bmp");

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
	//iH.setAllInputMaps(cam);
	iH.setAllInputMaps(*(testScene.getScenegraph()->getActiveCamera()));
	iH.changeActiveInputMap("Trackball");


	//Create Nodes with geometry and texture
	Node testNode("testNode");
	testNode.addGeometry(&tea);
	testNode.addTexture(&texCV);
	testNode.setModelMatrix(glm::translate(testNode.getModelMatrix(), glm::vec3(0.0, 0.0, 0.0)));

	Node testNodeChild("child1");
	testNodeChild.addGeometry(&cube);
	testNodeChild.addTexture(&tex);
	testNodeChild.setModelMatrix(glm::translate(testNodeChild.getModelMatrix(), glm::vec3(3.0, 0.0, 0.0)));

	/*Node skyboxNode("skybox");
	skyboxNode.addGeometry(&cube);*/

	//Creating a scenegraph
	testScene.getScenegraph()->getRootNode()->addChildrenNode(&testNode);
	testNode.addChildrenNode(&testNodeChild);

	//Renderloop
	while (!glfwWindowShouldClose(testWindow.getWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//Skybox rendering
		/*shaderSkybox.bind();
		glDisable(GL_DEPTH_TEST);
		shaderSkybox.sendMat4("viewMatrix", cam.getViewMatrix());
		shaderSkybox.sendMat4("projectionMatrix", cam.getProjectionMatrix());
		shaderSkybox.sendSkyboxTexture("testTexture", skybox.getSkyboxTexture());
		skyboxNode.render();
		shaderSkybox.unbind();*/

		glEnable(GL_DEPTH_TEST);
		//Scene Rendering
		shader.bind();
		shader.sendMat4("viewMatrix", cam.getViewMatrix());
		shader.sendMat4("projectionMatrix", cam.getProjectionMatrix());
		testNode.setModelMatrix(glm::rotate(testNode.getModelMatrix(), 0.02f, glm::vec3(0.0, 1.0, 0.0)));
		testScene.render(shader);
		shader.unbind();

		glfwSwapBuffers(testWindow.getWindow());
		glfwPollEvents();
	}

	glfwDestroyWindow(testWindow.getWindow());
	glfwTerminate();

	return 0;
}