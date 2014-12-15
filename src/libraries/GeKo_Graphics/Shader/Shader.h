#ifndef SHADER_H
#define SHADER_H

#pragma once
//#include "GeKo_Graphics/Defs.h"
#include <string>
#include "GeKo_Graphics/Light/PointLight.h"
#include "GeKo_Graphics/Light/DirectionLight.h"
#include "GeKo_Graphics/Light/ConeLight.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

class PointLight;
class DirectionLight;
class ConeLight;

// Do I really need to do this? Better use something different than GLEW
enum ShaderType{
    VERTEX_SHADER = 0x8B31,
    FRAGMENT_SHADER = 0x8B30,
    GEOMETRY_SHADER = 0x8DD9,
};
/// Loads the shader source from a location
std::string loadShaderSource(std::string path);

/// FIXME: Doesn't check properly - Validates the shader 
void checkShader(GLuint shader);

struct BaseShader{
    GLuint handle;
    BaseShader(const std::string &shaderSource, ShaderType shaderType);
};
struct VertexShader : public BaseShader{
    VertexShader(const std::string &shaderSource) : BaseShader(shaderSource, VERTEX_SHADER){}
};
struct FragmentShader : public BaseShader{
    FragmentShader(const std::string &shaderSource) : BaseShader(shaderSource, FRAGMENT_SHADER){}
};
struct GeometryShader : public BaseShader{
    GeometryShader(const std::string &shaderSource) : BaseShader(shaderSource, GEOMETRY_SHADER){}
};
/**
TODO: Add additional shader
*/

template<typename ... Args>
void attachShaders(GLuint handle, GLuint shaderHandle, Args ...args);
void attachShaders(GLuint handle, GLuint shaderHandle);

class ShaderProgram{

public:
    GLuint handle;
    ShaderProgram(const VertexShader &vs, const FragmentShader &fs);
    void bind() const;
    void unbind() const;
    GLuint getLocation(std::string uniform);
	void sendInt(std::string uniform, int i);
	void sendDouble(std::string uniform, double d);
	void sendFloat(std::string uniform, float f);
    void sendVec3(std::string uniform,glm::vec3 v);
	void sendVec4(std::string uniform, glm::vec4 v);
	void sendMat4(std::string uniform, glm::mat4 m);
	void sendSampler2D(std::string uniform, GLuint sampler2Dhandler);
	void sendSampler2D(std::string uniform, GLuint sampler2Dhandler, int textureIndex);
	void sendSkyboxTexture(std::string uniform, GLuint sampler2Dhandler);
	void sendLightData(std::string uniformPosition, std::string uniformColor, std::string uniformDirection, std::string uniformExponent, std::string uniformAngle, std::string uniformRadius, PointLight light);
	void sendLightData(std::string uniformPosition, std::string uniformColor, std::string uniformDirection, std::string uniformExponent, std::string uniformAngle, std::string uniformRadius, DirectionLight light);
	void sendLightData(std::string uniformPosition, std::string uniformColor, std::string uniformDirection, std::string uniformExponent, std::string uniformAngle, std::string uniformRadius, ConeLight light);
	//add sendLight general

};

#endif