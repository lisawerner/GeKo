#pragma once

// To use the InputHandler create an instance in the main.cpp and call setAllInputMaps() to fill all the InputMaps
// set the key callback (glfwSetKeyCallback(window, key_callback);) in the main.cpp

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>

#include "InputMap.h"



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

