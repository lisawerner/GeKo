#pragma once

#include <GeKo_Graphics/Defs.h>
#include <GeKo_Graphics/Buffer.h>
#include <GeKo_Graphics/Shader/Shader.h>
#include <GeKo_Graphics/Scenegraph/Scene.h>
#include <GeKo_Graphics/Shader/FBO.h>
#include <GeKo_Graphics/Scenegraph/Node.h>
#include <glm/glm.hpp>


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

class GUI;
class FBO;
class Scene;
class Shader;
class Window;
class Node;

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

  ///renders the given GUI
  void renderGUI(GUI &guiToRender, Window &window);

  void useReflections(bool useReflections);
  void useAntiAliasing(bool useAntiAliasing);
  void useDeferredShading(bool useDeferredShading, Node *lightRootNode, glm::fvec3 *lightColor = new glm::fvec3(1.0,1.0,1.0));
  void useBloom(bool useBloom);
  void useSSAO(bool useSSAO);

private:
  void bindFBO();
  void unbindFBO();
	FBO* getLastFBO();

  void renderReflections(float camNear, float camFar);
  void renderAntiAliasing();
  void renderDeferredShading();
  void renderBloom();
  void renderSSAO();

  bool m_useReflections;
  bool m_useAntiAliasing;
  bool m_useBloom;
  bool m_useDeferredShading;
  bool m_useSSAO;

  Node *m_dsLightRootNode;
  glm::fvec3 *m_dsLightColor;

	bool m_currentFBOIndex;
  bool m_firstRender;

  FBO *m_gBuffer;
	FBO *m_ping;
	FBO *m_pong;

	glm::mat4 m_currentProjectionMatrix;
	glm::mat4 m_currentViewMatrix;

  int m_windowWidth;
  int m_windowHeight;
	
	ShaderProgram *m_shaderGBuffer;
	ShaderProgram *m_shaderRLR;
  ShaderProgram *m_shaderSFQ;
  ShaderProgram *m_shaderFXAA;
  ShaderProgram *m_shaderDSLighting;
  ShaderProgram *m_shaderDSCompositing;
  ShaderProgram *m_shaderBloom;
  ShaderProgram *m_shaderSSAOcalc;
  ShaderProgram *m_shaderSSAOblur;
  ShaderProgram *m_shaderSSAOfinal;

  Rect m_sfq;
};