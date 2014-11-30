#pragma once

#include "InputMap.h"

class MapTrackball : public InputMap
{
public:
	MapTrackball(Camera &activeCam);
	~MapTrackball();

	// updates the active camera
	void update(Camera &activeCam);
};

