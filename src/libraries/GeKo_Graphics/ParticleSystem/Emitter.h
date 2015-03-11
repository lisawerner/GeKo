#pragma once
#include "GeKo_Graphics/Shader/Shader.h"
#include "GeKo_Graphics/Camera/Camera.h"
#include "GeKo_Graphics/ObjectInclude.h"
#include "GeKo_Graphics/Material/Texture.h"

/*
Description:
Source of the particles. Has parameter which define the form and the distribution of the particles

Tipps:
the particle maximum is PARTICLELIFETIME * PARTICLESPEREMIT / EMITFREQUENCY

Methods:
-setVelocity: for the movement in the beginning
-usePhysic..: how the particle should moving
-setAreaEmitting: if the particle should not come from the source, but in an area
-addTexture & useTexture: to generate with textures
-switchToGeometryShader or switchToPointSprites: to use Geometry Shader or PointSprites
*/
class Emitter{
public:
	/*
	1. Description
		the constructor of the source for the particle. 
		Point Sprites Shader is default. If you want change, use the method switchToGeometryShader()

	2. Attributes
		Emitter:
			if OUTPUT is 0, we generate constant new particle, if 1 we just do it once and if -1, the emitter is unused
			if EMITTERLIFE is equal zero, then the emitter won't die
			EMITFREQUENCY defines after how many time we generate new particles
			PARTICLESPEREMIT defines how much particle we generate, when we are generating some
	
		Particles:
			if PARTICLEMORTAL is false, that means the particle won't die, so the OUTPUT will be setted as once,
			the EMITFREQUENCY and DEATHTIME will be 0.0 (DEATHTIME is the time how long the blending in the end of the particlelife takes) 
	*/
	Emitter(const int OUTPUT, glm::vec3 position, double emitterLifetime, double emitFrequency, int particlesPerEmit, 
		double particleLifeTime, bool particleMortal);
	/*
	
	*/
	~Emitter();

	//set the time for generating and stuff
	void startTime();

	//update & generate the particle
	void update();
	void generateParticle();
	void pushParticle(int numberNewParticle);

	//for moving emitter
	void update(glm::vec3 playerPosition);
	void generateParticle(glm::vec3 playerPosition);
	void pushParticle(int numberNewParticle, glm::vec3 playerPosition);
	void movePosition(glm::vec3 playerPosition);

	//handle the buffer
	void loadBuffer();
	glm::vec4* positions;

	//switch between Point Sprites & Geometry Shader. PS is default. Differents CS can be loaded 
	void switchToGeometryShader();
	void switchToPointSprites();
	void setComputeShader(std::string address);

	//draw the particle
	void render(Camera &cam);

	//our method & var for velocity
	void setAreaEmitting(bool areaEmittingXY, bool areaEmittingXZ, float size, int accuracy);
	static glm::vec3 useVelocityZero();
	static glm::vec3 useVelocityLeftQuarterCircle();
	static glm::vec3 useVelocityRightQuarterCircle();
	static glm::vec3 useVelocitySemiCircle();
	static glm::vec3 useVelocityCircle();
	static glm::vec3 useVelocitySemiSphere();
	static glm::vec3 useVelocitySphere();
	void setVelocity(glm::vec3(*pfunc)());
	glm::vec3(*m_pfunc)();

	//our physic possibilities
	void usePhysicTrajectory(glm::vec4 gravity, float speed);
	bool m_useTrajectory = false;
	void usePhysicDirectionGravity(glm::vec4 gravity, float speed);
	bool m_usePointGravity = false;
	void usePhysicPointGravity(glm::vec4 gravity, float gravityRange, int gravityFunction, float speed);
	bool m_useDirectionGravity = true;
	void usePhysicSwarmCircleMotion(bool verticalMovement, bool horizontalXMovement, bool horizontalYMovement, float movementLength);
	bool m_useChaoticSwarmMotion = false;

