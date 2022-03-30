#pragma once

class WindowGL
{
public:
	static class GLFWwindow* window;
};

class Input
{
	/*#define KeyPressed(glfwKey) glfwGetKey(WindowGL::window, glfwKey) == GLFW_PRESS
	#define KeyReleased(glfwKey) glfwGetKey(WindowGL::window, glfwKey) == GLFW_RELEASE
	#define KeyValue(glfwKey, _pressedValue, _notPressedValue) KeyPressed(_key) ? _pressedValue : _notPressedValue;*/
	template<class T>
	static T FlipFlop(int _key, T _pressedValue, T _notPressedValue)
	{
		return KeyPressed(_key) ? _pressedValue : _notPressedValue;
	}
};