#include "Rect.h"

Rect::Rect()
{
	
		create(glm::vec3(0.9, -0.9, 0), glm::vec3(-0.9, -0.9, 0), glm::vec3(0.9, 0.9, 0), glm::vec3(-0.9, 0.9, 0),
		glm::vec2(0.9, 0.1), glm::vec2(0.1, 0.1), glm::vec2(0.9, 0.9), glm::vec2(0.1, 0.9));

		/*
	create(glm::vec3(1.0, -1.0, 0), glm::vec3(-1.0, -1.0, 0), glm::vec3(1.0, 1.0, 0), glm::vec3(-1.0, 1.0, 0),
		glm::vec2(1.0, 0), glm::vec2(0, 0), glm::vec2(1.0, 1.0), glm::vec2(0, 1.0));*/
}

Rect::Rect(glm::vec3 dright, glm::vec3 dleft, glm::vec3 uright, glm::vec3 uleft, glm::vec2 tca, glm::vec2 tcb, glm::vec2 tcc, glm::vec2 tcd)
{
	create(dright, dleft, uright, uleft, tca, tcb, tcc, tcd);

}

Rect::~Rect()
{
	m_vertices.clear();
}

void Rect::create(glm::vec3 dright, glm::vec3 dleft, glm::vec3 uright, glm::vec3 uleft, glm::vec2 tca, glm::vec2 tcb, glm::vec2 tcc, glm::vec2 tcd)
{
	m_vertices.push_back(glm::vec3(dright));
	m_vertices.push_back(glm::vec3(dleft));
	m_vertices.push_back(glm::vec3(uright));
	m_vertices.push_back(glm::vec3(uleft));

	m_points = 4;

	glm::vec3 n = glm::normalize(glm::cross(dright - dleft, uleft - dleft));

	m_normals.push_back(n);
	m_normals.push_back(n);
	m_normals.push_back(n);
	m_normals.push_back(n);

	//fixMe?
	m_uvs.push_back(tca);
	m_uvs.push_back(tcb);
	m_uvs.push_back(tcc);
	m_uvs.push_back(tcd);

	//fixMe?
	m_index.push_back(0);
	m_index.push_back(1);
	m_index.push_back(2);

	m_index.push_back(0);
	m_index.push_back(2);
	m_index.push_back(3);

	m_indices = 6;
}

void Rect::setPoints(glm::vec3 dright, glm::vec3 dleft, glm::vec3 uright, glm::vec3 uleft)
{
	m_vertices.clear();
	m_vertices.push_back(glm::vec3(dright));
	m_vertices.push_back(glm::vec3(dleft));
	m_vertices.push_back(glm::vec3(uright));
	m_vertices.push_back(glm::vec3(uleft));
}

//fixMe?
void Rect::setTcoords(glm::vec2 tca, glm::vec2 tcb, glm::vec2 tcc, glm::vec2 tcd)
{
	m_uvs.clear();
	m_uvs.push_back(tca);
	m_uvs.push_back(tcb);
	m_uvs.push_back(tcc);
	m_uvs.push_back(tcd);
}

void Rect::loadBufferData()
{
	m_vertexBuffer = new Buffer<glm::vec3>(m_vertices, STATIC_DRAW);
	m_normalBuffer = new Buffer<glm::vec3>(m_normals, STATIC_DRAW);
	m_uvBuffer = new Buffer<glm::vec2>(m_uvs, STATIC_DRAW);
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