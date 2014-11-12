#include "GeKo_Graphics/Defs.h"
#include "GeKo_Graphics/Renderer.h"
#include "GeKo_Graphics/Window.h"
#include "GeKo_Graphics/Shader.h"
#include "GeKo_Graphics/Buffer.h"
#include "GeKo_Graphics/FBO.h"
#include "GeKo_Graphics/Rect.h"
#include "GeKo_Graphics/Teapot.h"
#include "GeKo_Graphics/Cube.h"

/*
1. we set a window
2. set the shader with a fragmentshader & vertexshader
3. set a renderer
4. set 2 buffer for vertices & normals of the quad
5. gameloop
5.1 create a colortexture
5.2 show the colotexture with the screenfillingquad
*/
int main()
{
    glfwInit();

    //our window
    Window window(550, 50, 800, 600, "Renderer Example");

    glewInit();

	//our shader
	VertexShader vsFbo(loadShaderSource(SHADERS_PATH + std::string("/FBO/fbo.vert")));
	FragmentShader fsFbo(loadShaderSource(SHADERS_PATH + std::string("/FBO/fbo.frag")));
	ShaderProgram shaderFbo(vsFbo, fsFbo);

	VertexShader vsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/screenFillingQuad.vert")));
	FragmentShader fsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/screenFillingQuad.frag")));
	ShaderProgram shaderSfq(vsSfq, fsSfq);
    
	//our renderer
    OpenGL3Context context;
    Renderer renderer(context);

	//our object
	Rect rect;
	Cube cube;
	Teapot teapot; //buggy
  //  Buffer<glm::vec4> bufferV(rect.getVertices(),STATIC_DRAW);
	cube.loadBufferData();
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
		cube.renderGeometry();
		fbo.unbind();
		shaderFbo.unbind();

		//take the color texture and show it on the screen
		shaderSfq.sendSampler2D("colorTexture", fbo.getColorTexture(0));
		shaderSfq.bind();
		cube.renderGeometry();
		shaderSfq.unbind();
		
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }
    window.close();
    return 0;
}