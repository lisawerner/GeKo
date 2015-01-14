#pragma once
#include <vector>
#include <glm/ext.hpp>
#include <GeKo_Graphics/Scenegraph/Node.h>

/** The Bounding Box class provides a cube-like box, which contains an Object completely*/
class BoundingBox {

public:
	///Each Bounding Box needs a Object to wrap
	/**/
	BoundingBox(Node* object);
	~BoundingBox();

	///Returns all points of the Box
	/**/
	std::vector<glm::vec4> boundingBox(Node* object);

private:
    std::vector<glm::vec4> vertices;




};