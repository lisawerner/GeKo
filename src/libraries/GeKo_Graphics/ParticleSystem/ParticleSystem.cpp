#include "GeKo_Graphics/ParticleSystem/ParticleSystem.h"

ParticleSystem::ParticleSystem(glm::vec3 position)
{
	setPosition(position);
}

ParticleSystem::ParticleSystem(glm::vec3 position, Effect* effect)
{
	setPosition(position);
	setEffect(effect);
}

ParticleSystem::ParticleSystem(glm::vec3 position, const char* filepath)
{
	setPosition(position);
	loadEffect(filepath);
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