#include <GeKo_Graphics/Object/Cube.h>

Cube::Cube()
{
	m_vaoBuffer = 0;
	m_points = 36;
	m_indices = 36;
	setIndexFalse();

	GLfloat vertices[] = {
		// Front face
		-1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0,
		// Right face
		1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0,
		1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0,
		// Back face
		-1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0,
		1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0,
		// Left face
		-1.0, -1.0, 1.0, -1.0, -1.0, -1.0, -1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0,
		// Bottom face   
		-1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0,
		1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0,
		// Top Face
		-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0,
		1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0
	};

	GLfloat normals[] = {
		// Front face
		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
		// Right face
		1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		// Back face
		0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
		0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
		// Left face
		-1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
		// Bottom face
		0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0,
		0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0,
		// Top face
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0
	};

	GLfloat texCoords[] = {
		0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0
	};

	for (int i = 0; i<m_points; i++)
	{
		m_vertices.push_back(glm::vec4(vertices[i * 3]*0.5, vertices[i * 3 + 1]*0.5, vertices[i * 3 + 2]*0.5, 1.0f));
		m_normals.push_back(glm::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]));
		m_uvs.push_back(glm::vec2(texCoords[i * 2], texCoords[i * 2 + 1]));
	}

	for (int i = 0; i < m_indices; i++)
	{
		m_index.push_back(i);
	}
}

Cube::~Cube()
{
	m_vertices.clear();
	m_normals.clear();
	m_uvs.clear();
	m_index.clear();
}

//void Cube::loadBufferData()
//{
//	m_vertexBuffer = new Buffer<glm::vec4>(m_vertices, STATIC_DRAW);
//	m_normalBuffer = new Buffer<glm::vec3>(m_normals, STATIC_DRAW);
//	//m_uvBuffer = new Buffer<glm::vec2>(m_uvs, STATIC_DRAW);	
//	//m_indexBuffer = new Buffer<GLuint>(m_index, STATIC_DRAW);
//
//	glGenVertexArrays(1, &m_vaoBuffer);
//	glBindVertexArray(m_vaoBuffer);
//	m_vertexBuffer->bind();
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
//
//	m_normalBuffer->bind();
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	/*m_uvBuffer->bind();
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);*/
//
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	//glEnableVertexAttribArray(2);
//
//	glBindVertexArray(0);
//
//}

//void Cube::renderGeometry()
//{
//
//	glBindVertexArray(m_vaoBuffer);
//	glDrawArrays(GL_TRIANGLES, 0, 3*6*2);
//}