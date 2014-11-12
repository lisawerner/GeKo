#include "GeKo_Graphics/Defs.h"
#include <GeKo_Graphics/Renderer.h>
#include "GeKo_Graphics/Window.h"
#include "GeKo_Graphics/Shader.h"
#include <GeKo_Graphics/Rect.h>
#include <GeKo_Graphics/Scene.h>
#include <GeKo_Graphics/Node.h>
#include <GeKo_Graphics/Scenegraph.h>
#include <GeKo_Graphics/Cube.h>
/*
first example:

1. We will set the Window
2. We will set the Shader
3. We will set the renderer, so we have the "context"
4. We will create a scenegraph with one node and one geometry
5. We let the geometry be drawn while using the scenegraph
*/
int main()
{
 

    glfwInit();

    //our window
    Window window(550, 50, 800, 600, "Renderer Example");

    glewInit();

	//our shader
    VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader/colorShader.vert")));
    FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader/colorShader.frag")));
    ShaderProgram shader(vs, fs);
	

	//our renderer
    OpenGL3Context context;
    Renderer renderer(context);

	//Scenegraph initialisation with all classes we need
//	Rect* rectangle = new Rect(); //Geht nicht ohne new Rect()!!TO FIX
	Cube* cube = new Cube();
	Scene testScene("TestScene");
	Node testNode("testNode");

	//Bufferloading will be done at this point, when the geometry is set
	testNode.addGeometry(cube);
	//adding the node to the scenegraph
	testScene.getScenegraph()->getRootNode()->addChildrenNode(testNode);

    //Gameloop
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.bind();
        //FIXME - need proper shader uniform
        shader.sendVec3("color", glm::vec3(0.5,0.2,0.8));

		//The array will be drawed by the rect-class with its buffer which will be bind
		testScene.getScenegraph()->getRootNode()->getChildrenNode("testNode")->render();

        shader.unbind();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    window.close();
    return 0;
}