#pragma once

#include "GeKo_Graphics/Camera/Camera.h"
#include <map>
#include <functional>
#include <GLFW/glfw3.h>

/** InputMap is a superclass of the specific map classes.
To insert an own specific InputMap, you have to add a class containing an update function, which allocates keys or buttons to a method in the map. 
Make sure that your new specific InputMap has a name(m_name) and a boolean variable (m_active = false)
and the filled map(m_map) in its contructor.
In addition you have to adjust the InputHandler by adding the new class instance to the method 'void InputHandler::setAllInputMaps(Camera &activeCam)'.*/

class InputMap
{
public:
	InputMap();
	~InputMap();
	
	/// The method returns the map m_map, in which a key to a function is mapped
	std::map<int, std::function<void()>> getMap();

	/// Enables or disables the map
	/* DO NEVER USE THIS!!
	Please use the method "void changeActiveIputMap(std::string name)" from the class InputHandler to ensure that only one InputMap is active*/
	void setActive(bool a);

	/// The method returns whether the InputMap is active or not
	bool getActive();

	/// The Method names the InputMap
	void setName(std::string name);

	/// The method returns the name of the InputMap
	std::string getName();
	
	/// The method checks whether multiple keys are pressed to ensure performing the right action and it's implemented in the specific InputMaps
	virtual void checkMultipleMappedKeys(int key, GLFWwindow &window);

	void setGLFWwindow(GLFWwindow* window);
	GLFWwindow* getWindow();
protected:
	// This map maps a key to a function
	std::map<int, std::function<void()>> m_map;

	// Indicates whether the InputMap is active or inactive
	bool m_active;

	// The naming of the InputMap ensures that a specific InputMap instance can be returned
	std::string m_name;

	GLFWwindow* m_usedWindow;

};

