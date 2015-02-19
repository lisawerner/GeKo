#include "Node.h"

Node::Node()
{
	m_nodeName = "Default";
	setIdentityMatrix_ModelMatrix();
	
	m_hasTexture = false;
  m_hasNormalMap = false;
  m_hasHeightMap = false;
	m_hasCamera = false;
	m_hasGeometry = false;
}

Node::Node(std::string nodeName)
{
	m_nodeName = nodeName;
	setIdentityMatrix_ModelMatrix();
	m_hasTexture = false;
  m_hasNormalMap = false;
  m_hasHeightMap = false;
	m_hasCamera = false;
	m_hasGeometry = false;
}


Node::~Node()
{
}

std::string Node::getNodeName()
{
	return m_nodeName;
}

void Node::setNodeName(std::string nodeName)
{
	m_nodeName = nodeName;
}


Node* Node::getParentNode()
{
	return m_parentNode;
}

void Node::setParentNode(Node* parentNode)
{
	m_parentNode = parentNode;
}

Node* Node::getChildrenNode(std::string nodeName)
{

	for (int i = 0; i < m_childrenSet.size(); i++)
	{
		if (m_childrenSet.at(i)->getNodeName() == nodeName)
		{
			return m_childrenSet.at(i);
		}
	}
	std::cout << "ERROR: The Node with the name " << nodeName << " does not exist!" << std::endl;
	return NULL;
}

void Node::addChildrenNode(Node* node)
{
	m_childrenSet.push_back(node);
	getChildrenNode(node->getNodeName())->setParentNode(this);
}

void Node::deleteChildrenNode(std::string nodeName)
{
	for (int i = 0; i < m_childrenSet.size(); i++)
	{
		if (m_childrenSet.at(i)->getNodeName() == nodeName)
		{
			m_childrenSet.erase(m_childrenSet.begin()+i);
			std::cout << "SUCESS: The Node with the name " << nodeName << " was deleted!" << std::endl;
		}
	}
}


void Node::clearChildrenSet()
{
	m_childrenSet.clear();
}


Geometry* Node::getGeometry()
{
	return m_geometry;
}

void Node::addGeometry(Geometry* geometry)
{
	m_geometry = geometry;
	m_hasGeometry = true;
	if (!m_geometry->isLoaded())
	{
		m_geometry->loadBufferData();
		m_geometry->setLoaded();
	}
}

Texture* Node::getTexture()
{
	return m_texture;
}

void Node::addTexture(Texture* texture)
{
	m_texture = texture;
	m_hasTexture = true;
}

Texture* Node::getNormalMap()
{
	return m_normalmap;
}

void Node::addNormalMap(Texture* normalmap)
{
	m_normalmap = normalmap;
	m_hasNormalMap = true;
}

Texture* Node::getHeightMap()
{
  return m_heightmap;
}

void Node::addHeightMap(Texture* heightmap)
{
  m_heightmap = heightmap;
  m_hasHeightMap = true;
}

Camera* Node::getCamera()
{
	return m_camera;
}

void Node::setCamera(Camera* camera)
{
	m_camera = camera;
	m_hasCamera = true;
}


glm::mat4 Node::getModelMatrix()
{
	return m_modelMatrix;
}

void Node::setModelMatrix(glm::mat4 modelMatrix)
{
	m_modelMatrix = modelMatrix;
}

glm::mat4 Node::getRotationMatrix()
{
	return m_rotationMatrix;
}

void Node::addRotation(float angle, glm::vec3 axis)
{
	glm::mat4 newRotationMatrix = glm::rotate(getRotationMatrix(), angle, axis);
	m_rotationMatrix = newRotationMatrix;

	updateModelMatrix(m_rotationMatrix);
}

glm::mat4 Node::getTranslationMatrix()
{
	return m_translateMatrix;
}

