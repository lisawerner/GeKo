#include "GeKo_Graphics/Defs.h"
#include "GeKo_Graphics/Renderer/Renderer.h"
#include "GeKo_Graphics/Window.h"
#include "GeKo_Graphics/Shader/Shader.h"
#include "GeKo_Graphics/Buffer.h"
#include "GeKo_Graphics/Shader/FBO.h"
#include "GeKo_Graphics/Object/Rect.h"
#include "GeKo_Graphics/Object/Teapot.h"
#include "GeKo_Graphics/Object/Cube.h"
#include <GeKo_Graphics/Camera/Camera.h>
#include <GeKo_Graphics/Camera/Trackball.h>
#include <GeKo_Gameplay/Input/InputHandler.h>
#include <GeKo_Gameplay/Input/InputMap.h>
#include <GeKo_Graphics/Material/Texture.h>
#include <GeKo_Graphics/Scenegraph/Scene.h>
#include <GeKo_Graphics/Scenegraph/Node.h>

/*
Descripton
*/

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
	window = glfwCreateWindow(800, 600, "FBO Test", NULL, NULL);
	glfwMakeContextCurrent(window);

	//Set Camera to another position
	cam.setPosition(glm::vec4(0.0, 0.0, 10.0, 1.0));
	cam.setName("TrackballCam");

	//Set all InputMaps and set one InputMap active
	iH.setAllInputMaps(cam);
	iH.changeActiveInputMap("Trackball");

	//Callback
	glfwSetKeyCallback(window, key_callback);

	glewInit();

	//our shader
	VertexShader vsTexture(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.vert")));
	FragmentShader fsTexture(loadShaderSource(SHADERS_PATH + std::string("/TextureShader3D/TextureShader3D.frag")));
	ShaderProgram shaderTexture(vsTexture, fsTexture);

	VertexShader vsRedShader(loadShaderSource(SHADERS_PATH + std::string("/RedShader/redShader.vert")));
	FragmentShader fsRedShader(loadShaderSource(SHADERS_PATH + std::string("/RedShader/redShader.frag")));
	ShaderProgram shaderRedShader(vsRedShader, fsRedShader);

	VertexShader vsGBuffer(loadShaderSource(SHADERS_PATH + std::string("/GBuffer/GBuffer.vert")));
	FragmentShader fsGBuffer(loadShaderSource(SHADERS_PATH + std::string("/GBuffer/GBuffer.frag")));
	ShaderProgram shaderGBuffer(vsGBuffer, fsGBuffer);

	VertexShader vsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/screenFillingQuad.vert")));
	FragmentShader fsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/screenFillingQuad.frag")));
	ShaderProgram shaderSfq(vsSfq, fsSfq);
    
	//our renderer
    OpenGL3Context context;
    Renderer renderer(context);

	//our object
	Rect rect;
	Cube cube;
	Teapot tea;

	//our textures
//	Texture texCV((char*)RESOURCES_PATH "/cv_logo.bmp");
//	Texture texBrick((char*)RESOURCES_PATH "/brick.bmp");

	//our fbos
	FBO fbo1(800, 600, 3, true, false);
	FBO fbo2(800, 600, 3, true, false);

	//our scene
	Scene scene;

	Node teaNode("TeaNode");
	teaNode.addGeometry(&tea);
//	teaNode.addTexture(&texCV);
	teaNode.setModelMatrix(glm::translate(teaNode.getModelMatrix(), glm::vec3(0.0, 0.0, 0.0)));

	Node brickNode("BrickNode");
	brickNode.addGeometry(&cube);
//	brickNode.addTexture(&texBrick);
	brickNode.setModelMatrix(glm::translate(brickNode.getModelMatrix(), glm::vec3(3.0, 0.0, 0.0)));

	scene.getScenegraph()->getRootNode()->addChildrenNode(teaNode);
	teaNode.addChildrenNode(brickNode);
	brickNode.setParentNode(&teaNode);

    //Gameloop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH);

		//GBuffer
/*		fbo.bind(); //TODO: Stencil- und Depth Textures gehen noch nicht, weitere Funktionen der FBO Klasse ausprobieren
		shaderGBuffer.bind();
		cube.renderGeometry();
		shaderGBuffer.unbind();
		fbo.unbind();*/
		
/*		//ScreenFillingQuad
		shaderSfq.bind();
		shaderSfq.sendSampler2D("texture", fbo.getDepthTexture());
		rect.renderGeometry(); //Normalen sind kaputt??
		shaderSfq.unbind();*/

		//color Output wieso bekommt redShader die uniform Variablen???
//		fbo1.bind();
		shaderRedShader.bind();
		teaNode.setModelMatrix(glm::rotate(teaNode.getModelMatrix(), 0.02f, glm::vec3(0.0, 1.0, 0.0)));
		shaderTexture.sendMat4("modelMatrix", teaNode.getModelMatrix());
		shaderTexture.sendMat4("viewMatrix", cam.getViewMatrix());
		shaderTexture.sendMat4("projectionMatrix", cam.getProjectionMatrix());

//		shaderTexture.sendSampler2D("texture", teaNode.getTexture()->getTexture());
		scene.getScenegraph()->getRootNode()->getChildrenNode("TeaNode")->render();

//		shaderTexture.sendSampler2D("texture", brickNode.getTexture()->getTexture());
		shaderTexture.sendMat4("modelMatrix", teaNode.getModelMatrix() * brickNode.getModelMatrix());
		brickNode.render();
		shaderRedShader.unbind();
//		fbo1.unbind();

		//color Output with texture
/*		fbo.bind();
		shaderTexture.bind();

		teaNode.setModelMatrix(glm::rotate(teaNode.getModelMatrix(), 0.02f, glm::vec3(0.0, 1.0, 0.0)));
		shaderTexture.sendMat4("modelMatrix", teaNode.getModelMatrix());
		shaderTexture.sendMat4("viewMatrix", cam.getViewMatrix());
		shaderTexture.sendMat4("projectionMatrix", cam.getProjectionMatrix());

		shaderTexture.sendSampler2D("texture", teaNode.getTexture()->getTexture());
		scene.getScenegraph()->getRootNode()->getChildrenNode("TeaNode")->render();

		shaderTexture.sendSampler2D("texture", brickNode.getTexture()->getTexture());
		shaderTexture.sendMat4("modelMatrix", teaNode.getModelMatrix() * brickNode.getModelMatrix());
		brickNode.render();

		shaderTexture.unbind();
		fbo.unbind();*/
	
		//ScreenFillingQuad
/*		shaderSfq.bind();
		shaderSfq.sendSampler2D("texture", fbo1.getColorTexture(0));
		teaNode.render();
		brickNode.render();
		shaderSfq.unbind();	*/

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}