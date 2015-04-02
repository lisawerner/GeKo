#include "InputMap.h"

InputMap::InputMap()
{
	m_active = false;
}

InputMap::~InputMap()
{
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

void InputMap::checkMultipleMappedKeys(int key, GLFWwindow &window){}

void InputMap::setGLFWwindow(GLFWwindow* window)
{
	m_usedWindow = window;
}

GLFWwindow* InputMap::getWindow()
{
	return m_usedWindow;
}