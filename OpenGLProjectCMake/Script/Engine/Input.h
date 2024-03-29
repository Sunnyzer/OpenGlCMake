#pragma once
#include "WindowGL.h"
#include <vector>
#include <functional>
#include <GLFW\glfw3.h>
#include <Action.h>

#define KeyPressed(glfwKey) \
glfwKey >= 32 ? glfwGetKey(WindowGL::window, glfwKey) == GLFW_PRESS : glfwGetMouseButton(WindowGL::window, glfwKey) == GLFW_PRESS \

#define KeyReleased(glfwKey) \
glfwKey >= 32 ? glfwGetKey(WindowGL::window, glfwKey) == GLFW_RELEASE : glfwGetMouseButton(WindowGL::window, glfwKey) == GLFW_RELEASE \

enum class InputType
{
	Pressed,
	Released,
	Repeat
};

class Input
{
private:
	struct InputAction
	{
	public:
		int keyInput = 0;
		std::function<void(void)> funcInvoke;
		bool pressed = false;
		InputType inputType = InputType::Pressed;
	};
public:
	~Input()
	{
		//for (size_t i = 0; i < actionKey.size(); ++i)
		//	delete actionKey[i];
		actionKey.clear();
	}
	template<class T>
	static T FlipFlop(int _key, T _pressedValue, T _releasedValue)
	{
		return KeyPressed(_key) ? _pressedValue : _releasedValue;
	}
	static void UpdateInput()
	{
		glfwPollEvents();
		for (size_t i = 0; i < size; ++i)
		{
			InputAction* _input = &actionKey[i];
			switch (_input->inputType)
			{
			case InputType::Pressed:
				if (KeyPressed(_input->keyInput) && _input->pressed == false)
				{
					_input->pressed = true;
					_input->funcInvoke();
				}
				else if (KeyReleased(_input->keyInput))
				{
					_input->pressed = false;
				}
				break;
			case InputType::Released:
				if (KeyReleased(_input->keyInput) && _input->pressed == true)
				{
					_input->pressed = false;
					_input->funcInvoke();
				}
				else if (!_input->pressed && KeyPressed(_input->keyInput))
				{
					_input->pressed = true;
				}
				break;
			case InputType::Repeat:
				if (_input->pressed || KeyPressed(_input->keyInput))
				{
					_input->pressed = true;
					_input->funcInvoke();
				}
				if (KeyReleased(_input->keyInput))
				{
					_input->pressed = false;
				}
				break;
			}
		}
	}
	template<class object, typename ...args>
	static void BindInput(int _key, InputType _inputType, object* _object, void (object::* function)(args...), args... arg)
	{
		InputAction _input;
		_input.keyInput = _key;
		_input.inputType = _inputType;
		_input.funcInvoke = std::function<void(void)>([_object, function, arg...]()
		{
			std::invoke(function, _object, arg...);
		});
		actionKey.push_back(_input);
		++size;
	}
	template<typename ...args>
	static void BindInput(int _key, InputType _inputType, std::function<void(void)> _add, args... arg)
	{
		InputAction _input;
		_input.keyInput = _key;
		_input.inputType = _inputType;
		_input.funcInvoke = std::function<void(void)>([_add, arg...]()
		{
			_add(arg...);
		});
		actionKey.push_back(_input);
		++size;
	}
private:
	static std::vector<InputAction> actionKey;
	static size_t size;
};