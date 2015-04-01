#pragma once

#include <GeKo_Graphics/Geometry/Geometry.h>
#include <time.h>
#include <iostream>

class Terrain : public Geometry {


public:

	Terrain(std::string filename, float resolution, float interval);

	~Terrain();

	void loadHeightmap(std::string filename);

	void generateMesh();

	glm::vec3 calculateNormal(int x, int z);

	float getHeight(glm::vec2 position);
	float getHeight(int x, int z);
	void setHeight(int x, int z, float height);

	float random(float interval);

	void generate(int x1, int z1, int x2, int z2, float interval);

protected:
	std::vector<float> m_height;
	int m_resolutionX, m_resolutionY;

	float **m_heightMap;

	float m_interval, m_resolution;


};
