#include "Terrain.h"
#include <stb_image.h>


Terrain::Terrain(std::string filename, float resolution, float interval) 
{
	setIndexFalse();
	

	loadHeightmap(filename);

	m_interval = interval;
	m_resolution = resolution;

	m_height.resize(resolution * resolution);

	for (int i = 0; i < resolution * resolution; i++)
	{
		m_height[i] = 0.0f;
	}
	setHeight(0, 0, random(interval));
	setHeight(0, resolution - 1, random(interval));
	setHeight(resolution - 1, resolution - 1, random(interval));
	setHeight(resolution - 1, 0, random(interval));
	generate(0, 0, resolution - 1, resolution - 1, interval);

	m_vertices.push_back(glm::vec4(0 / (resolution - 1), getHeight(0, 0), 0 / (resolution - 1), 1.0f));
	m_vertices.push_back(glm::vec4(0 / (resolution - 1), getHeight(0, resolution - 1), (resolution - 1) / (resolution - 1), 1.0f));
	m_vertices.push_back(glm::vec4((resolution - 1) / (resolution - 1), getHeight(resolution - 1, 0), 0 / (resolution - 1), 1.0f));
	m_vertices.push_back(glm::vec4((resolution - 1) / (resolution - 1), getHeight(resolution - 1, resolution - 1), (resolution - 1) / (resolution - 1), 1.0f));
	for (int i = 0; i<m_vertices.size(); i++){
		// std::cout << "Punkt an der Stelle:" << i << " " << m_vertices.at(i).x << ", " << m_vertices.at(i).y << ", " << m_vertices.at(i).z << std::endl;
	}
	//m_indices = m_vertices.size();
	//m_indices = m_index.size();
	m_points = m_vertices.size();

	for (int i = 0; i < m_vertices.size(); i++)
	{
		m_uvs.push_back(glm::vec2(0, 0));
		m_index.push_back(1);
	}
	m_indices = m_index.size();

}

Terrain::~Terrain(void){
	
}

void Terrain::loadHeightmap(std::string fileName) {
	int bytesPerPixel;
	unsigned char *image = stbi_load(fileName.c_str(), &m_resolutionX, &m_resolutionY, &bytesPerPixel, 1);

	int count = 0;
	m_heightMap = new float*[m_resolutionX];
	for (int i = 0; i < m_resolutionX; ++i) {
		m_heightMap[i] = new float[m_resolutionY];
		for (int j = 0; j < m_resolutionY; ++j) {
			m_heightMap[i][j] = (float)image[count++] / 512.0f * 100;
		}
	}
}

//void Terrain::generateMesh() {
//
//	// Create vertices
//	glm::vec4 vertex;
//
//	glm::vec3 normal;
//
//	for (int z = 1; z < m_resolutionY - 1; z++){
//		for (int x = 1; x < m_resolutionX - 1; x++){
//			normal = calculateNormal(x, z);
//			vertex.x = x; vertex.y = getHeight(glm::vec2(x, z)); vertex.z = z;
//			
//			m_vertices.push_back(vertex);
//			m_normals.push_back(normal);
//			m_uvs.push_back(glm::vec2(vertex.x, vertex.z));
//		}
//	}
//
//	//Create indices
//	int offset = 0;
//	for (int z = 0; z < m_resolutionY - 3; z++){
//		for (int x = 0; x < m_resolutionX - 3; x++){
//			// 1. Triangle
//		
//			m_index.push_back(offset + x);
//			m_index.push_back(offset + x + 1);
//			m_index.push_back(offset + x + (m_resolutionY - 2));
//
//			// 2. Triangle
//			m_index.push_back(offset + x + (m_resolutionY - 2));
//			m_index.push_back(offset + x + 1);
//			m_index.push_back(offset + x + (m_resolutionY - 2) + 1);
//		}
//		offset += (m_resolutionY - 2);
//	}
//
//}

glm::vec3 Terrain::calculateNormal(int x, int z)
{
	glm::vec3 normal;

	normal.x = getHeight(glm::vec2(x - 1, z)) - getHeight(glm::vec2(x + 1, z));
	normal.y = 2.0f;
	normal.z = getHeight(glm::vec2(x, z - 1)) - getHeight(glm::vec2(x, z + 1));

	return normal;
}

float Terrain::getHeight(glm::vec2 p) {
	if (p.x < 0 || p.y < 0 || p.x >= m_resolutionX - 1 || p.y >= m_resolutionY - 1) {
		return 0.0f;
	}

	float x0y1 = m_heightMap[(int)p.x][(int)p.y + 1];
	float x0y0 = m_heightMap[(int)p.x][(int)p.y];
	float x1y1 = m_heightMap[(int)p.x + 1][(int)p.y + 1];
	float x1y0 = m_heightMap[(int)p.x + 1][(int)p.y];
	float dx = p.x - (int)p.x;
	float dy = p.y - (int)p.y;

	float interpolateX0 = x0y0 * (1 - dx) + x1y0 * dx;
	float interpolateX1 = x0y1 * (1 - dx) + x1y1 * dx;

	return interpolateX0 * (1 - dy) + interpolateX1 * dy;
}


