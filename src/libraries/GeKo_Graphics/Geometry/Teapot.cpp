#include "Teapot.h"
#include "TeapotData.h"

Teapot::Teapot()
{
	m_points = _points;
	m_indices = _indices;
	setIndexTrue();
	setUVTrue();
	setNormalsTrue();

	for (int i = 0; i<_points; i++)
	{
		m_vertices.push_back(glm::vec4(_v[i * 3], _v[i * 3 + 1], _v[i * 3 + 2], 1.0));
		m_normals.push_back(glm::vec3(_n[i * 3], _n[i * 3 + 1], _n[i * 3 + 2]));
		m_uvs.push_back(glm::vec2(_t[i * 2], 1 - _t[i * 2 + 1]));
	}

	for (int i = 0; i<_indices; i++)
	{
		m_index.push_back(_index[i]);
	}
}

Teapot::~Teapot()
{
	m_vertices.clear();
	m_normals.clear();
	m_uvs.clear();
	m_index.clear();
}


///A Method to load Buffer
/*The vertices Data from m_vertices will be loaded into Buffers, so the Shader can use this information for the position of the object*/
//void Teapot::loadBufferData()
//{
//	m_vertexBuffer = new Buffer<glm::vec4>(m_vertices, STATIC_DRAW);
//	m_normalBuffer = new Buffer<glm::vec3>(m_normals, STATIC_DRAW);
//	m_uvBuffer = new Buffer<glm::vec2>(m_uvs, STATIC_DRAW);
//	m_indexBuffer = new BufferIndex<GLuint>(m_index, STATIC_DRAW_INDEX);
//
//	glGenVertexArrays(1, &m_vaoBuffer);
//	glBindVertexArray(m_vaoBuffer);
//
//	m_vertexBuffer->bind();
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
//
//	m_normalBuffer->bind();
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	m_uvBuffer->bind();
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//	m_indexBuffer->bind();
//
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//
//	glBindVertexArray(0);
//}

///A method to render the Object 
/*In the while-Loop of the main-programm (Renderer or else) this method will be called to draw the array*/
//void Teapot::renderGeometry()
//{
//	glBindVertexArray(m_vaoBuffer);
//
//	glDrawElements(GL_TRIANGLES, m_index.size(), GL_UNSIGNED_INT, 0);
//}