#include "Cursor.h"
#include <WindowGL.h>
#include <GLFW/glfw3.h>

void Cursor::Enable()
{
	glfwSetInputMode(WindowGL::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Cursor::Disable()
{
	glfwSetInputMode(WindowGL::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Cursor::Lock()
{
	glfwSetInputMode(WindowGL::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

glm::vec2 Cursor::GetCursorPosition()
{
	double xpos, ypos;
	glfwGetCursorPos(WindowGL::window, &xpos, &ypos);
	return glm::vec2(xpos, ypos);
}