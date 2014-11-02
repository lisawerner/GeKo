#include "GeKo_Graphics/Defs.h"
#include "GeKo_Graphics/Renderer.h"
#include "GeKo_Graphics/Window.h"
#include "GeKo_Graphics/Shader.h"
#include "GeKo_Graphics/Buffer.hpp"

//Example

/*
measure the time for a certain number of loops
*/
/*
first example:

we set a window,
initialize the renderer and load an object,
set the shaderhandle & give him the path of the shaders
and renderering the object in the gameloop
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

    VertexShader vs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader/colorShader.vert")));
    FragmentShader fs(loadShaderSource(SHADERS_PATH + std::string("/ColorShader/colorShader.frag")));
    ShaderProgram p(vs, fs);
    //our renderer
    OpenGL3Context context;
    Renderer renderer(context);
    Buffer<glm::vec3> buffer(vertices,STATIC_DRAW);

    //Gameloop
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        p.bind();
        //FIXME - need proper shader uniform
        p.sendVec3("color", glm::vec3(0.5,0.2,0.8));
        renderer.draw(buffer);
        p.unbind();
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    window.close();
    return 0;
}