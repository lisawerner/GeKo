#include "Geometry.h"


Geometry::Geometry()
{
	m_wasLoaded = false;
}

Geometry::~Geometry()
{
}


void Geometry::loadBufferData()
{
	m_vertexBuffer = new Buffer<glm::vec4>(m_vertices, STATIC_DRAW);
	m_normalBuffer = new Buffer<glm::vec3>(m_normals, STATIC_DRAW);
	m_uvBuffer = new Buffer<glm::vec2>(m_uvs, STATIC_DRAW);
	m_indexBuffer = new BufferIndex<GLuint>(m_index, STATIC_DRAW_INDEX);

	glGenVertexArrays(1, &m_vaoBuffer);
	glBindVertexArray(m_vaoBuffer);

	m_vertexBuffer->bind();
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	m_normalBuffer->bind();
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	m_uvBuffer->bind();
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	m_indexBuffer->bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}


void Geometry::renderGeometry()
{
	glBindVertexArray(m_vaoBuffer);

	if (m_hasIndex)
	{
		glDrawElements(GL_TRIANGLES, m_index.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_indices);
	}

}


std::vector<glm::vec4> Geometry::getVertices()
{
	return m_vertices;
}

std::vector<glm::vec3> Geometry::getNormals()
{
	return m_normals;
}

std::vector<glm::vec2> Geometry::getUV()
{
	return m_uvs;
}

std::vector<GLuint> Geometry::getIndexList()
{
	return m_index;
}

void Geometry::setLoaded()
{
	m_wasLoaded = true;
}


void Geometry::resetLoaded()
{
	m_wasLoaded = false;
}


bool Geometry::isLoaded()
{
	return m_wasLoaded;
}

void Geometry::setIndexTrue()
{
	m_hasIndex = true;
}

void Geometry::setIndexFalse()
{
	m_hasIndex = false;
}

bool Geometry::hasIndex()
{
	return m_hasIndex;
}