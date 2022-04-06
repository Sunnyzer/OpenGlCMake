#include "WindowGL.h"
#include <cstdio>
#include <GLFW\glfw3.h>

GLFWwindow* WindowGL::window = nullptr;
int WindowGL::width = 0;
int WindowGL::height = 0;

WindowGL::WindowGL()
{
	
}

bool WindowGL::CreateWindow(const char* _name, int _width, int _height)
{
	if (window) return false;
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
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}
