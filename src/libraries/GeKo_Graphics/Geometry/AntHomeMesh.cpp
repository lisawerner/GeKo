#include "AntHomeMesh.h"



AntHomeMesh::AntHomeMesh() : Mesh((char*)RESOURCES_PATH "/AntHome.ply"){

}

AntHomeMesh::~AntHomeMesh(void){
	/*for(int i = 0; i < meshEntries.size(); ++i){
		delete meshEntries.at(i);
	}
	meshEntries.clear();*/
}


