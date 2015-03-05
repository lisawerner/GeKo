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
Source of the particles. Has parameter which define the form and the distribution of the particles
*/
class Emitter{
public:
	//construct & destructor
	Emitter();	//default constructor
	Emitter(const int OUTPUT, glm::vec3 position, bool mortality, double emitFrequency,
		int particlesPerEmit, double particleLifeTime, glm::vec4 gravity, float speed);	//full constructor
	Emitter(const int OUTPUT);	//temporary consturctor
	~Emitter();

	//Emitter must be activated in the begin for setting the time
	void active();
	void deactive();

	//update & generate the particle
	void update();
	void generateParticle();
	void pushParticle(int numberNewParticle);

	//handle the buffer
	void loadBuffer();

	//switch between Point Sprites & Geometry Shader. PS is default
	void switchToGeometryShader();
	void switchToPointSprites();

	//draw the particle
	void render(Camera &cam);

	//change properties
	void setOutputMode(const int OUTPUT);
	void setPosition(glm::vec3 newPosition);
	void setMortality(bool mortality);
	void setEmitterLifetime(double emitterLifetime);
	void setEmitFrequency(float newEmitFrequency);
	void setParticlesPerEmit(int numberParticles);
	void setParticleLifetime(float newLifetime);
	void setGravity(glm::vec4 newGravity);
	void setComputeVar(bool useTrajector, bool useDirectToGravity, bool useDirectionGravity, bool usePointGravity, float gravityRange, int gravityFunction);
	void setComputeShader(std::string address);
	void setSpeed(float speed);
	void setAreaEmitting(bool areaEmittingXY, bool areaEmittingXZ, float size, int accuracy);
	void addTexture(Texture &texture, float percentageLife);
	void deleteTexture(int position);
	void setUseTexture(bool useTexture);
	void setRotationSpeed(float rotationSpeed);

	//get properties
	int getOutputMode();
	glm::vec3 getPosition();
	bool getMortality();
	double getEmitterLifetime();
	double getEmitFrequency();
	int getParticlesPerEmit();
	float getParticleLifetime();
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

	//Ready for setter & getter?
	bool m_useTrajectory = false;
	bool m_usePointGravity = false;
	bool m_useDirectionGravity = true;
	bool m_useDirectToGravity = false;
	float m_gravityRange = 1.8f;
	int m_gravityFuncion = 0;

	//Kevin
	glm::vec4* positions;
	std::vector<glm::vec4> colorList;
	bool m_useColorFlow = false;
	GLuint color_ubo;
	glm::vec3 getVelocity();
	glm::vec3 m_velocity;
	float m_speed;
	float m_birthTime;
	float m_deathTime;
	std::vector<Texture> m_textureList;
	glm::vec3 static getVelocityZero();
	glm::vec3 static getVelocitySemiCircle();
	glm::vec3 static getVelocitySemiSphere();
	glm::vec3 static getVelocityCircle();
	glm::vec3 static getVelocitySphere();
	void setVelocity(glm::vec3 (*pfunc)());
	glm::vec3 (*m_pfunc)();

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
	bool mortal;			//if the emitter stops working after emitLifetime
	double emitLifetime;	//if mortal=true: how long the emitter is active
	float emitFrequency;	//After this frequencytime we generate particle

	//Number of particles
	int numMaxParticle;		//How many particles we has as maximum
	int particlesPerEmit;	//How many new particles we emit per second
	int computeGroupCount;	//number of compute groups (for glDispatchCompute)

	//property of the particle
	float particleLifetime;	//lifetime of any particle in seconds
	int minParticleSize;	//TODO (better by an array?)
	int maxParticleSize;	//TODO
	glm::vec4 gravity;		//xyz = direction of the gravity, z = power

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
	float m_rotationSpeed = 0;
};