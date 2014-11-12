#pragma once
#include <glm/glm.hpp>
#include<vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GeKo_Graphics/Buffer.h>

/*This class should be used as a interface class. It provides two Methods to load Data and to render the Vertice Data. 
  Every Geometry Object which will inherit this class should use this methods. A vector for the vertices is provided as well.*/
class Geometry
{
public:
	
	///Standard constructor, sets the m_wasLoaded boolean to false
	/**/
	Geometry();
	~Geometry();

	///A Method to load Buffer
	/**The vertices Data from m_vertices will be loaded into Buffers, so the Shader can use this information for the position of the object*/
	virtual void loadBufferData();

	///A method to render the Object 
	/**In the while-Loop of the main-programm (Renderer or else) this method will be called to draw the array*/
	virtual void renderGeometry();

	///Returns m_vertices of the Geometry Object
	/**/
	std::vector<glm::vec4> getVertices();

	///Returns m_normals of the Geometry Object
	/**/
	std::vector<glm::vec3> getNormals();

	///Returns m_uvs of the Geometry Object
	/**/
	std::vector<glm::vec2> getUV();

	///Returns m_index of the Geometry Object
	/**/
	std::vector<GLuint> getIndexList();
	
	///Sets m_wasLoaded to true
	/**/
	void setLoaded();

	///Sets m_wasLoaded to false
	/**/
	void resetLoaded();

	///Returns the boolean of m_wasLoaded
	/**/
	bool isLoaded();

protected:
	int m_points;
	std::vector<glm::vec4> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_uvs;

	std::vector<GLuint> m_index;
	int m_indices;

	Buffer<glm::vec4>* m_vertexBuffer;
	Buffer<glm::vec3>* m_normalBuffer;
	Buffer<glm::vec2>* m_uvBuffer;
	//Indexbuffer braucht einen speziellen Buffer
//	Buffer<GLuint>* m_indexBuffer;

	GLuint m_vaoBuffer;
private:
	bool m_wasLoaded;
};
/*Questions and TODOS:
	1. virtual methods shouldnt be used, maybe theres another way to do it?
	2. Should reconsider to have the Buffer as a Pointer
*/