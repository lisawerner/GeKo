#pragma once
#include "GeKo_Graphics/ParticleSystem/Emitter.h"
#include "tinyxml2.h"

/*
Compilation of different Emitters.
*/
class Effect{
public:
	Effect();
	Effect(std::string name);
	Effect(const char* filepath);	//TODO: gets an effect file
	~Effect();

	/*void active();*/

	void addEmitter(Emitter* emitter);
	void removeEmitter(int arrayPosition);

	void changePosition(glm::vec3 newPosition);	//updates the positions of every Emitter
	void updateEmitters();	//compute Shader
	void renderEmitters(Camera &cam);	//render Shader

	int loadEffect(const char* filepath);	//TODO: change the currently loaded effect
	int saveEffect(char* filepath);		//TODO: save the settings of this effect to a file (XML?)

	void setName(std::string name);
	std::string getName();

protected:
	std::vector<Emitter*> emitterVec;	//contains all Emitters of the Effect
	std::string effectName;		//name of the effect file

	//check for Error
	#ifndef XMLCheckResult
	#define XMLCheckResult(result) if (result != XML_SUCCESS) { printf("Error: %i\n", result); return result; }
	#endif
};