#include "InputMap.h"

InputMap::InputMap()
{
	m_active = false;
}


InputMap::~InputMap()
{
}



// Fills the InputMaps specifically

void InputMap::fillTrackball(Camera &activeCam){

	// Setting all methods
	auto cameraMoveFwd = [&](){
		activeCam.moveForward();
	};
	auto cameraMoveBwd = [&](){
		activeCam.moveBackward();
	};
	auto cameraMoveRndL = [&](){
		activeCam.moveAroundLeft();
	};
	auto cameraMoveRndR = [&](){
		activeCam.moveAroundRight();
	};
	auto cameraMoveOverF = [&](){
		activeCam.moveOverForward();
	};
	auto cameraMoveOverB = [&](){
		activeCam.moveOverBackward();
	};


	// Mapping the keys to the methods context specific
	auto trackball = [&](std::map<int, std::function<void()>> &m){
		m[GLFW_KEY_W] = cameraMoveFwd;
		m[GLFW_KEY_S] = cameraMoveBwd;
		m[GLFW_KEY_A] = cameraMoveRndL;
		m[GLFW_KEY_D] = cameraMoveRndR;
		m[GLFW_KEY_E] = cameraMoveOverF;
		m[GLFW_KEY_Q] = cameraMoveOverB;
	};

	trackball(m_map);
}


std::map<int, std::function<void()>> InputMap::getMap(){
	return m_map;
}

void InputMap::setActive(bool a){
	m_active = a;
}

bool InputMap::getActive(){
	return m_active;
}

void InputMap::setName(std::string name){
	m_name = name;
}

std::string InputMap::getName(){
	return m_name;
}




