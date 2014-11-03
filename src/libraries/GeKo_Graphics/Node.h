#pragma once
#include <vector>
#include <glm/ext.hpp>
#include <iostream>
#include <GeKo_Graphics\Geometry.h>
#include <GeKo_Graphics\Rect.h>

/*A "Node" should be a container for Geometry, Material, Lights and Cameras and provides all the information a shader could need
  like a Modelmatrix for example. It has one parent and can have a lot of children or none. Every Node exists as long as the scenegraph */
class Node
{
public:
	Node();
	Node(std::string nodeName);
	~Node();

	std::string getNodeName();

	void setNodeName(std::string nodeName);

	Node* getParentNode();

	void setParentNode(Node* parentNode);

	void addChildrenNode(Node* childrenNode);
	
	void deleteChildrenNode(std::string nodeName);

	void clearChildrenSet();

	Node* getChildrenNode(std::string nodeName);

	glm::mat4 getModelMatrix();

	void setModelMatrix(glm::mat4);

	void addRotation(float angle, glm::vec3 axis);

	glm::mat4 getRotationMatrix();

	void addTranslation(float x, float y, float z);

	glm::mat4 getTranslationMatrix();

	void addScale(float x, float y, float z);
	
	glm::mat4 getScaleMatrix();

	//TODO: Weiß nicht, ob das inverse für die skalierung und die Rotationsmatrix richtig sind
	//TODO: In CG1 gab es da eigene Inverse Matrizen für Rotation und Skalierung
	//TODO: Wäre auszuprobieren und eventuell anzupassen
	void setIdentityMatrix_Translate();

	void setIdentityMatrix_Scale();

	void setIdentityMatrix_Rotation();
	
	void setIdentityMatrix_ModelMatrix();

	void addGeometry(Geometry* geometry);

	Geometry* getGeometry();

	//TODO: Folgende methoden müssten noch hinzugefügt werdenlaut UML-Diagramm (werde ich teilweise am Dienstag zwischen 12 und 18 Uhr dann machen, muss morgen früh raus!)
	/*
	void addCamera(Camera* camera);
	void addLight(Light* light);
	void setMaterial(Material* material);
	*/

protected:
	std::string m_nodeName;
	Node* m_parentNode;
	std::vector<Node*> m_childrenSet;

	glm::mat4 m_modelMatrix;
	
	glm::mat4 m_rotationMatrix;
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_translateMatrix;

	Geometry* m_geometry;

private:
	void updateModelMatrix(glm::mat4 updateMatrix);

};

