#pragma once
#include <vector>
#include <functional>

class MonoBehaviour;

template<typename ...args>
struct Delegate
{
public:
	void* adressFunc;
	virtual void Invoke(args ...params)
	{}
};

template<typename ...args>
struct StaticDelegate : public Delegate<args...>
{
	typedef void (*Func)(args...);
public:
	Func func;
	StaticDelegate(Func _func)
	{
		func = _func;
		adressFunc = (void*&)func;
	}
	void Invoke(args ...params) override
	{
		func(params...);
	}
};

template<class Class, typename ...args>
struct ConstDelegate : public Delegate<args...>
{
	typedef void (Class::*Func)(args...) const;
public:
	Class* owner;
	Func func;
	ConstDelegate(Class* _owner, Func _func)
	{
		owner = _owner;
		func = _func;
		adressFunc = (void*&)func;
	}
	void Invoke(args ...params) override
	{
		if (!owner) return;
		(owner->*func)(params...);
	}
};

template<class Class, typename ...args>
struct MethodDelegate : public Delegate<args...>
{
	typedef void (Class::*Func)(args...);
public:
	Class* owner;
	Func func;
	MethodDelegate(Class* _owner, Func _func)
	{
		owner = _owner;
		func = _func;
		adressFunc = (void*&)func;
	}
	void Invoke(args ...params) override
	{
		if (!owner)return;
		(owner->*func)(params...);
	}
};

template<class Class, typename ...args>
struct FunctionDelegate : public Delegate<args...>
{
public:
	Class* owner;
	std::function<void(args...)> func;

	FunctionDelegate(Class* _owner, std::function<void(args...)> _func)
	{
		owner = _owner;
		func = _func;
		adressFunc = (void*&)func;
	}
	void Invoke(args ...params) override
	{
		if (!owner)return;
		func(params...);
	}
};

template<typename ...args>
class Action
{
public:
	~Action()
	{
		Clear();
	}
	template<class object>
	void Add(object* _object, void (object::*func)(args...))
	{
		delegates.push_back(new MethodDelegate<object, args...>(_object, func));
	}
	template<class object>
	void Add(object* _object, void (object::*func)(args...) const)
	{
		delegates.push_back(new ConstDelegate<object, args...>(_object, func));
	}
	template<class object>
	void Add(object* _object, std::function<void(args...)> func)
	{
		delegates.push_back(new FunctionDelegate<object, args...>(_object, func));
	}
	void Add(void (*func)(args...))
	{
		delegates.push_back(new StaticDelegate<args...>(func));
	}
	template<class object>
	void Remove(object* _object, void (object::*func)(args...))
	{
		std::vector<Delegate<args...>*>::iterator it;
		for (it = delegates.begin(); it != delegates.end(); ++it)
		{
			if((*it)->adressFunc == (void*&)func)
			{
				Delegate<args...>* _delegate = *it;
				delegates.erase(it);
				delete _delegate;
				return;	
			}
		}
	}
	void Clear()
	{
		size_t _size = delegates.size();
		for (int i = 0; i < _size; ++i)
		{
			delete delegates[i];
		}
		delegates.clear();
	}
	void Invoke(args ...ar)
	{
		size_t _size = delegates.size();
		for (size_t i = 0; i < _size; ++i)
			delegates[i]->Invoke(ar...);
	}
private:
	std::vector<Delegate<args...>*> delegates; 
};