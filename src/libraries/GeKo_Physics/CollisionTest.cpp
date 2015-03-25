#include <Geko_Physics/CollisionTest.h>

CollisionTest::CollisionTest()
{

}
CollisionTest::CollisionTest(std::vector <Node*> TestObjects){
    objects.clear();
	for(int i = 0; i < TestObjects.size(); i++){
	    objects.push_back(TestObjects.at(i));
	}
}

CollisionTest::CollisionTest(Node* rootNode)
{
	collectNodes(rootNode);
}

CollisionTest::~CollisionTest(){
    objects.clear();
}

bool CollisionTest::collides(BoundingSphere* sphere1, BoundingSphere* sphere2)
{
	//std::cout << "COLLISION TEST WILL BE STARTED! " << std::endl;
	double testRadius = sphere1->radius + sphere2->radius;
	//std::cout << "TESTRADIUS : " << testRadius << std::endl;
	//std::cout << "CENTER OF SPHERE 1 : " << sphere1->center.x << " CENTER OF SPHERE 2: " << sphere2->center.x << std::endl;
	glm::vec3 space = glm::vec3(sphere1->center.x - sphere2->center.x, sphere1->center.y - sphere2->center.y, sphere1->center.z - sphere2->center.z);
	float distance = glm::length(space);
	//std::cout << "DISTANCE : " << distance << std::endl;

	if (testRadius >= distance){
		return true;
	}
	else {

		return false;
	}
}


void CollisionTest::update()
{
	//Falls es nur ein Objekt in der Szene gäbe, wird jegliche Kollision auf "false" gesetzt
	//Kann später wieder raus, denn jede Szene besteht mindestens aus einem Terrain und einem Objekt (?)
	if (objects.size() == 1)
	{
		objects.at(0)->getBoundingSphere()->setCollisionDetected(false);
	}
	else
	{
		//Wir überprüfen jedes Objekt i mit allen Objekten aus dem Szenegraph
		for (int i = 0; i < objects.size(); i++)
		{
			bool collisionDetected = false;

			for (int j = 0; j < objects.size(); j++)
			{
				//Falls es sich um das gleiche Objekt handelt, wollen wir nicht testen
				if (i == j){ }
				//Wenn das Terrain, also unsere Plane, getestet werden soll, überspringen wir den Schritt
				else if (objects.at(i)->getNodeName() == "Plane"){  }
				//Falls es sich nicht um das gleiche Objekt handelt...
				else if(true){
					for (int k = 0; k < objects.at(i)->getBoundingList()->size(); k++)
					{
						bool collisionBefore = objects.at(i)->getBoundingList()->at(k)->getCollisionDetected();
						bool collisionAfter = collides(objects.at(i)->getBoundingList()->at(k), objects.at(j)->getBoundingSphere());

						//Wenn das Objekt noch nicht kollidiert ist und jetzt kollidiert, erkennen wir ein Event
						//==TODO: Sollten diese Abfragen vielleicht in den Observer? Ja, Nein, Vielleicht?==//
						if ((!collisionBefore | collisionBefore) & collisionAfter)
						{
							//Wir schauen uns an, mit welchem Objekt das aktuelle Objekt kollidiert
							//Handelt es sich um das Terrain, hier als Plane bezeichnet, dann wird ein anderes Event ausgerufen
							if (objects.at(j)->getNodeName() == "Plane")
							{
								notify(*objects.at(i), Collision_Event::PLANE_COLLISION);
							}
							//Bei der Kollision handelt es sich nicht um die Plane, dann...
							//...Schauen wir ob Flick mit dem Player kollidiert
							//==TODO: Muss verallgemeinert werden zu: KI kollidiert mit Spieler==//
							/*else if (objects.at(i)->getNodeName() == "Flick" & objects.at(j)->getNodeName() == "Player")
							{
								notify(*objects.at(i), *objects.at(j), Collision_Event::COLLISION_KI_PLAYER);
								notify(*objects.at(i), *objects.at(j), Collision_Event::COLLISION_AI_FIGHT_PLAYER);
							}*/
							else if (objects.at(i)->getType() == ClassType::AI & objects.at(j)->getType() == ClassType::PLAYER)
							{
								//HIERRRRRRRRRRRRRRRRRR
								notify(*objects.at(i), *objects.at(j), Collision_Event::COLLISION_KI_PLAYER);
								notify(*objects.at(i), *objects.at(j), Collision_Event::COLLISION_AI_FIGHT_PLAYER);
							}

							else if (objects.at(i)->getType() == ClassType::AI & objects.at(j)->getType() == ClassType::STATIC)
							{
								notify(*objects.at(i), *objects.at(j), Collision_Event::AI_STATIC_COLLISION);
							}
							else if (objects.at(i)->getType() == ClassType::PLAYER & objects.at(j)->getType() == ClassType::STATIC)
							{
								notify(*objects.at(i), *objects.at(j), Collision_Event::PLAYER_STATIC_COLLISION);
							}

							//Wenn es sich um den Spieler handelt, der mit der KI kollidiert, wird ihm dies mitgeteilt
							//== TODO: Hier sollte ein spezielles Event später eingebaut werden, er merkt erstmal nur, dass es eine Kollision gab! ==//
							else if (objects.at(i)->getType() == ClassType::PLAYER & objects.at(j)->getType() == ClassType::AI)
							{
								notify(*objects.at(i), Collision_Event::COLLISION_DETECTED);
							}

							collisionDetected = true;
						}

						//Wenn das Objekt noch nicht kollidiert ist und immer noch nicht kollidiert, passiert nichts, denn es hat sich nichts geändert
						else if (!collisionBefore & !collisionAfter)
						{

						}

						//Das Objekt wusste schon, dass es kollidiert und kollidiert immer noch, es ändert sich also  nichts
						//==Ist Überflüssig, da durch 1. Falll schon abgehandelt! ==//
						else if (collisionBefore & collisionAfter)
						{
							//==Unschöne Variante ==//
							if (objects.at(j)->getNodeName() == "Plane")
							{
								notify(*objects.at(i), Collision_Event::PLANE_COLLISION);
							}
							collisionDetected = true;
						}

						//Das Objekt kollidierte mit einem Objekt, aber es ist bis jetzt noch keine erneute Kollision festgestellt worden
						else if (collisionBefore & !collisionAfter & !collisionDetected)
						{

							if (objects.at(i)->getType() == ClassType::AI & objects.at(j)->getType() == ClassType::PLAYER)
							{
								notify(*objects.at(i), Collision_Event::NO_COLLISION_KI_PLAYER);
							}
							else if (true)
							{
								notify(*objects.at(i), Collision_Event::NO_COLLISION_DETECTED);
							}
						}


					}
			

				}
			}
		}
	}
}

void CollisionTest::addNode(Node* nodeObject)
{
	objects.push_back(nodeObject);
}

void CollisionTest::collectNodes(Node* root)
{
	for (int i = 0; i < root->getChildrenSet()->size(); i++)
	{
		addNode(root->getChildrenSet()->at(i));
		collectNodes(root->getChildrenSet()->at(i));
	}
}