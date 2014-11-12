#include "Teapot.h"
#include "TeapotData.h"

Teapot::Teapot()
{
	m_points = _points;
	m_indices = _indices;

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
}


///A Method to load Buffer
/*The vertices Data from m_vertices will be loaded into Buffers, so the Shader can use this information for the position of the object*/
void Teapot::loadBufferData()
{
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(glm::vec4), &m_vertices[0], GL_STATIC_DRAW);

	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

///A method to render the Object 
/*In the while-Loop of the main-programm (Renderer or else) this method will be called to draw the array*/
void Teapot::renderGeometry()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_points);
}