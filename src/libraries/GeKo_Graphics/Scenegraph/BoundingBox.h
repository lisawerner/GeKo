#pragma once
#include <vector>
#include <glm/ext.hpp>
#include <GeKo_Graphics/Scenegraph/Node.h>


class BoundingBox {

private:
    std::vector<glm::vec4> vertices;

public:
    BoundingBox(Node* object);
	~BoundingBox();
	
	std::vector<glm::vec4> boundingBox(Node* object);


};