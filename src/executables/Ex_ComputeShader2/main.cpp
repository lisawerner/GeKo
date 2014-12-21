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
	
	ComputeShader cs(loadShaderSource(SHADERS_PATH + std::string("/ComputeShader/simpleComputeShader2.comp")));
	ShaderProgram computeShader(cs);

	/*Outsourcing*/
	#define NUM_PARTICLES 1024*1024
	#define WORK_GROUP_SIZE 128
	struct pos
	{
		float x, y, z, w; // positions
	};
	struct vel
	{
		float vx, vy, vz, vw; // velocities
	};
	/*struct col
	{
		float r, g, b, a;
	}color;*/

	GLuint posSSbo;
	GLuint velSSbo;
	//GLuint colSSbo;

	glGenBuffers(1, &posSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, posSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(struct pos), NULL, GL_STATIC_DRAW);
	
	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
	struct pos *points = (struct pos *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct pos), bufMask);
	for (int i = 0; i < NUM_PARTICLES; i++){
		points[i].x = rand() % 10;
		points[i].y = rand() % 10;
		points[i].z = rand() % 10;
		points[i].w = rand() % 10;
	}
	points[5].x = 2;
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glGenBuffers(1, &velSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, velSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(struct vel), NULL, GL_STATIC_DRAW);
	struct vel *vels = (struct vel *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct vel), bufMask);
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		vels[i].vx = rand() % 10;
		vels[i].vy = rand() % 10;
		vels[i].vz = rand() % 10;
		vels[i].vw = rand() % 10;
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	//BUUUUUUUGGGG
	/*glGenBuffers(1, &colSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, colSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(struct col), NULL, GL_STATIC_DRAW);
	struct col *cols = (struct col *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct col), bufMask);
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		cols[i].r = rand() % 1;
		cols[i].g = rand() % 1;
		cols[i].b = rand() % 1;
		cols[i].a = rand() % 1;
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);*/

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, posSSbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, velSSbo);
	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, colSSbo);

	computeShader.bind();
	
	std::cout << "HIER MUSS IRGENDWAS > 0 STEHEN:   " << points[5].x << std::endl;
	glDispatchCompute(NUM_PARTICLES / WORK_GROUP_SIZE, 1, 1);

	computeShader.unbind();

	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	
	/*END*/

	std::cout << "HIER MUSS IRGENDWAS > 0 STEHEN:   " << points[5].x << std::endl;

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