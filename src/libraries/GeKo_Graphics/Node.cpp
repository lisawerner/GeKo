#include "Node.h"

Node::Node()
{
	m_nodeName = "Default";

	setIdentityMatrix_ModelMatrix();
}
///The constructor of a Node
/*At the beginning a Node just needs a name, the m_modelMatrix will be set to the identity matrix*/
Node::Node(std::string nodeName)
{
	m_nodeName = nodeName;

	setIdentityMatrix_ModelMatrix();
}


Node::~Node()
{
}

///A getter for the name of a Node
/*Returns the name of the Node as const char*/
std::string Node::getNodeName()
{
	return m_nodeName;
}

///A Setter for the name of the Node
/*The m_nodeName will be set*/
void Node::setNodeName(std::string nodeName)
{
	m_nodeName = nodeName;
}

///A getter for the parent of the Node
/*Returns a Node Object which represent the Parent Node*/
Node* Node::getParentNode()
{
	return m_parentNode;
}

///A setter for the parent of the Node
/*The methods expect a node which will be used as m_parentNode*/
void Node::setParentNode(Node* parentNode)
{
	m_parentNode = parentNode;
}

///A add-Method for the list of children 
/*A NodeObject is given by the user and the node puts the new node into his m_childrenSet as a new children
The childrenNode m_parentNode will be set automatically*/
void Node::addChildrenNode(Node* node)
{

	m_childrenSet.push_back(node);
	node->setParentNode(this);
}

///A delete Method to delete a child
/*The user gives the method a name and the method iterates over the m_childrenSet and deletes the Child with the nodeName*/
void Node::deleteChildrenNode(std::string nodeName)
{
	for (int i = 0; i < m_childrenSet.size(); i++)
	{
		if (m_childrenSet.at(i)->getNodeName() == nodeName)
		{
			m_childrenSet.erase(m_childrenSet.begin()+i);
		}
	}
}

///A method to clear the whole set of children
/*Every Child Node in m_childrenNode will be deleted*/
void Node::clearChildrenSet()
{
	m_childrenSet.clear();
}

///A getter Method for a children Node
/*This Method iterates over the m_childrenSet and returns the Node with the nodeName*/
Node* Node::getChildrenNode(std::string nodeName)
{
	
	for (int i = 0; i < m_childrenSet.size(); i++)
	{
		if (m_childrenSet.at(i)->getNodeName() == nodeName)
		{
			return m_childrenSet.at(i);
		}
	}

	return NULL;
}

///A getter Method for the Modelmatrix
/*Returns the Modelmatrix of the current Node as a matrix*/
glm::mat4 Node::getModelMatrix()
{
	return m_modelMatrix;
}


///A Setter Method for the Modelmatrix
/*A complete mat4 Modelmatrix is given by the user and will be the m_modelMatrix of the Node*/
void Node::setModelMatrix(glm::mat4 modelMatrix)
{
	m_modelMatrix = modelMatrix;
}

///A rotation will be added to the Modelmatrix
/*The user tells the method how big the angle should be and around which axis we are rotation.
Then the method calls the rotate(...) Method of opengl and updates the modelmatrix*/
void Node::addRotation(float angle, glm::vec3 axis)
{
	glm::mat4 newRotationMatrix = glm::rotate(getRotationMatrix(), angle, axis);
	m_rotationMatrix = newRotationMatrix;

	updateModelMatrix(m_rotationMatrix);
}

///A getter for the rotationmatrix of the Node
/*Returns the Rotationmatrix m_rotationMatrix as a mat4*/
glm::mat4 Node::getRotationMatrix()
{
	return m_rotationMatrix;
}

///A translation will be added to the Modelmatrix
/*The user tells the method how far the object will move in x,y and z direction.
Then the method calls the translate(...) Method of opengl and updates the modelmatrix*/
void Node::addTranslation(float x, float y, float z)
{
	glm::vec3 transfer = glm::vec3(x, y, z);
	glm::mat4 newTranslationMatrix = glm::translate(getTranslationMatrix(), transfer);
	m_translateMatrix = newTranslationMatrix;

	updateModelMatrix(m_translateMatrix);
}

///A getter for the translationmatrix of the Node
/*Returns the Translationmatrix m_translateMatrix as a mat4*/
glm::mat4 Node::getTranslationMatrix()
{
	return m_translateMatrix;
}

///A scale will be added to the Modelmatrix
/*The user tells the method in which directions (x, y and/or z) the object should be scaled.
Then the method calls the scale(...) Method of opengl and updates the modelmatrix*/
void Node::addScale(float x, float y, float z)
{
	glm::vec3 scale = glm::vec3(x, y, z);
	glm::mat4 newScaleMatrix = glm::scale(getScaleMatrix(), scale);
	m_scaleMatrix = newScaleMatrix;

	updateModelMatrix(m_scaleMatrix);
}

///A Getter for the Scalematrix of the Node
/*Returns the Scalematrix m_scaleMatrix as a mat4*/
glm::mat4 Node::getScaleMatrix()
{
	return m_scaleMatrix;
}

///A method which updates the Modelmatrix
/*When a new rotation, scale or translation is added to the object, then the modelMatrix needs an update.
This update will be done by this method, the matrix which will be added to the modelMatrix is the updatedMatrix*/
void Node::updateModelMatrix(glm::mat4 updateMatrix)
{
	m_modelMatrix = updateMatrix * m_modelMatrix;
}

///The Translationmatrix will be set to the Identity matrix
/*The Translationsmatrix will be replaced and the Modelmatrix will be updated using the inverse of the actual m_translateMatrix*/
void Node::setIdentityMatrix_Translate()
{
	glm::mat4 inverseMatrix = glm::inverse(m_translateMatrix);
	m_modelMatrix = inverseMatrix * m_modelMatrix;
	m_translateMatrix = inverseMatrix * m_translateMatrix;
}

///The Scalematrix will be set to the Identity matrix
/*The Scalematrix will be replaced and the Modelmatrix will be updated using the inverse of the actual m_scaleMatrix*/
void Node::setIdentityMatrix_Scale()
{
	glm::mat4 inverseMatrix = glm::inverse(m_scaleMatrix);
	m_modelMatrix = inverseMatrix * m_modelMatrix;
	m_scaleMatrix = inverseMatrix * m_scaleMatrix;
}


///The Rotationmatrix will be set to the Identity matrix
/*The Rotationmatrix will be replaced and the Modelmatrix will be updated using the inverse of the actual m_rotateMatrix*/
void Node::setIdentityMatrix_Rotation()
{
	glm::mat4 inverseMatrix = glm::inverse(m_rotationMatrix);
	m_modelMatrix = inverseMatrix * m_modelMatrix;
	m_rotationMatrix = inverseMatrix * m_rotationMatrix;
}

///The Modelmatrix will be set to the Identity matrix
/*The Modelmatrix m_modelMatrix will be set to the identity matrix, all scales, rotations and translation will be lost*/
void Node::setIdentityMatrix_ModelMatrix()
{
	m_modelMatrix = glm::mat4(1);
}

///We link a Geometry to the node
/*A geometry Object will be linked with the node and will be saved as m_geometry*/
void Node::addGeometry(Geometry* geometry)
{
	m_geometry = geometry;
}

///A Getter for the Geometry of the Node
/*Returns m_geometry as a Geometry object*/
Geometry* Node::getGeometry()
{
	return m_geometry;
}
