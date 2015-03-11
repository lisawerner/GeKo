#pragma once
#include "GeKo_Graphics/Shader/Shader.h"
#include "GeKo_Graphics/Camera/Camera.h"

//das Folgende fliegt noch raus
#include "GeKo_Graphics/ObjectInclude.h"
//#include "GeKo_Graphics/Object/Geometry.h"
//#include "GeKo_Graphics/Object/Teapot.h"
//#include "GeKo_Graphics/Object/Cube.h"
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
	void update(glm::vec3 playerPosition); //for moving emitter
	void generateParticle();
	void generateParticle(glm::vec3 playerPosition); //also for moving emitter
	void pushParticle(int numberNewParticle);
	void pushParticle(int numberNewParticle, glm::vec3 playerPosition); //alos for moving emitter

	//handle the buffer
	void loadBuffer();

	//switch between Point Sprites & Geometry Shader. PS is default
	void switchToGeometryShader();
	void switchToPointSprites();

	//draw the particle
	void render(Camera &cam);

	//our method & var for velocity
	glm::vec3 static useVelocityZero(); //TODO
	glm::vec3 static useVelocityLeftQuarterCircle();
	glm::vec3 static useVelocityRightQuarterCircle();
	glm::vec3 static useVelocitySemiCircle();
	glm::vec3 static useVelocityCircle();
	glm::vec3 static useVelocitySemiSphere();
	glm::vec3 static useVelocitySphere();
	void setVelocity(glm::vec3(*pfunc)());
	glm::vec3(*m_pfunc)();

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
	void setComputeShader(std::string address);
	void setSpeed(float speed);
	void setAreaEmitting(bool areaEmittingXY, bool areaEmittingXZ, float size, int accuracy);
	void addTexture(Texture &texture, float percentageLife);
	void deleteTexture(int position);
	void useTexture(bool useTexture, float particleSize,
		float birthTime = 0.0, float deathTime = 0.0, bool rotateLeft = false, float rotationSpeed = 0.0);
	void useTexture(bool useTexture, std::vector<float> scalingSize, std::vector<float> scalingMoment, 
		float birthTime = 0.0, float deathTime = 0.0, bool rotateLeft = false, float rotationSpeed = 0.0);

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
	float m_movementLength;
	bool m_movementVertical = false;
	bool m_movementHorizontalX = false;
	bool m_movementHorizontalZ = false;

	//Kevin
	glm::vec4* positions;
	std::vector<glm::vec4> colorList;
	bool m_useColorFlow = false;
	GLuint color_ubo;
	float m_speed = 0.0f;
	float m_birthTime;
	float m_deathTime;
	std::vector<Texture> m_textureList;
	float m_scalingData [32];
	int m_scalingCount = 0;
	bool m_useScaling = false;
	bool m_rotateLeft = true;
	float particleDefaultSize = 1.0;
	void movePosition(glm::vec3 playerPosition);

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
	bool m_particleMortal;
	int minParticleSize;	//TODO (better by an array?)
	int maxParticleSize;	//TODO
	glm::vec4 m_gravity = glm::vec4(0.0,-1.0,0.0,1.0);		//xyz = direction of the gravity, z = power

	//Var for time measure
	double generateTime;	//The last time, when particle were generated	
	double updateTime;		//The last time, when particle were updated
	double deltaTime;		//temp var which calculate the difference of actual time & generateTime/updateTime

	//Var for emitting in an Area
	bool m_areaEmittingXY = false;
	bool m_areaEmittingXZ = false;
	float m_areaSize;
	int m_areaAccuracy;

	//Property of the rendering
	bool m_useGeometryShader = false;
	bool m_usePointSprites = true;
	bool m_useTexture = false;

	//Property of the Geometry Shader
	float m_rotationSpeed = 0.0;
};

/*
1. lifetime = 0.0?
2. angle / ubo
3. delete all unnecessary things
4. dynamic position
5. memory
6. rename & stuff
*/