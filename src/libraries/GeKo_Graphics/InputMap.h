#pragma once

// TODO catch keys that are not defined

#include "GeKo_Graphics/Defs.h"
#include "Camera.h"
#include "Trackball.h"
#include <map>
#include <functional>

class InputMap
{
public:
	InputMap();
	~InputMap();

	// The method fills the InputMap for the trackball
	void fillTrackball(Camera &activeCam);

	// Enables / Disables the Map
	/* DO NEVER EVER EVER EVER USE THIS!!
	Please use the method "void changeActiveIputMap(std::string name)" from the class InputHandler to ensure that only one InputMap is active
	*/
	void setActive(bool a);
	bool getActive();

	std::map<int, std::function<void()>> getMap();

	void setName(std::string name);
	std::string getName();



protected:

	// This map maps a key to a function
	std::map<int, std::function<void()>> m_map;

	// Indicates whether the InputMap is active or inactive
	bool m_active;

	// The naming of the InputMap ensures that a specific InputMap instance can be returned
	std::string m_name;

};

