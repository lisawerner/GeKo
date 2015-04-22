#pragma once
#include "GeKo_Graphics/ParticleSystem/Emitter.h"
#include "tinyxml2.h"

/*
Compilation of different Emitters.
*/
class Effect{
public:
	Effect();
	Effect(const char* filepath);
	~Effect();

	/*void active();*/

	void addEmitter(Emitter* emitter);
	void removeEmitter(int arrayPosition);

	void updateEmitters(Camera &cam);	//compute Shader
	void renderEmitters(Camera &cam);	//render Shader

	int loadEffect(const char* filepath);	//TODO: change the currently loaded effect
	int saveEffect(char* filepath);		//TODO: save the settings of this effect to a file (XML?)

	void setPosition(glm::vec3 newPosition);	//updates the positions of every Emitter

private:
	std::vector<Emitter*> emitterVec;	//contains all Emitters of the Effect

	//check for XML Error
	int XMLCheckResult(int result);
};