	//our physic attributes
	float m_gravityRange = 0.0f;
	int m_gravityFunction = 0;
	float m_speed = 0.0f;
	float m_movementLength; //TODO
	bool m_movementVertical = false;
	bool m_movementHorizontalX = false;
	bool m_movementHorizontalZ = false;

	//texturing	
	void addTexture(Texture &texture, float percentageLife);
	void deleteTexture(int position);
	void useTexture(bool useTexture, float particleSize,
		float birthTime = 0.0, float deathTime = 0.0, bool rotateLeft = false, float rotationSpeed = 0.0);
	void useTexture(bool useTexture, std::vector<float> scalingSize, std::vector<float> scalingMoment,
		float birthTime = 0.0, float deathTime = 0.0, bool rotateLeft = false, float rotationSpeed = 0.0);
	std::vector<Texture> m_textureList;

	//rotating, scaling and blending of the particle
	float m_birthTime;
	float m_deathTime;
	float m_scalingData[32];
	int m_scalingCount = 0;
	bool m_useScaling = false;
	float particleDefaultSize = 1.0;
	bool m_rotateLeft = true;

	//change properties
	void setOutputMode(const int OUTPUT);
	void setPosition(glm::vec3 newPosition);
	void setEmitterMortality(double emitterLifetime);
	void setEmitterLifetime(double emitterLifetime);
	void setEmitFrequency(float newEmitFrequency);
	void setParticlesPerEmit(int numberParticles);
	void setParticleLifetime(float newLifetime);
	void setParticleMortality(bool particleMortality);
	void setGravity(glm::vec4 newGravity);
	void setSpeed(float speed);

	//get properties
	int getOutputMode();
	glm::vec3 getPosition();
	bool getEmitterMortality();
	double getEmitterLifetime();
	double getEmitFrequency();
	int getParticlesPerEmit();
	float getParticleLifetime();
	bool getParticleMortality();
	glm::vec4 getGravity();
	float getSpeed();
	bool getAreaEmittingXZ();
	bool getAreaEmittingXY();
	float getAreaSize();
	int getAreaAccuracy();
	bool getUseTexture();
	bool getUseGeometryShader();
	bool getUsePointSprites();
	float getRotationSpeed();

private:
	//updates the buffer and compute size
	void updateSize();

	//Buffers
	GLuint position_ssbo;
	GLuint velocity_ssbo;
	GLuint angle_ssbo;

	//Our Vertex, Fragment & Compute Shader
	ShaderProgram *emitterShader;
	ShaderProgram *compute;

	//Var how the Output should flow
	enum FLOW { UNUSED = -1, CONSTANT = 0, ONCE = 1 } m_output;

	//Var for the buffer iteration
	int indexBuffer = 0;

	//property of the emitter
	glm::vec3 emitterPosition;
	bool emitterMortal;			//if the emitter stops working after emitLifetime
	double emitLifetime;	//if mortal=true: how long the emitter is active
	float emitFrequency;	//After this frequencytime we generate particle

	//Number of particles
	int numMaxParticle;		//How many particles we has as maximum
	int particlesPerEmit;	//How many new particles we emit per second
	int computeGroupCount;	//number of compute groups (for glDispatchCompute)

	//property of the particle
	float particleLifetime;	//lifetime of any particle in seconds
	bool m_particleMortal; //if the particle can die
	glm::vec4 m_gravity = glm::vec4(0.0,-1.0,0.0,1.0);		//xyz = direction of the gravity, z = power

	//Var for time measure
	double generateTime;	//The last time, when particle were generated	
	double updateTime;		//The last time, when particle were updated
	double deltaTime;		//temp var which calculate the difference of actual time & generateTime/updateTime

	//Var for emitting in an Area
	bool m_areaEmittingXY = false;
	bool m_areaEmittingXZ = false;
	float m_areaSize = 3.0;
	int m_areaAccuracy = 1000;

	//Property of the rendering
	bool m_useGeometryShader = false;
	bool m_usePointSprites = true;
	bool m_useTexture = false;

	//Property of the Geometry Shader
	float m_rotationSpeed = 0.0;
};