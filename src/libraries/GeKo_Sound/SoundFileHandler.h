#pragma once

#include"AL/al.h"
#include"AL/alc.h"
#include"AL/efx.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <vector>
#include <glm/ext.hpp>
#include <map>

//#include <GeKo_Graphics/Scenegraph/Node.h>


class SoundFileHandler{
	public:
		SoundFileHandler::SoundFileHandler(int maxNumberOfSources);
		~SoundFileHandler();

		void generateSource(ALfloat position[3], const char *filepath);
		void generateSource(glm::vec3 position, const char *filepath);
		void generateSource(std::string name, ALfloat position[3], const char *filepath);
		void generateSource(std::string name, glm::vec3 position, const char *filepath);
		void setPitch(int i, float f);
		void setPitch(std::string name, float f);
		void setGain(int i, float f);
		void setGain(std::string name, float f);
		void updateSourcePosition(int i, ALfloat position[3]);
		void updateSourcePosition(std::string name, ALfloat position[3]);
		void updateSourcePosition(int i, glm::vec3 position);
		void updateSourcePosition(std::string name, glm::vec3 position);
		glm::vec3 getSourcePosition(int i);
		glm::vec3 getSourcePosition(std::string name);
		void updateSourceVelocity(int i, ALfloat velocity[3]);
		void updateSourceVelocity(std::string name, ALfloat velocity[3]);
		void updateSourceVelocity(int i, glm::vec3 velocity);
		void updateSourceVelocity(std::string name, glm::vec3 velocity);
		void enableLooping(int i);
		void enableLooping(std::string name);
		void disableLooping(int i);
		void disableLooping(std::string name);
		void updateListenerPosition(ALfloat position[3]);
		void updateListenerPosition(glm::vec3 position);
		glm::vec3 SoundFileHandler::getListenerPosition();
		void updateListenerVelocity(ALfloat velocity[3]);
		void updateListenerVelocity(glm::vec3 velocity);
		glm::vec3 SoundFileHandler::getListenerVelocity();
		void updateListenerOrientation(ALfloat orientation[6]);
		void updateListenerOrientation(glm::vec3 at, glm::vec3 up);
		void playSource(int i);
		void playSource(std::string name);
		void pauseSource(int i);
		void pauseSource(std::string name);
		void stopSource(int i);
		void stopSource(std::string name);
		void playAllSources();
		void pauseAllSources();
		void stopAllSources();

		bool sourceIsPlaying(std::string name);

	//	std::map<Node, std::string> sourceMap;

	protected:
		ALenum tempformat;
		int maxNumberOfSources;
		int numberOfSources;
		ALint iState;
		ALuint* buffers;
		ALuint* sources;
		int generateBufferData(const char *filepath, int numberOfSources);
		int endWithError(char* msg);

		std::map<std::string, int> sourceMap;
		char type[4];
		DWORD size, chunkSize;
		short formatType, channels;
		DWORD sampleRate, avgBytesPerSec;
		short bytesPerSample, bitsPerSample;
		DWORD dataSize;
		ALuint frequency;
		ALenum format; 
		FILE *fp = NULL;
		unsigned char* buf;


};