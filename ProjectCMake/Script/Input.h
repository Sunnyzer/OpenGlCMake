#pragma once
#include "WindowGL.h"
#include <vector>
#include <functional>
#include <GLFW/glfw3.h>

#define KeyPressed(glfwKey) glfwGetKey(WindowGL::window, glfwKey) == GLFW_PRESS
#define KeyReleased(glfwKey) glfwGetKey(WindowGL::window, glfwKey) == GLFW_RELEASE
//#define KeyValue(glfwKey, _pressedValue, _notPressedValue) KeyPressed(_key) ? _pressedValue : _notPressedValue;

class Input
{
private:
	struct InputAction
	{
	public:
		int keyInput;
		std::function<void(void)>* funcInvoke;

	};
public:
	template<class T>
	static T FlipFlop(int _key, T _pressedValue, T _releasedValue)
	{
		return KeyPressed(_key) ? _pressedValue : _releasedValue;
	}
	static void UpdateInput()
	{
		for (size_t i = 0; i < actionKey.size(); i++)
		{
			//bool _pressed = false;
			InputAction* _input = actionKey[i];
			if (/*!_pressed &&*/ KeyPressed(_input->keyInput))
			{
				//_pressed = true;
				_input->funcInvoke[0]();
			};
			//if (KeyReleased(_input.keyInput))
				//_pressed = false;
		}
	}
	template<class object, typename func, typename ...args>
	static void BindInput(int _key, object*& _object, void (func::* function)(args...), args... arg)
	{
		InputAction* _input = new InputAction();
		_input->funcInvoke = new std::function < void(void)>();
		_input->funcInvoke[0] = [&]() 
		{
			if (!_object)
			{
				std::cout << "object bind nullptr" << std::endl;
				return;
			}
			std::invoke(function, *_object, arg...); 
				std::cout << "object bind nullptr" << std::endl;
		};
		_input->keyInput = _key;
		actionKey.push_back(_input);
	}
	static std::vector<InputAction*> actionKey;
};