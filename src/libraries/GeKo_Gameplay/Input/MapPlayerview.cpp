#include <GeKo_Gameplay/Input/MapPlayerview.h>

MapPlayerview::MapPlayerview(Camera &activeCam)
{
	m_active = false;
	m_name = "Playerview";
	update(activeCam);
}


MapPlayerview::~MapPlayerview()
{
}


void MapPlayerview::update(Camera &activeCam){

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

	auto cameraTurn = [&](){
		activeCam.turn();
	};

	// Mapping the keys to the methods context specific
	auto playerview = [&](std::map<int, std::function<void()>> &m){
		m[GLFW_KEY_W] = cameraMoveFwd;
		m[GLFW_KEY_S] = cameraMoveBwd;
		m[GLFW_KEY_A] = cameraMoveLeft;
		m[GLFW_KEY_D] = cameraMoveRight;
		m[GLFW_MOUSE_BUTTON_LEFT] = cameraTurn;
		
	};

	playerview(m_map);
}

void MapPlayerview::checkMultipleMappedKeys(int key, GLFWwindow &window){
	if (key == GLFW_MOUSE_BUTTON_LEFT){
		if (glfwGetKey(&window, GLFW_KEY_W) == GLFW_PRESS){
			m_map.at(GLFW_KEY_W )();
			m_map.at(GLFW_MOUSE_BUTTON_LEFT)();
		}
		else if (glfwGetKey(&window, GLFW_KEY_S) == GLFW_PRESS){
			m_map.at(GLFW_KEY_S)();
			m_map.at(GLFW_MOUSE_BUTTON_LEFT)();
		}
		else if (glfwGetKey(&window, GLFW_KEY_A) == GLFW_PRESS){
			m_map.at(GLFW_KEY_A)();
			m_map.at(GLFW_MOUSE_BUTTON_LEFT)();
		}
		else if (glfwGetKey(&window, GLFW_KEY_D) == GLFW_PRESS){
			m_map.at(GLFW_KEY_D)();
			m_map.at(GLFW_MOUSE_BUTTON_LEFT)();
		}
		else {
			m_map.at(key)();
		}
	}
	else{
		m_map.at(key)();
	}

}