void Node::addTranslation(float x, float y, float z)
{
	glm::vec3 transfer = glm::vec3(x, y, z);
	glm::mat4 newTranslationMatrix = glm::translate(getTranslationMatrix(), transfer);
	m_translateMatrix = newTranslationMatrix;

	updateModelMatrix(m_translateMatrix);
}


glm::mat4 Node::getScaleMatrix()
{
	return m_scaleMatrix;
}

void Node::addScale(float x, float y, float z)
{
	glm::vec3 scale = glm::vec3(x, y, z);
	glm::mat4 newScaleMatrix = glm::scale(getScaleMatrix(), scale);
	m_scaleMatrix = newScaleMatrix;

	updateModelMatrix(m_scaleMatrix);
}


void Node::setIdentityMatrix_Translate()
{
	glm::mat4 inverseMatrix = glm::inverse(m_translateMatrix);
	m_modelMatrix = inverseMatrix * m_modelMatrix;
	m_translateMatrix = inverseMatrix * m_translateMatrix;
}

void Node::setIdentityMatrix_Scale()
{
	glm::mat4 inverseMatrix = glm::inverse(m_scaleMatrix);
	m_modelMatrix = inverseMatrix * m_modelMatrix;
	m_scaleMatrix = inverseMatrix * m_scaleMatrix;
}

void Node::setIdentityMatrix_Rotation()
{
	glm::mat4 inverseMatrix = glm::inverse(m_rotationMatrix);
	m_modelMatrix = inverseMatrix * m_modelMatrix;
	m_rotationMatrix = inverseMatrix * m_rotationMatrix;
}

void Node::setIdentityMatrix_ModelMatrix()
{
	m_modelMatrix = glm::mat4(1);
}

void Node::render()
{
  if (hasGeometry())
  {
    m_geometry->renderGeometry();
  }

  for (int i = 0; i < m_childrenSet.size(); i++)
  {
    m_childrenSet.at(i)->render();
  }
}

void Node::render(ShaderProgram &shader)
{
	if (!(m_nodeName == "Root"))
	{

		glm::mat4 modelMatrix = getParentNode()->getModelMatrix() * m_modelMatrix;
		shader.sendMat4("modelMatrix", modelMatrix);
	}

	if (m_hasTexture)
	{
		shader.sendSampler2D("testTexture", getTexture()->getTexture(),0);
    shader.sendInt("useTexture", 1);
  }
  else
    shader.sendInt("useTexture", 0);

  if (m_hasNormalMap)
  {
    shader.sendSampler2D("normalMap", getNormalMap()->getTexture(),1);
    shader.sendInt("useNormalMap", 1);
  }

  else
    shader.sendInt("useNormalMap", 0);

  if (m_hasHeightMap)
  {
    shader.sendSampler2D("heightMap", getHeightMap()->getTexture(), 2);
    shader.sendInt("useHeightMap", 1);
    shader.sendFloat("parallaxScale", 0.07f);
    shader.sendFloat("parallaxBias", 0.1f);
  }
  
  else
    shader.sendInt("useHeightMap", 0);

	if (hasGeometry())
	{
		m_geometry->renderGeometry();
	}

	for (int i = 0; i < m_childrenSet.size(); i++)
	{
		m_childrenSet.at(i)->render(shader);
	}

}

void Node::updateModelMatrix(glm::mat4 updateMatrix)
{
	m_modelMatrix = updateMatrix * m_modelMatrix;
}

glm::mat4 Node::updateModelMatrix()
{
	glm::mat4 modelMatrix = getParentNode()->getModelMatrix() * m_modelMatrix;
	//TODO: An dieser Stelle sollte die Matrix an den Shader gesendet werden als Uniform-Variable
	return modelMatrix;
}

std::vector<Node*>* Node::getChildrenSet()
{
	return &m_childrenSet;
}

bool Node::hasTexture()
{
	return m_hasTexture;
}

bool Node::hasNormalMap()
{
	return m_hasNormalMap;
}

bool Node::hasCamera()
{
	return m_hasCamera;
}

bool Node::hasGeometry()
{
	return m_hasGeometry;
}