#include "GeKo_Demo/Demo.h"


Demo::Demo(){

}

Demo::~Demo(){}

void Demo::setScene(Scene* s){
	m_demoScene = s;
}

void Demo::addDemoForests(){
	//===================================================================//
	//==================Object declarations - Geometry, Texture, Node=== //
	//==========================Object: Tree===========================//
	TreeMesh tree;

	//Tree Positions
	glm::vec3 trees[5] = { glm::vec3(16.0, 0.0, 76.0), glm::vec3(23.0, 0.0, 74.0), glm::vec3(21.5, 0.0, 78.5), glm::vec3(15.0, 0.0, 81.5), glm::vec3(27.5, 0.0, 88.5), };

	StaticObject treeStatic;
	treeStatic.setTree();
	Node treeNode("Tree");
	treeNode.addGeometry(&tree);
	treeNode.setObject(&treeStatic);
	treeNode.addTranslation(trees[0]);
	treeNode.getBoundingSphere()->radius = 3.0;

	StaticObject treeStatic2;
	treeStatic2.setTree();
	Node treeNode2("Tree2");
	treeNode2.addGeometry(&tree);
	treeNode2.setObject(&treeStatic2);
	treeNode2.addTranslation(trees[1]);
	treeNode2.getBoundingSphere()->radius = 3.0;

	StaticObject treeStatic3;
	treeStatic3.setTree();
	Node treeNode3("Tree3");
	treeNode3.addGeometry(&tree);
	treeNode3.setObject(&treeStatic3);
	treeNode3.addTranslation(trees[2]);
	treeNode3.getBoundingSphere()->radius = 3.0;

	StaticObject treeStatic4;
	treeStatic4.setTree();
	Node treeNode4("Tree4");
	treeNode4.addGeometry(&tree);
	treeNode4.setObject(&treeStatic4);
	treeNode4.addTranslation(trees[3]);
	treeNode4.getBoundingSphere()->radius = 3.0;

	StaticObject treeStatic5;
	treeStatic5.setTree();
	Node treeNode5("Tree5");
	treeNode5.addGeometry(&tree);
	treeNode5.setObject(&treeStatic5);
	treeNode5.addTranslation(trees[4]);
	treeNode5.getBoundingSphere()->radius = 3.0;

	//treeStatic.getInventory()->addItem(&cookie, 25);
	//treeStatic.getInventory()->addItem(&branch, 10);
}