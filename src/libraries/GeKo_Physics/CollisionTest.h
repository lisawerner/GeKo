#pragma once
#include <vector>
#include <glm/ext.hpp>
#include <GeKo_Graphics/Scenegraph/Node.h>


/**The Collision Test class provides a test, if two objects, which are contained in Bounding Spheres, are colliding!*/

class CollisionTest : public Subject<Node, Collision_Event>
{

private:
    std::vector <Node*> objects;

public:
	CollisionTest();
    CollisionTest(std::vector <Node*> TestObjects);
	CollisionTest(Node* rootNode);
	~CollisionTest();

	///The Collision Test needs two objects in its BoundingSpheres
	/**The Radius will be accumulated of the two spheres. Then the distance of the center-Points will be calculated. If the accumulated 
	radius is bigger than the distance, the Spheres collide!*/
	bool collides(BoundingSphere* object1, BoundingSphere* object2);

	///The Collision Test needs two objects in its BoundingSpheres
	/**/
	//bool collides(BoundingBox* object1, BoundingBox* object2);

	//bool collides(Node* object1, Node* object2);
	
	///Checks the collision of all objects per frame
	/***/
	void update();

	///Add an Object to the list 
	/**/
	void addNode(Node* nodeObject);

	///Collects all Nodes of the scenegraph
	/**Should be used before the render Loop but can be updated every frame too*/
	void collectNodes(Node* root);
};	