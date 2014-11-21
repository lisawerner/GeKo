#include "InputHandler.h"


InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}


// Iterates over m_allInputMaps, where all the InputMaps are stored and returns the one,
// whose member variable m_active is set true

// if there is no actve InputMap an empty InputMap is returned
// if there is more than one active InputMap the last one in the list, which is active,
// is returned with an message saying it's not the only map being active

// TODO exception instead of empty input map

InputMap* InputHandler::getActiveInputMap() {

	int i = 0;
	InputMap* temp= new InputMap();

	for (int j = 0; j < m_allInputMaps.size(); j++)
	{
		if (m_allInputMaps.at(j)->getActive() == true){
			temp = m_allInputMaps.at(j);
			i++;
		}
	}

	if (i == 0){
		perror("No InputMap is active.");
	}
	else if (i != 1){
		perror("Too Many InputMaps are active.");
	}
	return temp;
}



// If there is any InputMap named like the parameter, the InputMap is returned,
// else an empty InputMap is returned with an error message

// TODO exception instead of empty input map

InputMap* InputHandler::getInputMap(std::string name) {

	InputMap* instance = new InputMap();
	for (int i = 0; i < m_allInputMaps.size(); i++)
	{
		if (m_allInputMaps.at(i)->getName() == name){
			instance = m_allInputMaps.at(i);
			return instance;
		}
	}
	perror("No Map is named like this");
	return instance;
}




// Creates various InputMaps, fills them with their specific mapping and pushes them onto a vector, 
// which is the member variable m_allInputMaps

void InputHandler::setAllInputMaps(Camera &activeCam){
	
	// Instances of the Maps, which are named depending on their context
	IMTrackball* contextTrackball = new IMTrackball(activeCam);
	IMPilotview* contextPilotview = new IMPilotview(activeCam);

	// The Maps are stored in a vector
	m_allInputMaps.push_back(contextTrackball);
	m_allInputMaps.push_back(contextPilotview);
}


// Sets the InputMap active according to its name and ensures that just this InputMap is active
void InputHandler::changeActiveInputMap(std::string name){
	getActiveInputMap()->setActive(false);
	getInputMap(name)->setActive(true);
}





