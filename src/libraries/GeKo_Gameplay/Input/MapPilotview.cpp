#include <GeKo_Gameplay/Input/MapPilotview.h>

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

	auto cameraMoveDiagonalFwdL = [&](){
		activeCam.moveDiagonalFwdL();
	};

	auto cameraMoveDiagonalFwdR = [&](){
		activeCam.moveDiagonalFwdR();
	};

	auto cameraMoveDiagonalBwdL = [&](){
		activeCam.moveDiagonalBwdL();
	};

	auto cameraMoveDiagonalBwdR = [&](){
		activeCam.moveDiagonalBwdR();
	};

	// Mapping the keys to the methods context specific
	auto pilotview = [&](std::map<int, std::function<void()>> &m){
		m[GLFW_KEY_W] = cameraMoveFwd;
		m[GLFW_KEY_S] = cameraMoveBwd;
		m[GLFW_KEY_A] = cameraMoveLeft;
		m[GLFW_KEY_D] = cameraMoveRight;
		m[GLFW_KEY_E] = cameraMoveUp;
		m[GLFW_KEY_Q] = cameraMoveDown;
		m[GLFW_KEY_W + GLFW_KEY_A] = cameraMoveDiagonalFwdL;
		m[GLFW_KEY_W + GLFW_KEY_D] = cameraMoveDiagonalFwdR;
		m[GLFW_KEY_S + GLFW_KEY_A] = cameraMoveDiagonalBwdL;
		m[GLFW_KEY_S + GLFW_KEY_D] = cameraMoveDiagonalBwdR;
	};

	pilotview(m_map);
}


void MapPilotview::checkMultipleMappedKeys(int key, GLFWwindow &window){
	if (key == GLFW_KEY_W){
		if (glfwGetKey(&window, GLFW_KEY_A) == GLFW_PRESS){
			m_map.at(GLFW_KEY_W + GLFW_KEY_A)(); 
		}
		else if (glfwGetKey(&window, GLFW_KEY_D) == GLFW_PRESS){
			m_map.at(GLFW_KEY_W + GLFW_KEY_D)(); 
		}
		else {
			m_map.at(key)(); 
		}
	}
		
	if (key == GLFW_KEY_S){
		if (glfwGetKey(&window, GLFW_KEY_A) == GLFW_PRESS){
			m_map.at(GLFW_KEY_S + GLFW_KEY_A)(); 
		}
		else if (glfwGetKey(&window, GLFW_KEY_D) == GLFW_PRESS){
			m_map.at(GLFW_KEY_S + GLFW_KEY_D)(); 
		}
		else{
			m_map.at(key)();
		}
	}

	else{
		m_map.at(key)();
	}
			
}



