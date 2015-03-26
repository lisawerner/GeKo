#include "CubeMesh.h"



CubeMesh::CubeMesh() : Mesh((char*)RESOURCES_PATH "/Cube.obj"){
	//(char*)RESOURCES_PATH "/Flick34.obj"){

}

CubeMesh::~CubeMesh(void){
	/*for(int i = 0; i < meshEntries.size(); ++i){
	delete meshEntries.at(i);
	}
	meshEntries.clear();*/
}


