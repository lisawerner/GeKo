#ifndef SHADER_H
#define SHADER_H

#include "Defs.h"
#include <string>

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
    void sendVec3(std::string uniform,glm::vec3 v);
	void sendVec4(std::string uniform, glm::vec4 v);
	void sendSampler2D(std::string uniform, GLuint sampler2Dhandler);
	void sendMat4(std::string uniform, glm::mat4 m);
	void sendVec4(std::string uniform, glm::vec4 v);

	
	
};

#endif