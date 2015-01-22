#pragma once
#include <GeKo_Graphics/Defs.h>
#include <GeKo_Graphics/Buffer.h>
#include <GeKo_Graphics/Shader/Shader.h>
#include <GeKo_Graphics/Scenegraph/Scene.h>
#include <GeKo_Graphics/Shader/FBO.h>

/*
Need Information
*/

struct RenderObject{

};
struct RenderContext{
  virtual void bindContext() const = 0;
};
struct OpenGL3Context : RenderContext {
  /*
  by initializing, the renderer check, if the OS support OpenGL
  */
  virtual void bindContext() const override;
};

class FBO;
class Scene;
class Shader;
class Window;

class Renderer{
public:
  Renderer(const RenderContext &context);
  ~Renderer();

  template<typename T>
  void draw(const Buffer<T> &buffer) {
    buffer.bind();
    //FIXME - Needs generic interface
    glEnableVertexAttribArray(0);
    // MAGIC NUMBER - needs proper information for vertex size
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, buffer.size);
    glDisableVertexAttribArray(0);
    buffer.unbind();
  }
  /*
  print Information about the supported OpenGL & GLSL version, Vendor and Renderer
  */
  void printInfo();

  void init(int windowWidth, int windowHeight);
  void renderScene(Scene& scene, Window& window);

  void useReflections(bool useReflections);
  void useAntiAliasing(bool useAA);

private:
  void bindFBO();
  void unbindFBO();
	FBO* getLastFBO();

  void renderReflections(int windowWidth, int windowHeight, float camNear, float camFar);
  void renderAntiAliasing(int windowWidth, int windowHeight);
   
  bool m_useReflections;
  bool m_useAntiAliasing;

	bool m_currentFBOIndex;
	FBO *m_ping;
	FBO *m_pong;

	glm::mat4 *m_currentProjectionMatrix;
	glm::mat4 *m_currentViewMatrix;
	
	ShaderProgram *m_shaderGBuffer;
	ShaderProgram *m_shaderRLR;
  ShaderProgram *m_shaderSFQ;
  ShaderProgram *m_shaderFXAA;

  Rect m_sfq;
};