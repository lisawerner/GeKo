#include "GeKo_Gameplay/Input/MapPilotview.h"

MapPilotview::MapPilotview(Camera &activeCam)
{
	m_active = false;
	m_name = "Pilotview";
	update(activeCam);
}

MapPilotview::~MapPilotview()
{
}

void MapPilotview::update(Camera &activeCam){

	// Setting all methods
	auto cameraMoveFwd = [&](){
		activeCam.moveForward();
	};

	auto cameraMoveBwd = [&](){
		activeCam.moveBackward();
	};

	auto cameraMoveLeft = [&](){
		activeCam.moveLeft();
	};

	auto cameraMoveRight = [&](){
		activeCam.moveRight();
	};

	auto cameraMoveUp = [&](){
		activeCam.moveUp();
	};

	auto cameraMoveDown = [&](){
		activeCam.moveDown();
	};

	auto cameraTurnLeft = [&](){
		activeCam.turnLeft();
	};

	auto cameraTurnRight = [&](){
		activeCam.turnRight();
	};

	auto cameraTurnUp = [&](){
		activeCam.turnUp();
	};

	auto cameraTurnDown = [&](){
		activeCam.turnDown();
	};

	// Mapping the keys to the methods context specific
	auto pilotview = [&](std::map<int, std::function<void()>> &m){
		m[GLFW_KEY_W] = cameraMoveFwd;
		m[GLFW_KEY_S] = cameraMoveBwd;
		m[GLFW_KEY_A] = cameraMoveLeft;
		m[GLFW_KEY_D] = cameraMoveRight;
		m[GLFW_KEY_E] = cameraMoveUp;
		m[GLFW_KEY_Q] = cameraMoveDown;
		m[GLFW_KEY_LEFT] = cameraTurnLeft;
		m[GLFW_KEY_RIGHT] = cameraTurnRight;
		m[GLFW_KEY_UP] = cameraTurnUp;
		m[GLFW_KEY_DOWN] = cameraTurnDown;
	};

	pilotview(m_map);
}

void MapPilotview::checkMultipleMappedKeys(int key, GLFWwindow &window){

	if (glfwGetKey(&window, GLFW_KEY_W) == GLFW_PRESS){
		m_map.at(GLFW_KEY_W)();
	}
	if (glfwGetKey(&window, GLFW_KEY_A) == GLFW_PRESS){
		m_map.at(GLFW_KEY_A)();
	}
	if (glfwGetKey(&window, GLFW_KEY_S) == GLFW_PRESS){
		m_map.at(GLFW_KEY_S)();
	}
	if (glfwGetKey(&window, GLFW_KEY_D) == GLFW_PRESS){
		m_map.at(GLFW_KEY_D)();
	}
	if (key != GLFW_KEY_W && key != GLFW_KEY_A && key != GLFW_KEY_S && key != GLFW_KEY_D){
		m_map.at(key)();
	}		
}