#pragma once
#include <vector>

template<typename ...args>
class Action
{
	typedef void(*action)(...);
public:
	Action()
	{

	}
	void operator +=(action _action)
	{
		actions.push_back(_action);
	}
	void operator -=(action _action)
	{
		std::vector<action>::iterator end = actions.end();
		for (std::vector<action>::iterator it = actions.begin(); it < end; it++)
		{
			if (*it == _action)
			{
				actions.erase(it);
				return;
			}
		}
	}
	void Invoke(args ...ar)
	{
		int _size = actions.size();
		for (size_t i = 0; i < _size; i++)
		{
			actions[i](ar...);
		}
	}
private:
	std::vector<action> actions;
};