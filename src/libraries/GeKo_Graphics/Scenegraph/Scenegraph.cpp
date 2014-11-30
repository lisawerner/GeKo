#include "Scenegraph.h"

Scenegraph::Scenegraph()
{
	Node root("Root");
	setRootNode(root);
	getRootNode()->setIdentityMatrix_ModelMatrix();
}


Scenegraph::Scenegraph(std::string scenegraphName)
{
	m_scenegraphName = scenegraphName;
	Node root("Root");
	setRootNode(root);
	getRootNode()->setIdentityMatrix_ModelMatrix();
}

Scenegraph::~Scenegraph()
{

}


std::string Scenegraph::getScenegraphName()
{
	return m_scenegraphName;
}

void Scenegraph::setScenegraphName(std::string scenegraphName)
{
	m_scenegraphName = scenegraphName;
}


Node* Scenegraph::getRootNode()
{
	return &m_rootNode;
}

void Scenegraph::setRootNode(Node rootNode)
{
	m_rootNode = rootNode;
}

Camera Scenegraph::getActiveCamera()
{
	return m_activeCamera;
}

void Scenegraph::setActiveCamera(std::string cameraName)
{
	for (int i = 0; i < m_cameraSet.size(); i++)
	{
		if (m_cameraSet.at(i).getName() == cameraName)
			m_activeCamera = m_cameraSet.at(i);
	}
}




Camera* Scenegraph::getCamera(std::string cameraName)
{
	for (int i = 0; i < m_cameraSet.size(); i++)
	{
		if (m_cameraSet.at(i).getName() == cameraName)
			return &m_cameraSet.at(i);
	}

	std::cout << "ERROR: The Camera with the name " << cameraName << " does not exist!" << std::endl;
	return NULL;
}

void Scenegraph::addCamera(Camera camera)
{
	m_cameraSet.push_back(camera);
}
