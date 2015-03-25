#include "GekoMesh.h"



GekoMesh::GekoMesh() : Mesh((char*)RESOURCES_PATH "/Geko.ply"){
	//(char*)RESOURCES_PATH "/Flick34.obj"){

}

GekoMesh::~GekoMesh(void){
	/*for(int i = 0; i < meshEntries.size(); ++i){
		delete meshEntries.at(i);
	}
	meshEntries.clear();*/
}


