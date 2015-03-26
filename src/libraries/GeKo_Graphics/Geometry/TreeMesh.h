#pragma once

//#include <GeKo_Graphics/Object/Geometry.h>
#include <GeKo_Graphics/Geometry/Mesh.h>
//#include <assimp\scene.h>
//#include <assimp\mesh.h>
//#include <assimp/Importer.hpp>
//#include <assimp/postprocess.h>
//#include <iostream>


///This is the class for importing static meshes via Assimp.
/**As imported meshes can consist of more than one model, this class has a vector named MeshEntry, where all the separate
 * meshes can be found.
 * To use the class you have to generate a new mesh via Mesh *name = new Mesh("dataname.format");
 * In the gameloop it is enough to use name->render(); as binding the buffers happens in the constructor for each MeshEntry.
 *
 **/
class TreeMesh : public Mesh {


public:
		/**
		*	Mesh constructor, loads the specified filename if supported by Assimp
		**/
		TreeMesh();

		/**
		*	Clears all loaded MeshEntries
		**/
		~TreeMesh();



};
