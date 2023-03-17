#pragma once
#include <vector>
#include <functional>

class TimerManager
{
public:
	struct Timer
	{
	public:
		bool haveExecuteStart = false;
		float startTime = 0;
		float duration = 0;
		float time = 0;
		bool repeat = false;
		std::function<void()> funcInvoke;
	};
	~TimerManager()
	{
		size_t _size = actionKey.size();
		for (size_t i = 0; i < _size; ++i)
		{
			delete actionKey[i];
		}
		actionKey.clear();
	}
	static void UpdateTimer(float _deltaTime)
	{
		for (size_t i = 0; i < size; ++i)
		{
			Timer* _timer = actionKey[i];
			_timer->time += _deltaTime;
			//bool _execute = _timer->haveExecuteStart ? _timer->time >= _timer->duration : _timer->time >= _timer->startTime;
			bool _execute = _timer->time >= (_timer->haveExecuteStart ? _timer->duration : _timer->startTime);
			if (!_execute)continue;
			_timer->funcInvoke();
			_timer->time = 0;
			_timer->haveExecuteStart = true;
			if (_timer->repeat)continue;
			RemoveTimer(_timer);
		}
	}
	template<class object,typename ...args>
	static void SetTimer(float _startTime, float _duration, bool _repeat, object* _object, void (object:: *function)(args...), args... arg)
	{
		Timer* _timer = new Timer();
		_timer->duration = _duration;
		_timer->repeat = _repeat;
		_timer->startTime = _startTime;
		std::function<void(void)> _func = [_object, function, arg...]()
		{
			std::invoke(_object,function, arg...);
		};
		_timer->funcInvoke = _func;
		actionKey.push_back(_timer);
		++size;
	}
	static void SetTimer(float _startTime, float _duration, bool _repeat, std::function<void(void)> _function)
	{
		Timer* _timer = new Timer();
		_timer->duration = _duration;
		_timer->repeat = _repeat;
		_timer->startTime = _startTime;
		_timer->funcInvoke = _function;
		actionKey.push_back(_timer);
		++size;
	}
	static void RemoveTimer(Timer* _timer)
	{
		std::vector<Timer*>::iterator it = actionKey.begin();
		for (; it != actionKey.end(); ++it)
		{
			if (*it != _timer)continue;
			Timer* _timer = *it;
			actionKey.erase(it);
			delete _timer;
			--size;
			return;
		}
	}
private:
	static std::vector<Timer*> actionKey;
	static size_t size;
};