#pragma once

#include "InputMap.h"

class IMTrackball : public InputMap
{
public:
	IMTrackball(Camera &activeCam);
	~IMTrackball();

	// updates the active camera
	void update(Camera &activeCam);
};

