#include "WindowGL.h"
#include <GLFW\glfw3.h>
#include <cstdio>
#include <Debug.h>

GLFWwindow* WindowGL::window = nullptr;
int WindowGL::width = 0;
int WindowGL::height = 0;

WindowGL::WindowGL()
{
	
}

bool WindowGL::CreateMyWindow(const char* _name, int _width, int _height)
{
	if (window)
	{
		Debug::Log("Failed to create window !!!");
		Debug::Log("Window already create !!!");
		return false;
	}
	width = _width;
	height = _height;
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, _name, NULL, NULL);
	if (window == NULL) 
	{
		Debug::Log("Failed to open GLFW window. Intel GPU are not 3.3 compatible.");
		int _i = getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}
