#include "Debugger.h"
///Output-Stream for error-messages
std::ofstream debugLog;

Debugger::Debugger(){
	/*
	 * TODO: Context woanders korrekt setzen
	 */ 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  glewExperimental = GL_TRUE;
  
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  //TODO: Pfad anpassen
  debugLog.open("OGLdebugLog.txt");

}

Debugger::~Debugger() { }

void APIENTRY defaultDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
  debugLog << "message: " << message << "\n";
  debugLog << "type: ";
  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    debugLog << "ERROR";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    debugLog << "DEPRECATED_BEHAVIOR";
    break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		debugLog << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		debugLog << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		debugLog << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_MARKER:
		debugLog << "ANNOTATION";
		break;
	case GL_DEBUG_TYPE_OTHER:
		debugLog << "OTHER";
		break;
	}
	debugLog << "\n";
	debugLog << "source: ";
	switch(source) {
	case GL_DEBUG_SOURCE_API:
		debugLog << "SOURCE_API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		debugLog << "WINDOW_SYSTEM";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		debugLog << "SHADER_COMPILER";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		debugLog << "THIRD_PARTY";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		debugLog << "SOURCE_APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		debugLog << "OTHER";
		break;
	} 
	debugLog << "\n";
	debugLog << "id: " << id << "\n";
	debugLog << "severity: ";

	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:
		debugLog << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		debugLog << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		debugLog << "HIGH";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		debugLog << "NOTIFICATION";
		break;
	}
	debugLog << "\n\n";
}

void Debugger::setDebugCallback() {
  glDebugMessageCallback(defaultDebugCallback, NULL);
  glEnable (GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void Debugger::setDebugCallback(GLDEBUGPROC debugCallback) {
	glDebugMessageCallback(debugCallback, NULL);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void Debugger::checkDebugMode() {
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Checking Debug Mode:" << std::endl;
	const GLubyte *extensions;
	GLint debugAvailable = 0;
	GLint flags = 0;
	extensions = glGetString(GL_EXTENSIONS);

	/*debugAvailable = (strstr((const char *) extensions, "GL_KHR_debug") != NULL);
	if (debugAvailable)
	std::cout << "KHR_debug supported" << std::endl;
	*/
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	std::cout << "Flags: " << flags << std::endl;
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		std::cout << "OpenGL debug context present" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
}