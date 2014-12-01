#pragma once
#include "GeKo_Graphics/include.h"
#include "GeKo_Graphics/Defs.h"
#include "GeKo_Graphics/Renderer/Renderer.h"
#include "GeKo_Graphics/Window.h"
#include "GeKo_Graphics/Light/PointLight.h"
#include "GeKo_Graphics/Light/ConeLight.h"
#include "GeKo_Graphics/Light/DirectionLight.h"
#include "GeKo_Graphics/Shader/Shader.h"
#include "GeKo_Graphics/Buffer.h"
#include "GeKo_Graphics/Shader/FBO.h"
#include "GeKo_Graphics/Object/Rect.h"
#include "GeKo_Graphics/Object/Teapot.h"
#include "GeKo_Graphics/Object/Cube.h"

/*
Description
*/
int main()
{
    glfwInit();

    //our window
    Window window(550, 50, 800, 600, "Light Example");

    glewInit();

	//our shader
	VertexShader vsColor(loadShaderSource(SHADERS_PATH + std::string("/PhongShader/phong.vert"))); //TODO umbennen & bugfix
	FragmentShader fsColor(loadShaderSource(SHADERS_PATH + std::string("/PhongShader/phong.frag")));
	ShaderProgram shaderPhong(vsColor, fsColor);

	/*VertexShader vsColorPhong(loadShaderSource(SHADERS_PATH + std::string("/Phong/Phong.vert"))); //TODO umbennen & bugfix
	FragmentShader fsColorPhong(loadShaderSource(SHADERS_PATH + std::string("/Phong/Phong.frag")));
	ShaderProgram shaderPhong2(vsColorPhong, fsColorPhong);*/
    
	//our renderer
    OpenGL3Context context;
    Renderer renderer(context);

	//our object
	Rect* rect = new Rect(glm::vec4(0.5, -0.5, 0, 1.0), glm::vec4(-0.5, -0.5, 0, 1.0), glm::vec4(0.5, 0.5, 0, 1.0), glm::vec4(-0.5, 0.5, 0, 1.0),
		glm::vec2(0.75, 0.25), glm::vec2(0.25, 0.25), glm::vec2(0.75, 0.75), glm::vec2(0.25, 0.75));
	rect->loadBufferData();

	//our light
	PointLight plight(glm::vec4(0.0, 0.0, 0.1, 1.0), glm::vec4(1.0, 1.0, 1.0, 1.0), true, 0); //TODO radius & mehrere Lichter uebergeben

    //Gameloop
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderPhong.bind();
		
		//Uniform TODO?
		//TODO color vec3
		shaderPhong.sendLightData("l_pos", "l_col", "l_dir", "l_exp", "l_ang", "l_rad", plight);
		glm::mat4 m(1.0);
		shaderPhong.sendMat4("modelMatrix", m);
		shaderPhong.sendMat4("viewMatrix", m);
		shaderPhong.sendMat4("projectionMatrix", m);
		shaderPhong.sendFloat("shininess", 2.0f);

		shaderPhong.sendVec4("ambient", glm::vec4(0.2,0.2,0.2, 1.0));
		shaderPhong.sendVec4("diffuse", glm::vec4(1.0, 0.0, 0.0, 1.0));
		shaderPhong.sendVec4("specular", glm::vec4(1.0, 1.0, 1.0,1.0));

		rect->renderGeometry();
		shaderPhong.unbind();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }
    window.close();
    return 0;
}