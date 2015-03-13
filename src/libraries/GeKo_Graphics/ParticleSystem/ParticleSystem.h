#pragma once
#include "GeKo_Graphics/ParticleSystem/Effect.h"

class ParticleSystem{
public:
	ParticleSystem(glm::vec3 position);
	ParticleSystem(glm::vec3 position, Effect* effect);
	ParticleSystem(glm::vec3 position, const char* filepath);
	~ParticleSystem();

	/*void active();*/

	void update();
	void render(Camera &cam);

	void setPosition(glm::vec3 newPosition);
	void setEffect(Effect* newEffect);
	void loadEffect(const char* filepath);

	glm::vec3 getPosition();
	Effect* getEffect();

private:
	glm::vec3 position;
	Effect* effect;
};