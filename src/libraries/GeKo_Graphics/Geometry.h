#pragma once
#include <glm/glm.hpp>
#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*This class should be used as a interface class. It provides two Methods to load Data and to render the Vertice Data. 
  Every Geometry Object which will inherit this class should use this methods. A vector for the vertices is provided as well.*/
class Geometry
{
public:
	
	Geometry();
	~Geometry();

	virtual void loadBufferData();
	virtual void renderGeometry();

//protected:
	std::vector<glm::vec3> m_vertices;
	std::vector<GLuint> m_index;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_uvs;
	int m_points;
	int m_indices;
};