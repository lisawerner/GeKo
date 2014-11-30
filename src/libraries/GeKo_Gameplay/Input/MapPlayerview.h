#pragma once

#include "InputMap.h"

class MapPlayerview : public InputMap
{
public:
	MapPlayerview(Camera &activeCam);
	~MapPlayerview();

	// updates the active camera
	void update(Camera &activeCam);

	void checkMultipleMappedKeys(int key, GLFWwindow &window);


};

