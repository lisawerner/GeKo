#pragma once

#include "InputMap.h"

class MapPilotview : public InputMap
{
public:
	MapPilotview(Camera &activeCam);
	~MapPilotview();

	// updates the active camera
	void update(Camera &activeCam);
	// the method considers multiple keys being pressed at the same time
	void checkMultipleMappedKeys(int key, GLFWwindow &window);
};

