#include "Renderer.h"

void OpenGL3Context::bindContext() const{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glewExperimental = GL_TRUE;
}

Renderer::Renderer(const RenderContext &context) :

m_currentFBOIndex(false),
m_gBuffer(NULL), m_shaderGBuffer(NULL),
m_ping(NULL), m_pong(NULL),
m_firstRender(true),
m_shaderSFQ(NULL),

m_useDeferredShading(false),  m_shaderDSLighting(NULL), m_shaderDSCompositing(NULL), m_dsLightRootNode(NULL), m_dsLightColor(NULL),
m_useReflections(false),      m_shaderRLR(NULL),
m_useAntiAliasing(false),     m_shaderFXAA(NULL),
m_useBloom(false),            m_shaderBloom(NULL),
m_useSSAO(false),             m_shaderSSAOcalc(NULL), m_shaderSSAOblur(NULL), m_shaderSSAOfinal(NULL),


m_currentViewMatrix(glm::mat4()), m_currentProjectionMatrix(glm::mat4()),
m_windowWidth(0), m_windowHeight(0)
  
{
  m_sfq.loadBufferData();
  context.bindContext();
  printInfo();
}

Renderer::~Renderer()
{
  delete m_ping;
  delete m_pong;
  delete m_gBuffer;
  delete m_shaderGBuffer;
  delete m_shaderSFQ;

  if(m_useReflections)       delete m_shaderRLR;
  if(m_useAntiAliasing)      delete m_shaderFXAA;
  if(m_useDeferredShading)   delete m_shaderDSLighting;
  if(m_useDeferredShading)   delete m_shaderDSCompositing;
  if(m_useBloom)             delete m_shaderBloom;
  if(m_useSSAO)              delete m_shaderSSAOcalc;
  if(m_useSSAO)              delete m_shaderSSAOblur;
  if(m_useSSAO)              delete m_shaderSSAOfinal;
}

void Renderer::printInfo(){

  std::cout << "=============================================" << std::endl;
  // print out some info about the graphics drivers
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "=============================================" << std::endl;
}

