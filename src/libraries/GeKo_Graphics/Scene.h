#pragma once
#include <glm/ext.hpp>
#include <GeKo_Graphics/Scenegraph.h>


/*The Scene class contains a scenegraph and represents a piece of a level or a whole level. 
In this class all the objects are contained cameras and lights included. */ 
class Scene
{
public:
	Scene();
	
	Scene(std::string sceneName);
	~Scene();

	std::string getSceneName();

	void setSceneName(std::string sceneName);

	void setScenegraph(Scenegraph scenegraph);
	
	Scenegraph* getScenegraph();

private:
	std::string m_sceneName;
	Scenegraph m_sceneGraph;


};