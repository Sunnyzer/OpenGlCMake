#pragma once
#include <vector>
#include <functional>

template<typename ...args>
class Action
{
public:
	template<class object>
	void Add(object*& _object, void (object::*func)(args...))
	{
		std::function<void(args...)> _func([&_object, func](args... _args)
		{
			std::invoke(func, _object, _args...);
		});
		actions.push_back(_func);
	}
	template<class object>
	void Add(object* _object, void (object::* func)(args...))
	{
		std::function<void(args...)> _func([_object, func](args... _args)
		{
			std::invoke(func, _object, _args...);
		});
		actions.push_back(_func);
	}
	void operator +=(std::function<void(args...)> _add)
	{
		actions.push_back(_add);
	}
	void operator -=(std::function<void(args...)> _remove)
	{
		size_t _size = actions.size();
		typename std::vector<std::function<void(args...)>>::iterator it;
		for (it = actions.begin(); it != actions.end(); it++)
		{
			const type_info& func1 = _remove.target_type();
			const type_info& func2 = (*it).target_type();
			if(func1 == func2)
			{
				actions.erase(it);
				return;
			}
		}
	}
	void operator  =(Action<args...>* _action)
	{
		if (!_action)
		{
			size_t _size = actions.size();
			for (size_t i = 0; i < _size; i++)
			{
				actions.pop_back();
			}
		}
			return;
		*this = *_action;
	}
	void Invoke(args ...ar)
	{
		size_t _size = actions.size();
		for (size_t i = 0; i < _size; i++)
		{
			actions[i](ar...);
		}
	}
private:
	std::vector<std::function<void(args...)>> actions;
};

