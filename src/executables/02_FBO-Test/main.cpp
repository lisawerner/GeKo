#include "GeKo_Graphics/Defs.h"
#include "GeKo_Graphics/Renderer.h"
#include "GeKo_Graphics/Window.h"
#include "GeKo_Graphics/Shader.h"
#include "GeKo_Graphics/Buffer.h"
//#include "GeKo_Graphics/FBO.h"
#include "GeKo_Graphics/Rect.h"
#include "GeKo_Graphics/Teapot.h"

/*
first example:

1. per hand we build a quad
2. we set a window
3. set the shader with a fragmentshader & vertexshader
3.1 fragmentShader get an uniform var 
4. set a renderer
5. set a buffer with the quad
6. gameloop
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
	VertexShader vsfbo(loadShaderSource(SHADERS_PATH + std::string("/FBO/fbo.vert")));
	FragmentShader fsfbo(loadShaderSource(SHADERS_PATH + std::string("/FBO/fbo.frag")));
	ShaderProgram shader(vs, fs);
    ShaderProgram shaderFbo(vsfbo, fsfbo);
    
	//our renderer
    OpenGL3Context context;
    Renderer renderer(context);

	//our object
	Rect rect;
	Teapot teapot; //buggy
    Buffer<glm::vec3> buffer(rect.getVertices(),STATIC_DRAW);

	//our fbo
	//FBO fbo(800, 600, 2, true, false);

    //Gameloop
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderFbo.bind();
        //FIXME - need proper shader uniform
        shaderFbo.sendVec3("color", glm::vec3(0.5,0.2,0.8));

		//fbo.bind();
		renderer.draw(buffer);
		//fbo.unbind();

        renderer.draw(buffer);
        shaderFbo.unbind();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    window.close();
    return 0;
}