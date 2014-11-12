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

}


void Geometry::renderGeometry()
{

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