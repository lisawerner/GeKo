#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>

#include "InputMap.h"



class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	
	std::map<int, std::function<void()>> getActiveMap();

	// creates InputMaps, fills them specifically, and pushes them on the membervector
	void setAllInputMaps();
	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


	// stores all the InputMaps by using setAllInputMaps
	std::vector<InputMap*> m_allInputMaps;

	


};

