#pragma once
#include <GeKo_Graphics/Geometry.h>

class Teapot : public Geometry
{
public:

	Teapot();
	~Teapot();

	void loadBufferData();
	void renderGeometry();
};