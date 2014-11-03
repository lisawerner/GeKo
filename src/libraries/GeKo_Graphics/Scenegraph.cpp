#include "Scenegraph.h"

Scenegraph::Scenegraph()
{
	Node root("Root");
	setRootNode(root);
}

///A scenegraph just gets a Name
/*The m_scenegraphName will be set and the m_rootNode will be set automatically too*/
Scenegraph::Scenegraph(std::string scenegraphName)
{
	m_scenegraphName = scenegraphName;

	Node root("Root");
	setRootNode(root);
}

Scenegraph::~Scenegraph()
{

}

///A getter for the Name of the scenegraph
/*Returns a the m_scenegraphName as a string*/
std::string Scenegraph::getScenegraphName()
{
	return m_scenegraphName;
}

///A Setter for the name of the scenegraph
/*Sets the m_scenegraphName attribute */
void Scenegraph::setScenegraphName(std::string scenegraphName)
{
	m_scenegraphName = scenegraphName;
}

/// A getter for the root node
/*Returns the m_rootNode as a Node object*/
Node* Scenegraph::getRootNode()
{
	return &m_rootNode;
}

///A setter for the Root Node of the scenegraph
/*The m_rootNode attribute will be set to a Node object*/
void Scenegraph::setRootNode(Node rootNode)
{
	m_rootNode = rootNode;
}