#include <GeKo_Graphics/Scenegraph/BoundingSphere.h>

BoundingSphere::BoundingSphere(Geometry* object, glm::mat4 modelMatrix){
  
	//Mittelpunkt der Box entspricht dem Mittelpunkt der Kugel
	// m_maxX = object->getVertices().at(0).x;
	// m_minX = object->getVertices().at(0).x;

	// m_maxY = object->getVertices().at(0).y;
	// m_minY = object->getVertices().at(0).y;

	// m_maxZ = object->getVertices().at(0).z;
	// m_minZ = object->getVertices().at(0).z;

	//for (int i = 1; i < object->getVertices().size(); i++){
	//	if (object->getVertices().at(i).x > m_maxX){
	//		m_maxX = object->getVertices().at(i).x;
	//	}
	//	if (object->getVertices().at(i).y > m_maxY){
	//		m_maxY = object->getVertices().at(i).y;
	//	}
	//	if (object->getVertices().at(i).z > m_maxZ){
	//		m_maxZ = object->getVertices().at(i).z;
	//	}

	//	if (object->getVertices().at(i).x < m_minX){
	//		m_minX = object->getVertices().at(i).x;
	//	}
	//	if (object->getVertices().at(i).y < m_minY){
	//		m_minY = object->getVertices().at(i).y;
	//	}
	//	if (object->getVertices().at(i).z < m_minZ){
	//		m_minZ = object->getVertices().at(i).z;
	//	}
	//}
	//
	//


	//center = glm::vec3(modelMatrix* glm::vec4((m_maxX + m_minX) / 2, (m_maxY + m_minY) / 2, (m_maxZ + m_minZ) / 2, 1.0));
	//originalCenter = center;
	//
	////Radius bestimmen
	//glm::vec4 diagonal = modelMatrix * glm::vec4(m_maxX - m_minX, m_maxY - m_minY, m_maxZ - m_minZ, 1.0);
	//radius = float(glm::length(diagonal) / 2);

	//setCollisionDetected(false);

	//std::cout << " RADIUS = " << radius << std::endl;
	//std::cout << " CENTER = " << center.x << "; " << center.y << "; " << center.z << std::endl;

	m_collisionDetected = false;
	createSphere(object, modelMatrix);
		
}

BoundingSphere::BoundingSphere(double rad, glm::vec3 cent)
{
	radius = rad;
	center = cent;
	originalCenter = cent;
}

BoundingSphere::~BoundingSphere(){
   
}

void BoundingSphere::update(glm::mat4 modelMatrix)
{
	//center = modelMatrix * glm::vec4((m_maxX + m_minX) / 2, (m_maxY + m_minY) / 2, (m_maxZ + m_minZ) / 2, 1.0);
	center = glm::vec3(modelMatrix * glm::vec4(originalCenter, 1.0));
}


void BoundingSphere::setCollisionDetected(bool collision)
{
	m_collisionDetected = collision;

}
bool BoundingSphere::getCollisionDetected()
{
	return m_collisionDetected;
}

void BoundingSphere::createSphere(Geometry* object, glm::mat4 modelMatrix)
{
	std::vector<glm::vec4> vs = object->getVertices();

	int i, n;
	float dx, dy, dz, le;
	glm::vec4 lev(1.0);

	n = vs.size();

	center = glm::vec3(0.0);

	for (int i = 0; i < n - 1; i++)
	{
		center.x = center.x + vs.at(i).x;
		center.y = center.y + vs.at(i).y;
		center.z = center.z + vs.at(i).z;

		center.x = center.x / n;
		center.y = center.y / n;
		center.z = center.z / n;
	}

	radius = 0;

	for (int i = 0; i < n - 1; i++)
	{
		dx = vs.at(i).x - center.x;
		dy = vs.at(i).y - center.y;
		dz = vs.at(i).z - center.z;

		lev.x = dx;
		lev.y = dy;
		lev.z = dz;
		lev = modelMatrix * lev;

		if (radius < glm::length(lev))
		{
			radius = glm::length(lev);
		}


	}

	originalCenter = center;
	center = glm::vec3(modelMatrix * glm::vec4(center, 1.0));
}