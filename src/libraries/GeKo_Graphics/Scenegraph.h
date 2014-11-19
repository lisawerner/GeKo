#pragma once
#include <GeKo_Graphics/Node.h>
#include <GeKo_Graphics/Camera.h>


/**Every scenegraph is connected with one scene.
The scenegraph is managing all the objects in the scene which are added to the scenegraph by adding them to the scene*/
class Scenegraph
{
public:
	Scenegraph();
	
	///A scenegraph just gets a Name
	/**The m_scenegraphName will be set and the m_rootNode will be set automatically too*/
	Scenegraph(std::string scenegraphName);
	~Scenegraph();

	
	///Returns m_scenegraphName as a string
	/**/
	std::string getScenegraphName();
	void setScenegraphName(std::string scenegraphName);
	
	/// Returns the m_rootNode as a Node object
	/**/
	Node* getRootNode();
	void setRootNode(Node rootNode);

	///Returns the m_activeCamera Camera-Object
	/**/
	Camera* getActiveCamera();
	void setActiveCamera(std::string cameraName);

	///Returns a Camera-Object
	/**The Camera Name must be known for finding the Camera Object. If there is no such Camera with this name
		an error will be placed and NULL returns*/
	Camera* getCamera(std::string cameraName);
	void addCamera(Camera camera);

protected:

	std::string m_scenegraphName;
	Node m_rootNode;
	
	Camera* m_activeCamera;
	std::vector<Camera> m_cameraSet;
};

/*Questions and TODOS:
	1. Could there be more than one active Camera?
		- e.x. a editor has 4 views at the same time (top, bot,left, right)
	2. Should the Camera be set to the Rootnode and from the rootnode to a Node? 
		- then you have to go two ways, another possibility could be, that a Node knows his scenegraph
		- then the camera would be add to the scenegraph list when adding to a Node as well
		- CONS: Why should the Node know the scenegraph? Just one case did not qualify this method!
	3. TODO: Light class
	*/