float Terrain::getHeight(int x, int z)
{
	return m_height[z*m_resolution + x];
}
void Terrain::setHeight(int x, int z, float height)
{
	if (getHeight(x, z) > 0.0f)
		return;
	m_height[z*m_resolution + x] = height;
}
float Terrain::random(float interval)
{
	return ((float)rand() / (float)RAND_MAX) * interval;
}
void Terrain::generate(int x1, int z1, int x2, int z2, float interval)
{

	/*
	* Perform a diamond and square step of "diamond-square" algorithm
	*
	* The method gets four variables (x1, x2, z1, z2) and one interval-variable
	*/
	//we push the new points onto the stack
	if (z1 % 2 == 0){
		m_vertices.push_back(glm::vec4(x1, getHeight(x1, z1), z1, 1.0f));
		m_vertices.push_back(glm::vec4(x1, getHeight(x1, z2), z2, 1.0f));
		m_vertices.push_back(glm::vec4(x2, getHeight(x2, z1), z1, 1.0f));
		m_vertices.push_back(glm::vec4(x2, getHeight(x2, z2), z2, 1.0f));

	}
	else{
		//if z1%2 != 0, we push the new points onto the stack, but we change the order
		m_vertices.push_back(glm::vec4(x2, getHeight(x2, z1), z1, 1.0f));
		m_vertices.push_back(glm::vec4(x2, getHeight(x2, z2), z2, 1.0f));
		m_vertices.push_back(glm::vec4(x1, getHeight(x1, z1), z1, 1.0f));
		m_vertices.push_back(glm::vec4(x1, getHeight(x1, z2), z2, 1.0f));
	}
	//std::cout << "THE POINTS : " << x1 << ", " << z1 << ", " << x2 << ", " << z2 << std::endl;
	//if the width and height is lower than 2, we stop the method
	if ((x2 - x1)<2 && (z2 - z1) <2){
		return;
	}
	//if we want to divide the rectangle another time, we delete the points of the bigger rectangle (s.o)
	for (int i = 0; i<4; i++){
		m_vertices.pop_back();
	}
	//now we want new points:
	//we create a vector with x, z coordinate
	//if we want to get the new z-coordinate, we have to get it with vec2.y
	//let's get the middle point of the rectangle:
	glm::vec2 middle((x1 + x2) / 2, (z1 + z2) / 2);
	//std:: cout << "Middle-Point = " << middle.x << ", "<< middle.y << std::endl;
	//we set the height of the middle point
	float height = (getHeight(x1, z1) + getHeight(x2, z1) + getHeight(x1, z2) + getHeight(x2, z2)) / 4;
	setHeight(middle.x, middle.y, height + random(interval));
	//the middle point of the right-side
	glm::vec2 left(x1, (z1 + z2) / 2);
	// std:: cout << "Left-Point = " << left.x << ", "<< left.y << std::endl;
	//we set the height of the left middle point
	height = (getHeight(x1, z1) + getHeight(x1, z2)) / 2;
	height = height + random(interval);
	setHeight(left.x, left.y, height);
	//the middle point of the left-side
	glm::vec2 right(x2, (z1 + z2) / 2);
	//std:: cout << "Right-Point = " << right.x << ", "<< right.y << std::endl;
	//we set the height of the right middle point
	height = (getHeight(x2, z1) + getHeight(x2, z2)) / 2;
	height = height + random(interval);
	setHeight(right.x, right.y, height);
	//the middle point of the top line
	glm::vec2 top((x1 + x2) / 2, z1);
	// std:: cout << "Top-Point = " << top.x << ", "<< top.y << std::endl;
	//we set the height of the top middle point
	height = (getHeight(x1, z1) + getHeight(x2, z1)) / 2;
	height = height + random(interval);
	setHeight(top.x, top.y, height);
	//the middle point of the bottom line
	glm::vec2 bottom((x1 + x2) / 2, z2);
	// std:: cout << "Bottom-Point = " << bottom.x << ", "<< bottom.y << std::endl;
	//we set the height of the bottom middle point
	height = (getHeight(x1, z2) + getHeight(x2, z2)) / 2;
	height = height + random(interval);
	setHeight(bottom.x, bottom.y, height);
	//std::cout << "ALL SET : NEW METHOD-CALL "<< std::endl;
	//std::cout << "---------------------------"<< std::endl;
	//we call the method again with the new rectangles
	//the first at the upper left corner
	Terrain::generate(x1, z1, top.x, left.y, interval / 2);
	//the second at the upper right corner
	Terrain::generate(top.x, top.y, x2, middle.y, interval / 2);
	//the fourth at the lower right corner
	Terrain::generate(middle.x, middle.y, right.x, bottom.y, interval / 2);
	//the third at the lower left corner
	Terrain::generate(left.x, left.y, middle.x, z2, interval / 2);
}