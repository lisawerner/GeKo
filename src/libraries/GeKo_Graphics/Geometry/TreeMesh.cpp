#include "TreeMesh.h"



TreeMesh::TreeMesh() : Mesh((char*)RESOURCES_PATH "/Tree.ply"){

}

TreeMesh::~TreeMesh(void){
	/*for(int i = 0; i < meshEntries.size(); ++i){
		delete meshEntries.at(i);
	}
	meshEntries.clear();*/
}


