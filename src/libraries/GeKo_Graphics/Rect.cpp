#include "Rect.h"

Rect::Rect()
{
	
	m_points = 4;

	m_vertices.push_back(glm::vec3( 0.5, -0.5, 0.0));
	m_vertices.push_back(glm::vec3(-0.5, -0.5, 0.0));
	m_vertices.push_back(glm::vec3( 0.5,  0.5, 0.0));
	m_vertices.push_back(glm::vec3(-0.5,  0.5, 0.0));


}

Rect::~Rect()
{
	m_vertices.clear();
}


void Rect::loadBufferData()
{
	m_vertexBuffer = new Buffer<glm::vec3>(m_vertices, STATIC_DRAW);

}

void Rect::renderGeometry()
{
	
	m_vertexBuffer->bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertexBuffer->size);
	glDisableVertexAttribArray(0);
	m_vertexBuffer->unbind();

}