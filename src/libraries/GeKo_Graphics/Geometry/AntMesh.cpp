#include "AntMesh.h"



AntMesh::AntMesh() : Mesh((char*)RESOURCES_PATH "/Ant.ply"){
	//(char*)RESOURCES_PATH "/Flick34.obj"){

}

AntMesh::~AntMesh(void){
	/*for(int i = 0; i < meshEntries.size(); ++i){
		delete meshEntries.at(i);
	}
	meshEntries.clear();*/
}


