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
	Effect(const char* filepath);
	~Effect();

	/*void active();*/

	void addEmitter(Emitter* emitter);
	void removeEmitter(int arrayPosition);

	void updateEmitters(glm::vec3 playerPosition = glm::vec3(0.0, 0.0, 0.0));	//compute Shader
	void renderEmitters(Camera &cam);	//render Shader

	int loadEffect(const char* filepath);	//TODO: change the currently loaded effect
	int saveEffect(char* filepath);		//TODO: save the settings of this effect to a file (XML?)

	void setPosition(glm::vec3 newPosition);	//updates the positions of every Emitter
	void setName(std::string name);
	std::string getName();

private:
	std::vector<Emitter*> emitterVec;	//contains all Emitters of the Effect
	std::string effectName;		//name of the effect file

	//check for Error
	#ifndef XMLCheckResult
	#define XMLCheckResult(result) if (result != XML_SUCCESS) { printf("Error: %i\n", result); return result; }
	#endif
};