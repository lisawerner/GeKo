#include "Scene.h"

Scene::Scene()
{

}
///A scene just gets a name
/*The m_sceneName will be set and a scenegraph object m_sceneGraph will be provided automatically*/
Scene::Scene(std::string sceneName)
{
	m_sceneName = sceneName;
}

Scene::~Scene()
{

}

///A Getter for the name of the Scene
/*Returns the string msceneName*/
std::string Scene::getSceneName()
{
	return m_sceneName;
}

///A Setter for the name of the Scene
/*The Method gets a string for m_sceneName*/
void Scene::setSceneName(std::string sceneName)
{
	m_sceneName = sceneName;
}

///A setter for a scenegraph
/*The Constructor sets automatically a scenegraph to the scene*/
void Scene::setScenegraph(Scenegraph scenegraph)
{
	m_sceneGraph = scenegraph;
}

///A getter for the scenegraph
/*Returns a Scenegraph object m_sceneGraph*/
Scenegraph* Scene::getScenegraph()
{
	return &m_sceneGraph;
}