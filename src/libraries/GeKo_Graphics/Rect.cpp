#include "Rect.h"

Rect::Rect()
{
	m_vertices.push_back(glm::vec3(0.5, -0.5, 0.0));
	m_vertices.push_back(glm::vec3(-0.5, -0.5, 0.0));
	m_vertices.push_back(glm::vec3(0.5, 0.5, 0.0));
	m_vertices.push_back(glm::vec3(-0.5, 0.5, 0.0));
}

Rect::~Rect()
{

}


///A Method to load Buffer
/*The vertices Data from m_vertices will be loaded into Buffers, so the Shader can use this information for the position of the object*/
void Rect::loadBufferData()
{
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

///A method to render the Object 
/*In the while-Loop of the main-programm (Renderer or else) this method will be called to draw the array*/
void Rect::renderGeometry()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}