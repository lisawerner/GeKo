#include "GeKo_Graphics/Renderer/Renderer.h"
#include "GeKo_Graphics/Shader/Shader.h"

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

	GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, 10 * sizeof(glm::fvec4), NULL, GL_DYNAMIC_COPY);

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
	glm::fvec4* points = (glm::fvec4*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 10 * sizeof(glm::fvec4), bufMask);
	for (int i = 0; i < 10; i++)
	{
		points[i] = glm::vec4(0.0, 0.0, 0.0, 0.0);
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	//auto buffer_index = glGetProgramResourceIndex(computeShader.handle, GL_SHADER_STORAGE_BLOCK, "Test");
	//glShaderStorageBlockBinding(computeShader.handle, buffer_index, 0);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
	computeShader.bind();
	//glBindImageTexture(0, ssbo, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	
	std::cout << "HIER MUSS 000 STEHEN:   " << points[1].x << points[1].y << points[1].z << std::endl;
	glDispatchCompute(10 / 2, 1, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	computeShader.unbind();

	std::cout << "HIER MUSS 111 STEHEN:   " << points[1].x << points[1].y << points[1].z << std::endl;
	
	/*END*/


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