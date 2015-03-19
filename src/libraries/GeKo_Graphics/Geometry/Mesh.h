#pragma once
#include <GeKo_Graphics/Object/Geometry.h>

#include <iostream>

///This is the class for importing static meshes via Assimp.
/**As imported meshes can consist of more than one model, this class has a vector named MeshEntry, where all the separate
 * meshes can be found.
 * To use the class you have to generate a new mesh via Mesh *name = new Mesh("dataname.format");
 * In the gameloop it is enough to use name->render(); as binding the buffers happens in the constructor for each MeshEntry.
 *
 **/
class aiMesh;

class Mesh : public Geometry {


public:
		/**
		*	Mesh constructor, loads the specified filename if supported by Assimp
		**/
		//Mesh(const char *filename);
		Mesh(const char *filename);

		/**
		*	Clears all loaded MeshEntries
		**/
		~Mesh();

		///This method loads all the data of the meshes into the Geometry class
		/**/
		void initializeData();

protected:
	std::vector<aiMesh*> meshEntries;
};
