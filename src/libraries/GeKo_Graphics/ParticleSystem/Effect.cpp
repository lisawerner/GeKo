#include "Effect.h"

Effect::Effect()
{
	setName("unnamedEffect");
}

Effect::Effect(std::string name)
{
	setName(name);
}

Effect::Effect(const std::string &filepath)
{
	//TODO
}

Effect::~Effect()
{
	//TODO
	emitterVec.~vector();
}


void Effect::active()
{
	for (auto iterator = emitterVec.begin(); iterator < emitterVec.end(); iterator++){
		iterator->startTime();
	}
}

void Effect::addEmitter(Emitter emitter)
{
	emitterVec.push_back(emitter);
}

void Effect::removeEmitter(int arrayPosition)
{
	emitterVec.erase(emitterVec.begin() + arrayPosition);
}

void Effect::changePosition(glm::vec3 newPosition)
{
	for (auto emitter : emitterVec){
		emitter.setPosition(newPosition);
	}
}

void Effect::updateEmitters()
{
	for (auto iterator = emitterVec.begin(); iterator < emitterVec.end(); iterator++){
		iterator->generateParticle();
		iterator->update();
	}
}

void Effect::renderEmitters(Camera &cam)
{
	for (auto emitter : emitterVec){
		emitter.render(cam);
	}
}


void Effect::loadEffect(const std::string &filepath)
{
	//TODO
}

void Effect::storeEffect(std::string &filepath)
{
	//TODO
}


void Effect::setName(std::string name)
{
	effectName = name;
}

std::string Effect::getName()
{
	return effectName;
}