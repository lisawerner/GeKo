#include "InputHandler.h"

// create an instance of the InputHandler in the main.cpp and call setAllInputMaps() to fill all the map types
// call setCharCallback in the main.cpp

InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}


// Iterates over m_allInputMaps, where all the InputMaps are stored and returns the one,
// whose member variable m_active is set true


// if there is no actve InputMap an empty map is returned
// if there is more than one active InputMap the last one in the list, which is active,
// is returned with an message saying it's not the only map being active

std::map<int, std::function<void()>> InputHandler::getActiveMap() {

	int i = 0;
	std::map<int, std::function<void()>> temp;

	for (int j = 0; j < m_allInputMaps.size();j++)
	{
		if (m_allInputMaps.at(j)->getActive() == true){
			temp = m_allInputMaps.at(j)->getMap();
			i++;
		}
	}

	if(i == 0){
		perror ("No InputMap is active.");
	} else if (i != 1){
		perror ("Too Many InputMaps are active.");
	}
	return temp;
}



// If there are is any InputMap:
// Return the First InputMap
// If there is no InputMap:
// Return an error

InputMap* InputHandler::getFirstInputMapInstance() {

	int i = 0;
	InputMap* temp;
	if (m_allInputMaps.size() >= 1){
		temp = m_allInputMaps.at(0);
	} else {
		perror("There is no InputMap available.");
	}
	return temp;
}



// Creates various InputMaps, fills them with their specific mapping and pushes them onto a vector, 
// which is the member variable m_allInputMaps

void InputHandler::setAllInputMaps(){

	// Instances of the Maps, which are named depending on their context
	InputMap* contextTrackball = new InputMap();

	// The Maps are filled context specific
	contextTrackball->fillTrackball();

	// The Maps are stored in a vector
	m_allInputMaps.push_back(contextTrackball);

}




