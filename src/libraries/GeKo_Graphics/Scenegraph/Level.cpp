#include <GeKo_Graphics/Scenegraph/Level.h>


Level::Level(const char* levelName)
{
	m_levelName = levelName;
}


Level::~Level()
{
}

const char* Level::getLevelName()
{
	return m_levelName;
}

void Level::addScene(Scene scene)
{
	m_sceneSet.push_back(scene);
}

void Level::removeScene(std::string sceneName)
{
	for (int i = 0; i < m_sceneSet.size(); i++)
	{
		if (m_sceneSet.at(i).getSceneName() == sceneName)
		{
			m_sceneSet.erase(m_sceneSet.begin() + i);
		}
	}
}

Scene* Level::getScene(std::string sceneName )
{
	for (int i = 0; i < m_sceneSet.size(); i++)
	{
		if (m_sceneSet.at(i).getSceneName() == sceneName)
		{
			return &m_sceneSet.at(i);
		}
	}
	std::cout << "ERROR: The Scene with the name " << sceneName << " does not exist!" << std::endl;
	return NULL;
}

void Level::changeScene(std::string sceneName)
{
	for (int i = 0; i < m_sceneSet.size(); i++)
	{
		if (m_sceneSet.at(i).getSceneName() == sceneName)
		{
			m_activeScene = m_sceneSet.at(i);
		}
	}
}