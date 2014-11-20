#pragma once

#include "InputMap.h"

class IMPilotview : public InputMap
{
public:
	IMPilotview(Camera &activeCam);
	~IMPilotview();

	// updates the active camera
	void update(Camera &activeCam);
	


};

