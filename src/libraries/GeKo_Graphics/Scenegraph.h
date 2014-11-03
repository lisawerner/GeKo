#pragma once
#include <GeKo_Graphics\Node.h>

/**Every scenegraph is connected with one scene.
The scenegraph is managing all the objects in the scene which are added to the scenegraph by adding them to the scene*/
class Scenegraph
{
public:
	Scenegraph();
	
	Scenegraph(std::string scenegraphName);
	~Scenegraph();

	
	void setScenegraphName(std::string scenegraphName);

	
	std::string getScenegraphName();

	
	void setRootNode(Node rootNode);

	
	Node* getRootNode();

protected:
	Node m_rootNode;
	std::string m_scenegraphName;
};

