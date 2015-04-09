#include "GeKo_Graphics/ParticleSystem/ParticleSystem.h"

ParticleSystem::ParticleSystem(glm::vec3 position)
{
	Effect* effect = new Effect();
	setEffect(effect);
	setPosition(position);
}

ParticleSystem::ParticleSystem(glm::vec3 position, Effect* effect)
{
	setEffect(effect);
	setPosition(position);
}

ParticleSystem::ParticleSystem(glm::vec3 position, const char* filepath)
{
	loadEffect(filepath);
	setPosition(position);
}

ParticleSystem::~ParticleSystem()
{
	//TODO
}


//void ParticleSystem::active()
//{
//	effect->active();
//}

void ParticleSystem::update()
{
	effect->updateEmitters();
}

void ParticleSystem::render(Camera &cam)
{
	effect->renderEmitters(cam);
}

void ParticleSystem::setPosition(glm::vec3 newPosition)
{
	position = newPosition;
	effect->setPosition(newPosition);
}

void ParticleSystem::setEffect(Effect* newEffect)
{
	effect = newEffect;
}

void ParticleSystem::loadEffect(const char* filepath)
{
	effect->loadEffect(filepath);
}

glm::vec3 ParticleSystem::getPosition()
{
	return position;
}

Effect* ParticleSystem::getEffect()
{
	return effect;
}