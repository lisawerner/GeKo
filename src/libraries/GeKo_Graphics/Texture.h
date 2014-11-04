#pragma once

#include "Defs.h"

/*
TODO: Information
*/

class Texture
{
public:
	Texture(char* Filename);
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