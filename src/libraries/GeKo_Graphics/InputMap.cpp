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


	// Mapping the keys to the methods context specific
	auto trackball = [&](std::map<int, std::function<void()>> &m){
		m[GLFW_KEY_W] = cameraMoveFwd;
		m[GLFW_KEY_S] = cameraMoveBwd;
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




