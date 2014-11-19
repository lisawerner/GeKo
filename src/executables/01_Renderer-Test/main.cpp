#include "GeKo_Graphics/Defs.h"
#include "GeKo_Graphics/Renderer.h"
#include "GeKo_Graphics/Window.h"
#include "GeKo_Graphics/Shader.h"
#include "GeKo_Graphics/Buffer.h"

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
    //our example
    std::vector<glm::vec3> vertices;
    vertices.push_back(glm::vec3(0.5, -0.5, 0.0));
    vertices.push_back(glm::vec3(-0.5, -0.5, 0.0));
    vertices.push_back(glm::vec3(0.5, 0.5, 0.0));
    vertices.push_back(glm::vec3(-0.5, 0.5, 0.0));

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
    Buffer<glm::vec3> buffer(vertices,STATIC_DRAW);

    //Gameloop
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.bind();
        //FIXME - need proper shader uniform
        shader.sendVec3("color", glm::vec3(0.5,0.2,0.8));
        renderer.draw(buffer);
        shader.unbind();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    window.close();
    return 0;
}