void Renderer::init(int windowWidth, int windowHeight)
{
  m_windowWidth  = windowWidth;
  m_windowHeight = windowHeight;

  //create ping pong fbos
  m_ping    = new FBO(windowWidth, windowHeight, 3, true, false);
  m_pong    = new FBO(windowWidth, windowHeight, 3, true, false);
  m_gBuffer = new FBO(windowWidth, windowHeight, 3, true, false);

  //load Shader

  VertexShader vsGBuffer(loadShaderSource(SHADERS_PATH + std::string("/GBuffer/GBuffer.vert")));
  FragmentShader fsGBuffer(loadShaderSource(SHADERS_PATH + std::string("/GBuffer/GBuffer.frag")));
  m_shaderGBuffer = new ShaderProgram(vsGBuffer, fsGBuffer);

  if (m_useDeferredShading)
  {
    VertexShader vsDsLighting(loadShaderSource(SHADERS_PATH + std::string("/DeferredShading/dsLighting.vert")));
    FragmentShader fsDsLighting(loadShaderSource(SHADERS_PATH + std::string("/DeferredShading/dsLighting.frag")));
    m_shaderDSLighting = new ShaderProgram(vsDsLighting, fsDsLighting);

    VertexShader vsDsCompositing(loadShaderSource(SHADERS_PATH + std::string("/DeferredShading/dsFinalCompositing.vert")));
    FragmentShader fsDsCompositing(loadShaderSource(SHADERS_PATH + std::string("/DeferredShading/dsFinalCompositing.frag")));
    m_shaderDSCompositing = new ShaderProgram(vsDsCompositing, fsDsCompositing);
  }

  if (m_useReflections)
  {
    VertexShader vsRLR(loadShaderSource(SHADERS_PATH + std::string("/RealtimeLocalReflections/RealtimeLocalReflections.vert")));
    FragmentShader fsRLR(loadShaderSource(SHADERS_PATH + std::string("/RealtimeLocalReflections/RealtimeLocalReflections.frag")));
    m_shaderRLR = new ShaderProgram(vsRLR, fsRLR);
  }

  VertexShader vsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/ScreenFillingQuad.vert")));
  FragmentShader fsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/ScreenFillingQuad.frag")));
  m_shaderSFQ = new ShaderProgram(vsSfq, fsSfq);

  if (m_useBloom)
  {
    VertexShader vsBloom(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/ScreenFillingQuad.vert")));
    FragmentShader fsBloom(loadShaderSource(SHADERS_PATH + std::string("/Bloom/Bloom.frag")));
    m_shaderBloom = new ShaderProgram(vsBloom, fsBloom);
  }

  if (m_useAntiAliasing)
  {
    VertexShader vsFXAA(loadShaderSource(SHADERS_PATH + std::string("/FXAA/FXAA.vert")));
    FragmentShader fsFXAA(loadShaderSource(SHADERS_PATH + std::string("/FXAA/FXAA.frag")));
    m_shaderFXAA = new ShaderProgram(vsFXAA, fsFXAA);
  }

  if (m_useSSAO)
  {
    VertexShader vsSSAO(loadShaderSource(SHADERS_PATH + std::string("/SSAO/ssao.vert")));
    FragmentShader fsSSAO(loadShaderSource(SHADERS_PATH + std::string("/SSAO/ssao.frag")));
    m_shaderSSAOcalc = new ShaderProgram(vsSSAO, fsSSAO);

    VertexShader vsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/ScreenFillingQuad.vert")));
    FragmentShader fsBLUR(loadShaderSource(SHADERS_PATH + std::string("/SSAO/ssaoBlur.frag")));
    m_shaderSSAOblur = new ShaderProgram(vsSfq, fsBLUR);

    FragmentShader fsFinal(loadShaderSource(SHADERS_PATH + std::string("/SSAO/ssaoFinal.frag")));
    m_shaderSSAOfinal = new ShaderProgram(vsSfq, fsFinal);
  }
 }

void Renderer::renderScene(Scene& scene, Window& window)
{


  if (!m_ping || !m_pong)
    init(window.getWidth(), window.getHeight());

  m_firstRender = true;

  m_currentFBOIndex = 0;

  m_gBuffer->bind();
  glClearColor(0, 0, 0, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_shaderGBuffer->bind();

  m_currentViewMatrix = scene.getScenegraph()->getActiveCamera()->getViewMatrix();
  m_currentProjectionMatrix = scene.getScenegraph()->getActiveCamera()->getProjectionMatrix();

  m_shaderGBuffer->sendMat4("viewMatrix", m_currentViewMatrix);
  m_shaderGBuffer->sendMat4("projectionMatrix", m_currentProjectionMatrix);

  scene.render(*m_shaderGBuffer);
  m_shaderGBuffer->unbind();
  m_gBuffer->unbind();

  if (m_useSSAO)
    renderSSAO();

  if (m_useDeferredShading)
    renderDeferredShading();

  if (m_useReflections)
    renderReflections(scene.getScenegraph()->getActiveCamera()->getNear(), scene.getScenegraph()->getActiveCamera()->getFar());

  if (m_useBloom)
    renderBloom();

  if (m_useAntiAliasing)
    renderAntiAliasing();


  //Render SFQ
  m_shaderSFQ->bind();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_shaderSFQ->sendSampler2D("texture", getLastFBO()->getColorTexture(2));
  m_sfq.renderGeometry();
  m_shaderSFQ->unbind();

  glfwSwapBuffers(window.getWindow());
  glfwPollEvents();
}

void Renderer::useReflections(bool useReflections)
{
  m_useReflections = useReflections;
}

void Renderer::useAntiAliasing(bool useAntiAliasing)
{
  m_useAntiAliasing = useAntiAliasing;
}

void Renderer::useDeferredShading(bool useDeferredShading, Node *lightRootNode, glm::fvec3 *lightColor)
{
  m_useDeferredShading = useDeferredShading;
  m_dsLightRootNode = lightRootNode;
  m_dsLightColor = lightColor;
}

void Renderer::useBloom(bool useBloom)
{
  m_useBloom = useBloom;
}

void Renderer::useSSAO(bool useSSAO)
{
  m_useSSAO = useSSAO;
}

void Renderer::bindFBO()
{
  if (!m_currentFBOIndex)
  {
    m_ping->bind();
  }

  else if (m_currentFBOIndex)
  {
    m_pong->bind();
  }
}

void Renderer::unbindFBO()
{
  if (!m_currentFBOIndex)
  {
    m_ping->unbind();
    m_currentFBOIndex = 1;
  }

  else if (m_currentFBOIndex)
  {
    m_pong->unbind();
    m_currentFBOIndex = 0;
  }
}

FBO* Renderer::getLastFBO()
{
  if (m_firstRender)
  {
    m_firstRender = false;
    return m_gBuffer;
  }
  if (!m_currentFBOIndex)
  {
    return m_pong;
  }

  else
  {
    return m_ping;
  }
}

void Renderer::renderReflections(float camNear, float camFar)
{
  if (!m_shaderRLR)
    init(m_windowWidth, m_windowHeight);

  bindFBO();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shaderRLR->bind();


  m_shaderRLR->sendSampler2D("positionTexture", m_gBuffer->getColorTexture(0), 0);
  m_shaderRLR->sendSampler2D("normalTexture", m_gBuffer->getColorTexture(1), 1);
  m_shaderRLR->sendSampler2D("colorTexture", getLastFBO()->getColorTexture(2), 2);
  m_shaderRLR->sendSampler2D("depthBuffer", m_gBuffer->getDepthTexture(), 3);

  m_shaderRLR->sendMat4("projectionMatrix", m_currentProjectionMatrix);

  m_shaderRLR->sendInt("screenWidth", m_windowWidth);
  m_shaderRLR->sendInt("screenHeight", m_windowHeight);

  m_shaderRLR->sendFloat("zNear", camNear);
  m_shaderRLR->sendFloat("zFar", camFar);

  m_sfq.renderGeometry();

  m_shaderRLR->unbind();
  unbindFBO();
}

void Renderer::renderAntiAliasing()
{
  if (!m_shaderFXAA)
    init(m_windowWidth, m_windowHeight);

  bindFBO();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shaderFXAA->bind();

  m_shaderFXAA->sendSampler2D("colorTexture", getLastFBO()->getColorTexture(2), 2);
  m_shaderFXAA->sendInt("fboWidth", m_windowWidth);
  m_shaderFXAA->sendInt("fboHeight", m_windowHeight);

  m_sfq.renderGeometry();

  m_shaderFXAA->unbind();
  unbindFBO();
}

void Renderer::renderDeferredShading()
{
  if (!m_shaderDSLighting || !m_shaderDSCompositing)
    init(m_windowWidth, m_windowHeight);

  if (!m_dsLightColor || !m_dsLightRootNode)
    throw std::string("Error in renderDeferredShading - Light Color or Light Root Node was not set");

  FBO *a = new FBO(m_windowWidth,m_windowHeight,3,false,false);

  a->bind();

  glCullFace(GL_FRONT);
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shaderDSLighting->bind();

  m_shaderDSLighting->sendMat4("viewMatrix", m_currentViewMatrix);
  m_shaderDSLighting->sendMat4("projectionMatrix", m_currentProjectionMatrix);

  m_shaderDSLighting->sendSampler2D("positionMap", m_gBuffer->getColorTexture(0), 0);
  m_shaderDSLighting->sendSampler2D("normalMap", m_gBuffer->getColorTexture(1), 1);

  m_shaderDSLighting->sendInt("windowWidth", m_windowWidth);
  m_shaderDSLighting->sendInt("windowHeight", m_windowHeight);

  m_shaderDSLighting->sendVec3("lightColor", *m_dsLightColor);

  m_dsLightRootNode->render(*m_shaderDSLighting);

  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  m_shaderDSLighting->unbind();
  a->unbind();

  //COMPOSITING TEIL ===============================
  bindFBO();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_shaderDSCompositing->bind();

  m_shaderDSCompositing->sendSampler2D("colorMap", getLastFBO()->getColorTexture(2), 0);
  m_shaderDSCompositing->sendSampler2D("lightMap", a->getColorTexture(2), 1);

  m_sfq.renderGeometry();

  m_shaderDSCompositing->unbind();
  unbindFBO();

  delete a;
}

void Renderer::renderBloom()
{
  if (!m_shaderBloom)
    init(m_windowWidth, m_windowHeight);

  bindFBO();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shaderBloom->bind();

  m_shaderBloom->sendSampler2D("bgl_RenderedTexture", getLastFBO()->getColorTexture(2),2);
  m_sfq.renderGeometry();

  m_shaderBloom->unbind();

 unbindFBO();
}

void Renderer::renderSSAO()
{
  if (!m_shaderSSAOcalc || !m_shaderSSAOblur || !m_shaderSSAOfinal)
    init(m_windowWidth, m_windowHeight);

  FBO *a = new FBO(m_windowWidth, m_windowHeight, 3, false, false);
  FBO *b = new FBO(m_windowWidth, m_windowHeight, 3, false, false);

  a->bind();
  glClearColor(1, 1, 1, 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shaderSSAOcalc->bind();

  m_shaderSSAOcalc->sendSampler2D("positionMap", m_gBuffer->getColorTexture(0), 0);
  m_shaderSSAOcalc->sendSampler2D("normalMap", m_gBuffer->getColorTexture(1), 1);
  m_shaderSSAOcalc->sendMat4("sceneProjectionMatrix", m_currentProjectionMatrix);
  m_shaderSSAOcalc->sendFloat("radius", 0.1f);
  m_shaderSSAOcalc->sendFloat("quality", 30.0f);

  m_sfq.renderGeometry();

  m_shaderSSAOcalc->unbind();
  a->unbind();



  //Blur #1 SSAO calculation
  b->bind();

  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_shaderSSAOblur->bind();
  m_shaderSSAOblur->sendSampler2D("colortexture", a->getColorTexture(2), 0);
  m_shaderSSAOblur->sendInt("secondPass", 0);
  m_sfq.renderGeometry();

  m_shaderSSAOblur->unbind();
  b->unbind();

  

  //Blur #2 SSAO calculation
  a->bind();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shaderSSAOblur->bind();
  m_shaderSSAOblur->sendSampler2D("colortexture", b->getColorTexture(2), 0);
  m_shaderSSAOblur->sendFloat("secondPass", 1);
  m_sfq.renderGeometry();

  m_shaderSSAOblur->unbind();
  a->unbind();

  glClearColor(0, 0, 0, 0);
  

  //COLOR COMPOSITING
  bindFBO();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_shaderSSAOfinal->bind();
  m_shaderSSAOfinal->sendSampler2D("colorMap", getLastFBO()->getColorTexture(2), 0);
  m_shaderSSAOfinal->sendSampler2D("ssaoMap", a->getColorTexture(2), 1);
  m_sfq.renderGeometry();
  m_shaderSSAOfinal->unbind();
  unbindFBO();
 
  delete a;
  delete b;
}
