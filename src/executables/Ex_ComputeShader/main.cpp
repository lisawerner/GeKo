#include "GeKo_Graphics/Renderer/Renderer.h"
#include "GeKo_Graphics/Shader/Shader.h"

GLuint renderHandle, computeHandle;

int main() {
	glfwInit();

	//our window
	GLFWwindow* window;
	window = glfwCreateWindow(1, 1, "ComputeShader", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewInit();
	
	ComputeShader cs(loadShaderSource(SHADERS_PATH + std::string("/ComputeShader/simpleComputeShader.comp")));
	ShaderProgram computeShader(cs);

	/*Outsourcing*/

	int test = 2;

	GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(test), &test, GL_STATIC_DRAW);

	//auto buffer_index = glGetProgramResourceIndex(computeShader.handle, GL_SHADER_STORAGE_BLOCK, "Test");
	//glShaderStorageBlockBinding(computeShader.handle, buffer_index, 0);

	computeShader.bind();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

	
	std::cout << "HIER MUSS 2 STEHEN:   " << test << std::endl;
	glDispatchCompute(1, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);


	//glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	computeShader.unbind();

	//glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	
	/*END*/

	std::cout << "HIER MUSS 99 STEHEN:   " << test << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//for (int i = 0; i < 1024; ++i) {
	//	computeShader.bind();
	//	computeShader.sendFloat("roll", 0.1f);
	//	glDispatchCompute(2, 1, 1); // 512^2 threads in blocks of 16^2
	//	computeShader.unbind();

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}