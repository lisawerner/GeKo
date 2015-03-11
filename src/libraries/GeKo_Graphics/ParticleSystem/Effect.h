#pragma once
#include "GeKo_Graphics/ParticleSystem/Emitter.h"

/*
Compilation of different Emitters.
*/
class Effect{
public:
	Effect();
	Effect(std::string name);
	Effect(const std::string &filepath);	//TODO: gets an effect file
	~Effect();

	void active();

	void addEmitter(Emitter emitter);
	void removeEmitter(int arrayPosition);

	void changePosition(glm::vec3 newPosition);	//updates the positions of every Emitter
	void updateEmitters();	//compute Shader
	void renderEmitters(Camera &cam);	//render Shader

	void loadEffect(const std::string &filepath);	//TODO: change the currently loaded effect
	void storeEffect(std::string &filepath);		//TODO: save the settings of this effect to a file (XML?)

	void setName(std::string name);
	std::string getName();

private:
	std::vector<Emitter> emitterVec;	//contains all Emitters of the Effect
	std::string effectName;		//name of the effect file
};