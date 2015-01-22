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
  m_useReflections(false),
  m_useAntiAliasing(false),
	m_ping(NULL), m_pong(NULL), 
	m_currentViewMatrix(NULL), m_currentProjectionMatrix(NULL),
  m_shaderGBuffer(NULL), m_shaderRLR(NULL), m_shaderSFQ(NULL), m_shaderFXAA(NULL)
{
  m_sfq.loadBufferData();
  context.bindContext();
  printInfo();
}

Renderer::~Renderer()
{
	delete m_ping;
	delete m_pong;
	delete m_shaderGBuffer;
  delete m_shaderRLR;
  delete m_shaderSFQ;
  delete m_shaderFXAA;
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
	//create ping pong fbos
	m_ping = new FBO(windowWidth, windowHeight, 3, true, false);
	m_pong = new FBO(windowWidth, windowHeight, 3, false, false);
	
	//load Shader
  
  VertexShader vsGBuffer(loadShaderSource(SHADERS_PATH + std::string("/GBuffer/GBuffer.vert")));
	FragmentShader fsGBuffer(loadShaderSource(SHADERS_PATH + std::string("/GBuffer/GBuffer.frag")));
	m_shaderGBuffer = new ShaderProgram(vsGBuffer, fsGBuffer);

  if (m_useReflections)
  {
    VertexShader vsRLR(loadShaderSource(SHADERS_PATH + std::string("/RealtimeLocalReflections/RealtimeLocalReflections.vert")));
    FragmentShader fsRLR(loadShaderSource(SHADERS_PATH + std::string("/RealtimeLocalReflections/RealtimeLocalReflections.frag")));
    m_shaderRLR = new ShaderProgram(vsRLR, fsRLR);
  }
	
	VertexShader vsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/ScreenFillingQuad.vert")));
	FragmentShader fsSfq(loadShaderSource(SHADERS_PATH + std::string("/ScreenFillingQuad/ScreenFillingQuad.frag")));
	m_shaderSFQ = new ShaderProgram(vsSfq, fsSfq);

  if (m_useAntiAliasing)
  {
  VertexShader vsFXAA(loadShaderSource(SHADERS_PATH + std::string("/FXAA/FXAA.vert")));
  FragmentShader fsFXAA(loadShaderSource(SHADERS_PATH + std::string("/FXAA/FXAA.frag")));
  m_shaderFXAA = new ShaderProgram(vsFXAA, fsFXAA);
  }
}

void Renderer::renderScene(Scene& scene, Window& window)
{
  if (!m_ping || !m_pong)
    init(window.getWidth(), window.getHeight());

  m_currentFBOIndex = 0;

	bindFBO();
  //m_ping->bind();
	glClearColor(0, 0, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shaderGBuffer->bind();

	m_currentViewMatrix = &scene.getScenegraph()->getActiveCamera()->getViewMatrix();
	m_currentProjectionMatrix = &scene.getScenegraph()->getActiveCamera()->getProjectionMatrix();

	m_shaderGBuffer->sendMat4("viewMatrix", *m_currentViewMatrix);
	m_shaderGBuffer->sendMat4("projectionMatrix", *m_currentProjectionMatrix);
	m_shaderGBuffer->sendInt("useTexture", 1);
	scene.render(*m_shaderGBuffer);
	m_shaderGBuffer->unbind();
  unbindFBO();
  
  if (m_useReflections)
    renderReflections(window.getWidth(), window.getHeight(), scene.getScenegraph()->getActiveCamera()->getNear(), scene.getScenegraph()->getActiveCamera()->getFar());

  if (m_useAntiAliasing)
    renderAntiAliasing(window.getWidth(), window.getHeight());

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
  if (!m_currentFBOIndex)
  {
	  return m_pong;
  }

  else
  {
	  return m_ping;
  }
}

void Renderer::renderReflections(int windowWidth, int windowHeight, float camNear, float camFar)
{
  if (!m_shaderRLR)
    init(windowWidth, windowHeight);

  bindFBO();
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shaderRLR->bind();

  
  m_shaderRLR->sendSampler2D("positionTexture", getLastFBO()->getColorTexture(0), 0);
  m_shaderRLR->sendSampler2D("normalTexture", getLastFBO()->getColorTexture(1), 1);
  m_shaderRLR->sendSampler2D("colorTexture", getLastFBO()->getColorTexture(2), 2);
  m_shaderRLR->sendSampler2D("depthBuffer", getLastFBO()->getDepthTexture(), 3);

  m_shaderRLR->sendMat4("projectionMatrix", *m_currentProjectionMatrix);

  m_shaderRLR->sendInt("screenWidth", windowWidth);
  m_shaderRLR->sendInt("screenHeight", windowHeight);

  m_shaderRLR->sendFloat("zNear", camNear);
  m_shaderRLR->sendFloat("zFar", camFar);

  m_sfq.renderGeometry();

  m_shaderRLR->unbind();
  unbindFBO();  
}

void Renderer::renderAntiAliasing(int windowWidth, int windowHeight)
{
  if (!m_shaderFXAA)
    init(windowWidth, windowHeight);

  bindFBO();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_shaderFXAA->bind();

  m_shaderFXAA->sendSampler2D("colorTexture", getLastFBO()->getColorTexture(2), 2);
  m_shaderFXAA->sendInt("fboWidth", windowWidth);
  m_shaderFXAA->sendInt("fboHeight", windowHeight);

  m_sfq.renderGeometry();

  m_shaderFXAA->unbind();
  unbindFBO();
}