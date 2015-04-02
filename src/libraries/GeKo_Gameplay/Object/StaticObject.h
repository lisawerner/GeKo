#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Object.h"

class StaticObject : public Object
{
public: 
	//Eine Position: Objekt startet zu Hause! (Weiterer Konstrutkor, falls Objekt woanders starten soll)
	StaticObject();
	~StaticObject();

	void setTree();
	void setExampleAntHome();

protected:
	
};