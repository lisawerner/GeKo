#include "Window.h"

GLFWwindow* m_window;
const char* m_name;
int m_width;
int m_height;
int m_xpos;
int m_ypos;

/*
open a window with a certain size in a certain position and set the context to him
*/
Window::Window(int xpos, int ypos, int width, int height, const char* name, glm::vec3 color)
{
	this->m_name = name;
	this->m_width = width;
	this->m_height = height;
	this->m_xpos = xpos;
	this->m_ypos = ypos;
	
	m_window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwSetWindowPos(m_window, xpos, ypos);
	glfwMakeContextCurrent(m_window);
	glClearColor(color.x, color.y, color.z, 1.0f);
}

Window::~Window()
{
}

/*
assume the new setting of the window like width or xpos
*/
void Window::update()
{
}

/*
close the window and shut down the program
*/
void Window::close(){
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

/*
getter of the actual window
*/
GLFWwindow* Window::getWindow(){
	return m_window;
}
/*
set the name of the window
*/
void Window::setName(const char* name)
{
	m_name = name;
}

/*
get the name of the window
*/
const char* Window::getName()
{
	return m_name;
}

/*
set the width of the window
*/
void Window::setWidth(int width)
{
	m_width = width;
}

/*
get the width of the window
*/
int Window::getWidth()
{
	return m_width;
}

/*
set the height of the window
*/
void Window::setHeight(int height)
{
	m_height = height;
}

/*
get the height of the window
*/
int Window::getHeight()
{
	return m_height;
}

/*
set the xpos of the window
*/
void Window::setXpos(int xpos)
{
	m_xpos = xpos;
}

/*
get the xpos of the window
*/
int Window::getXpos()
{
	return m_xpos;
}

/*
set the xpos of the window
*/
void Window::setYpos(int ypos)
{
	m_ypos = ypos;
}

/*
get the ypos of the window
*/
int Window::getYpos()
{
	return m_ypos;
} 