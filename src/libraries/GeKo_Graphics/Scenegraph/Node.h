#pragma once
#include <vector>
#include <glm/ext.hpp>
#include <iostream>
#include <GeKo_Graphics/Object/Geometry.h>
#include <GeKo_Graphics/Object/Rect.h>
#include <GeKo_Graphics/Camera/Camera.h>
#include <GeKo_Graphics/Material/Texture.h>
#include <GeKo_Graphics/Shader/Shader.h>

///A Node contains Infomration, which can be rendered in the world
/*A "Node" should be a container for Geometry, Material, Lights and Cameras and provides all the information a shader could need
  like a Modelmatrix for example. It has one parent and can have a lot of children or none. Every Node exists as long as the scenegraph */
class Node
{
public:
	Node();
	///The constructor of a Node
	/**At the beginning a Node just needs a name, the m_modelMatrix will be set to the identity matrix*/
	Node(std::string nodeName);
	~Node();

	///Returns the m_name of the Node as a string
	/**/
	std::string getNodeName();
	void setNodeName(std::string nodeName);

	///Returns the m_Node Object which represent the Parent Node
	/**/
	Node* getParentNode();
	void setParentNode(Node* parentNode);

	///Returns a Node-Object with the name nodeName
	/**This Method iterates over the m_childrenSet and returns the Node with the nodeName*/
	Node* getChildrenNode(std::string nodeName);
	///A Node-Object will be add to m_childrenSet
	/**The Parent Node will be set automatically*/
	void addChildrenNode(Node* childrenNode);
	
	///This method deletes a Node-Object in m_childrenSet
	/**The user gives the method a name and the method iterates over the m_childrenSet 
	and deletes the Child with the nodeName*/
	void deleteChildrenNode(std::string nodeName);

	///A method to clear m_childrenSet
	/**Every Child Node in m_childrenSet will be deleted*/
	void clearChildrenSet();

	///Returns m_geometry as a Geometry object
	/**/
	Geometry* getGeometry();
	///A Geometry Object will be linked with the node
	/**A geometry Object will be linked with the node and will be saved as m_geometry*/
	void addGeometry(Geometry* geometry);

	///Returns m_texture as a Texture object
	/**/
	Texture* getTexture();
	void addTexture(Texture* texture);

	///Returns m_normalmap as a Texture object
	/**/
	Texture* getNormalMap();
	void addNormalMap(Texture* normalmap);

  ///Returns m_heightmap as a Texture object
  /**/
  Texture* getHeightMap();
  void addHeightMap(Texture* heightmap, float heightScale = 0.07f, float heightBias = 0.1f);

	///Returns m_Camera as a Camera Object
	/**/
	Camera* getCamera();
	void setCamera(Camera* camera);

	///Returns the m_modelMatrix as a mat4
	/**/
	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4);

	///Returns m_rotationMatrix as a mat4
	/**/
	glm::mat4 getRotationMatrix();
	///A rotation will be added to the Modelmatrix
	/**The user tells the method how big the angle should be and around which axis we are rotation.
	Then the method calls the rotate(...) Method of opengl and updates the modelmatrix*/
	void addRotation(float angle, glm::vec3 axis);
	
	///Returns m_translateMatrix as a mat4
	/**/
	glm::mat4 getTranslationMatrix();
	///A translation will be added to the Modelmatrix
	/**The user tells the method how far the object will move in x,y and z direction.
	Then the method calls the translate(...) Method of opengl and updates the modelmatrix*/
	void addTranslation(float x, float y, float z);

	///Returns m_scaleMatrix as a mat4
	/**/
	glm::mat4 getScaleMatrix();
	///A scale will be added to the Modelmatrix
	/**The user tells the method in which directions (x, y and/or z) the object should be scaled.
	Then the method calls the scale(...) Method of opengl and updates the modelmatrix*/
	void addScale(float x, float y, float z);

	///The Translationmatrix will be set to the Identity matrix
	/**The Translationsmatrix will be replaced and the Modelmatrix will be updated using the inverse of the actual m_translateMatrix*/
	void setIdentityMatrix_Translate();
	///The same as setIdentityMatrix_Translate() just for m_scaleMatrix
	/**/
	void setIdentityMatrix_Scale();
	///The same as setIdentityMatrix_Translate() just for m_rotationMatrix
	/**/
	void setIdentityMatrix_Rotation();
	///The same as setIdentityMatrix_Translate() just for m_modelMatrix
	/**/
	void setIdentityMatrix_ModelMatrix();
	
	///A method to tell the Node to draw itself
	/**The Node will take this call and forward it to the geometry, so the geometry will be drawed*/
	void render();

	void render(ShaderProgram &shader);

	glm::mat4 updateModelMatrix();

	std::vector<Node*>* getChildrenSet();

	bool hasTexture();
	bool hasNormalMap();
	bool hasCamera();
	bool hasGeometry();

protected:
	std::string m_nodeName;

	Node* m_parentNode;
	std::vector<Node*> m_childrenSet;

	Geometry* m_geometry;
	Texture* m_texture;
  Texture* m_normalmap;
  Texture* m_heightmap;
  float m_heightScale;
  float m_heightBias;

	Camera* m_camera;

	glm::mat4 m_modelMatrix;
	glm::mat4 m_rotationMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_translateMatrix;

	bool m_hasTexture;
  bool m_hasNormalMap;
  bool m_hasHeightMap;
	bool m_hasCamera;
	bool m_hasGeometry;

private:
	///A method which updates the Modelmatrix
	/**When a new rotation, scale or translation is added to the object, then the modelMatrix needs an update.
	This update will be done by this method, the matrix which will be added to the modelMatrix is the updatedMatrix*/
	void updateModelMatrix(glm::mat4 updateMatrix);
	

};

/* Questions and TODOS:
	1. Will the matrix-Functions work? They are not testes yet!
	2. TODO: addLight(Light* light)
	3. A Node should contain more than one Texture (normal, color etc.)
	4. Can a camera object linked directly to a node or does it have to be linked with the rootNode first?
	5. TODO: The Node should have more than one Camera Object at a time
	6. I should reconsider the Pointer to the camera and the geometry (Geometry will be a failure without pointer at the moment!)
		- I do not think it would be good without the pointer
*/
