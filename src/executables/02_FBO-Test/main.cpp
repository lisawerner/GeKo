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
	VertexShader vsColor(loadShaderSource(SHADERS_PATH + std::string("/ColorShader/colorShader.vert")));
	FragmentShader fsColor(loadShaderSource(SHADERS_PATH + std::string("/ColorShader/colorShader.frag")));
	ShaderProgram shaderColor(vsColor, fsColor);

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
	Teapot teapot; //buggy
	rect.loadBufferData();
	cube.loadBufferData();

	//our fbo
	FBO fbo(800, 600, 3, true, false);

    //Gameloop
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//GBuffer
		fbo.bind(); //TODO: Stencil- und Depth Textures gehen noch nicht, weitere Funktionen der FBO Klasse ausprobieren
		shaderGBuffer.bind();
		cube.renderGeometry();
		shaderGBuffer.unbind();
		fbo.unbind();

		//ScreenFillingQuad
		shaderSfq.bind();
		shaderSfq.sendSampler2D("texture", fbo.getDepthTexture());
		rect.renderGeometry(); //Normalen sind kaputt??
		shaderSfq.unbind();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }
    window.close();
    return 0;
}