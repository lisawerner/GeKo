#include "GeKo_Graphics/Defs.h"
#include "GeKo_Graphics/Renderer.h"
#include "GeKo_Graphics/Window.h"
#include "GeKo_Graphics/Shader.h"
//#include "GeKo_Graphics/Buffer.hpp"
#include "GeKo_Graphics/FBO.h"
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
	
	VertexShader vsFbo(loadShaderSource(SHADERS_PATH + std::string("/FBO/fbo.vert")));
	FragmentShader fsFbo(loadShaderSource(SHADERS_PATH + std::string("/FBO/fbo.frag")));
	
	VertexShader vsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/screenFillingQuad.vert")));
	FragmentShader fsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/screenFillingQuad.frag")));
	
	ShaderProgram shader(vs, fs);
    ShaderProgram shaderFbo(vsFbo, fsFbo);
	ShaderProgram shaderSfq(vsSfq, fsSfq);
    
	//our renderer
    OpenGL3Context context;
    Renderer renderer(context);

	//our object
	Rect rect;
	Teapot teapot; //buggy
    Buffer<glm::vec3> bufferV(rect.getVertices(),STATIC_DRAW);
	Buffer<glm::vec2> bufferUV(rect.getUV(), STATIC_DRAW);


	//our fbo
	FBO fbo(800, 600, 2, true, false);

    //Gameloop
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//creating color and depth textures
		shaderFbo.bind();
		shaderFbo.sendVec3("color", glm::vec3(0.5, 0.2, 0.8));

		fbo.bind();
		renderer.draw(bufferV);
		fbo.unbind();
		shaderFbo.unbind();

		//take the color texture and show it on the screen
		shaderSfq.sendSampler2D("colorTexture", fbo.getColorTexture(1));
		shaderSfq.bind();
        renderer.draw(bufferV);
		shaderSfq.unbind();
		
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    window.close();
    return 0;
}