#pragma once
#include <GeKo_Graphics/Scenegraph/Scenegraph.h>
#include <GeKo_Graphics/Scenegraph/Scene.h>
#include <iostream>
/**
The class "Level" has a unique name and can be identified with this name. 
A level manages his scenes, can change them, add and remove them
*/
class Level
{
public:
    ///The constructor for the level
	/**The level needs a name, but do not consist of any scenes at the beginning*/
	Level(const char* levelName);
	~Level();
	
	///A getter Method which returns a const char
	/**A getter for the name of the level*/
	const char* getLevelName();


	///This method adds a Scene to the level
	/**/
	void addScene(Scene scene);

	///This method deletes a specific Scene by its name
	/**/
	void removeScene(std::string sceneName);

	///Returns a Scene object
	/**Need a Scenename to find a Scene. Returns NULL if the Scene does not exist*/
	Scene* getScene(std::string sceneName);

	void changeScene(std::string sceneName);

protected:
	const char* m_levelName;
	std::vector<Scene> m_sceneSet;
	Scene m_activeScene;
};

