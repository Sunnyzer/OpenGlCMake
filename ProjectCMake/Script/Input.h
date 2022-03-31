#pragma once
#include "WindowGL.h"
#include <vector>
#include <functional>

class Input
{
	typedef void (*func)();
public:
	#define KeyPressed(glfwKey) glfwGetKey(WindowGL::window, glfwKey) == GLFW_PRESS
	#define KeyReleased(glfwKey) glfwGetKey(WindowGL::window, glfwKey) == GLFW_RELEASE
	#define KeyValue(glfwKey, _pressedValue, _notPressedValue) KeyPressed(_key) ? _pressedValue : _notPressedValue;
	template<class T>
	static T FlipFlop(int _key, T _pressedValue, T _releasedValue)
	{
		return KeyPressed(_key) ? _pressedValue : _releasedValue;
	}
	template<class object,typename func, typename ...args>
	static void UseKey(int _key, object* _object, void (func::*function)(args...), args... arg)
	{
		bool _pressed = false;
		if (!_pressed && KeyPressed(GLFW_KEY_SPACE))
		{
			_pressed = true;
			std::function<void(void)> lambda = [&]() { std::invoke(function, _object, arg...); };
			actionKey.push_back(&lambda);
		};
		if (!KeyPressed(GLFW_KEY_SPACE))
			_pressed = false;
	}

	std::vector<std::function<void(void)>> actionKey;
};