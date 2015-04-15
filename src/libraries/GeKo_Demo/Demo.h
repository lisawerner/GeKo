#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

//Scenegraph
#include <GeKo_Graphics/Scenegraph/Scene.h>

//Geometry and Texture Includes
#include <GeKo_Graphics/Geometry/TreeMesh.h>
#include <GeKo_Graphics/Material/Texture.h>

class Demo
{
public: 
	Demo();
	~Demo();

	void setScene(Scene* s);

	void addDemoForests();

protected:
	Scene* m_demoScene;

};