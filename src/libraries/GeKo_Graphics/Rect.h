#pragma once
#include <GeKo_Graphics/Geometry.h>

class Rect : public Geometry
{
public:

	Rect();
	~Rect();

	void loadBufferData();

	
	void renderGeometry();

};