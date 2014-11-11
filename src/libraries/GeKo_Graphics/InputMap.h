#pragma once

// TODO abfangen andrer gedrückter tasten die nicht definiert sind!!!

#include <iostream>
#include <functional>
#include <map>


#include "Camera.h"

class InputMap
{
public:
	InputMap();
	~InputMap();

	// The method fills the InputMap depending on their type
	void fillTrackball();

	// Enables/Disables the Map
	void setActive(bool a);

	bool getActive();

	std::map<int, std::function<void()>> getMap();

//protected:
	// This map maps a key to a function
	std::map<int, std::function<void()>> m_inputMap;

	// Indicates whether the InputMap is active or inactive
	bool m_active;

};

