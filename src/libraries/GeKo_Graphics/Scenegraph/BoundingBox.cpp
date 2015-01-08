#include "BoundingBox.h"

BoundingBox::BoundingBox(Node* object){
	for (int i = 0; i < object->getGeometry()->getVertices().size(); i++){
		vertices.push_back(glm::vec4(object->getGeometry()->getVertices().at(i).x, object->getGeometry()->getVertices().at(i).y, object->getGeometry()->getVertices().at(i).z, 1.0));
	}
}

BoundingBox::~BoundingBox(){
    vertices.clear();
}

std::vector<glm::vec4> BoundingBox::boundingBox(Node* object){
	float maxX = object->getGeometry()->getVertices().at(0).x;
	float minX = object->getGeometry()->getVertices().at(0).x;
	
	float maxY = object->getGeometry()->getVertices().at(0).y;
	float minY = object->getGeometry()->getVertices().at(0).y;

	float maxZ = object->getGeometry()->getVertices().at(0).z;
	float minZ = object->getGeometry()->getVertices().at(0).z;
	
	for(int i = 1; i < vertices.size(); i++){
		if (object->getGeometry()->getVertices().at(i).x > maxX){
			maxX = object->getGeometry()->getVertices().at(i).x;
		}
		if (object->getGeometry()->getVertices().at(i).y > maxY){
			maxY = object->getGeometry()->getVertices().at(i).y;
		}
		if (object->getGeometry()->getVertices().at(i).z > maxZ){
			maxZ = object->getGeometry()->getVertices().at(i).z;
		}
		
		if (object->getGeometry()->getVertices().at(i).x < minX){
			minX = object->getGeometry()->getVertices().at(i).x;
		}
		if (object->getGeometry()->getVertices().at(i).y < minY){
			minY = object->getGeometry()->getVertices().at(i).y;
		}
		if (object->getGeometry()->getVertices().at(i).z < minZ){
			minZ = object->getGeometry()->getVertices().at(i).z;
		}
	}
	
	std::vector<glm::vec4> box;
	box.clear();
	
	//mir ist grad die Reihenfolge der Punkte nicht klar... entlang der negativen z-Achse?
	box.push_back(glm::vec4(minX, minY, maxZ, 1.0));
	box.push_back(glm::vec4(maxX, minY, maxZ, 1.0));
	box.push_back(glm::vec4(maxX, minY, minZ, 1.0));
	box.push_back(glm::vec4(minX, minY, minZ, 1.0));
	box.push_back(glm::vec4(minX, maxY, maxZ, 1.0));
	box.push_back(glm::vec4(maxX, maxY, maxZ, 1.0));
	box.push_back(glm::vec4(maxX, maxY, minZ, 1.0));
	box.push_back(glm::vec4(minX, maxY, minZ, 1.0));
	
	return box;
	
}

//dann müssen noch schnitttests gemacht werden bzgl. der Hierarchie. Allerdings muss diese mit dem Szenegraph geregelt werden ... ?

