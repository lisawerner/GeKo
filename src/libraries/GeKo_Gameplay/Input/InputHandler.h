#pragma once

#include "GeKo_Graphics/Defs.h"
#include "InputMap.h"
#include "MapTrackball.h"
#include "MapPilotview.h"
#include "MapPlayerview.h"
#include <cstdlib> 


class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	// creates InputMaps, fills them specifically, and pushes them on the membervector
	void setAllInputMaps(Camera &activeCam);

	// The method returns the InputMap with the matching name
	InputMap* getInputMap(std::string name);

	// The method returns the active InputMap
	InputMap* getActiveInputMap();

	// Sets the InputMap active according to its name and ensures that just this InputMap is active
	void changeActiveInputMap(std::string name);

protected:
	// stores all the InputMaps by using setAllInputMaps
	std::vector<InputMap*> m_allInputMaps;

	


};

