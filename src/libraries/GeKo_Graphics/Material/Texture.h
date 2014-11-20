#pragma once

#include "Defs.h"

///This Class is to create Texture Objects by loading an image from the Ressources Folder

/*
To create a Texture use Texture(char* fileName). The file must be in the Ressources Folder.
*/

class Texture
{
public:
	Texture(char* fileName);	///The file must be in the Ressources folder
	Texture(GLuint texture);
	~Texture();

	bool load(char* fileName);
	void bind();

	void setTexture(GLuint texture);
	unsigned int getTexture();

private:
	void createTexture();

	unsigned int m_textureID;
	int m_width, m_heigth;

protected:

};