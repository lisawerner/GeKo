#include "InputMap.h"

InputMap::InputMap()
{
	m_active = true;
}


InputMap::~InputMap()
{
}



// Fills the InputMaps specifically

void InputMap::fillTrackball(){

	// Setting all variables
	// TODO  Use the Getter to get the Camera from the Scenegraph
	Camera cam;

	// Setting all methods
	auto cameraMoveFwd = [&](){
		cam.moveForward();
	};
	auto cameraMoveBwd = [&](){
		cam.moveBackward();
	};

	// Mapping the keys to the methods context specific
	auto trackball = [&](std::map<int, std::function<void()>> &m){
		m[GLFW_KEY_W] = cameraMoveFwd;
		m[GLFW_KEY_S] = cameraMoveBwd;
	};

	trackball(m_inputMap);
}


std::map<int, std::function<void()>> InputMap::getMap(){
	return m_inputMap;
}

void InputMap::setActive(bool a){
	m_active = a;
}

bool InputMap::getActive(){
	return m_active;
}




