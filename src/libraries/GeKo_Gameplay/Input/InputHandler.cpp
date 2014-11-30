#include "InputHandler.h"


InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}


// Iterates over m_allInputMaps, where all the InputMaps are stored and returns the one,
// whose member variable m_active is set true
// if there is no active InputMap he program exits with a message saying there's no InputMap active
// if there is more than one active InputMap the program exits with a message saying it's not the only map being active

InputMap* InputHandler::getActiveInputMap() {

	int i = 0;
	InputMap* activeInputMap = new InputMap();

	for (int j = 0; j < m_allInputMaps.size(); j++)
	{
		if (m_allInputMaps.at(j)->getActive() == true){
			activeInputMap = m_allInputMaps.at(j);
			i++;
		}
	}

	if (i == 0){
		std::cerr << "No InputMap is active." << std::endl;
		exit(1);
	}

	else if (i != 1){
		std::cerr << "Too Many InputMaps are active." << std::endl;
		exit(1);
	}
	return activeInputMap;
}



// if there is any InputMap named like the parameter, the InputMap is returned,
// else an error message is given

// TODO maybe an exception 

InputMap* InputHandler::getInputMap(std::string name) {

	InputMap* instance = new InputMap();

	for (int i = 0; i < m_allInputMaps.size(); i++)
	{
		if (m_allInputMaps.at(i)->getName() == name){
			instance = m_allInputMaps.at(i);
			return instance;
		}
	}
	std::cerr << "No map is named like this" << std::endl;

	return 0;
}



// Creates various InputMaps, fills them with their specific mapping and pushes them onto a vector, 
// which is the member variable m_allInputMaps

void InputHandler::setAllInputMaps(Camera &activeCam){
	
	// Instances of the Maps, which are named depending on their context
	MapTrackball* contextTrackball = new MapTrackball(activeCam);
	MapPilotview* contextPilotview = new MapPilotview(activeCam);
	MapPlayerview* contextPlayerview = new MapPlayerview(activeCam);

	// The Maps are stored in a vector
	m_allInputMaps.push_back(contextTrackball);
	m_allInputMaps.push_back(contextPilotview);
	m_allInputMaps.push_back(contextPlayerview);
}

// Sets the InputMap active according to its name and ensures that just this InputMap is active
void InputHandler::changeActiveInputMap(std::string name){
	// additional loop over all the InputMaps is necessary because the method retrieves always the last active InputMap and for the first time there's no InputMap active
	for (int j = 0; j < m_allInputMaps.size(); j++)
	{
		if (m_allInputMaps.at(j)->getActive() == true)
			getActiveInputMap()->setActive(false);
	}
	getInputMap(name)->setActive(true);
}