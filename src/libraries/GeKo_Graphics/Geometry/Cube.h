#pragma once
#include <GeKo_Graphics/Geometry/Geometry.h>

/**A Cube with vertices, normals and uv-coordinates*/
class Cube : public Geometry{

public:
	Cube();
	~Cube();

	///A Method to load Buffer
	/**The vertices Data from m_vertices will be loaded into Buffers, so the Shader can use this information for the position of the object*/
	//void loadBufferData();

	///A method to render the Object 
	/**In the while-Loop of the main-programm (Renderer or else) this method will be called to draw the array*/
	//void renderGeometry();


};