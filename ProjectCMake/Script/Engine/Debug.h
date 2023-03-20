#include <iostream>
#include <source_location>
#include <stdio.h>
#include <stdarg.h>
#include <stdexcept>

class DebugException : std::exception
{
public:
	DebugException(const char* _msg/*, const std::source_location _location = std::source_location::current()*/)
	{

	}
};

static class Debug
{
public:
	template<typename T>
	static void Log(T _object)
	{
		std::cout << _object << std::endl;
	}
	template<typename ...params>
	static void Log(std::string _debug, params... _params)
	{
		_debug = _debug + "\n";
		printf(_debug.c_str(), _params...);
	}
	template<typename T>
	static void LogError(T _object)
	{
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		Log(_object);
		//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		if (abordError)
			throw nullptr;
	}
	template<typename ...params>
	static void LogError(std::string _debug, params... _params)
	{
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		Log(_debug, _params);
		//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		if (abordError)
			throw nullptr;
	}
	template<typename T>
	static void LogWarning(T _object)
	{
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		Log(_object);
		//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		if (abordWarning)
			throw nullptr;
	}
	template<typename ...params>
	static void LogWarning(std::string _debug, params... _params)
	{
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		Log(_debug, _params);
		//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		if (abordWarning)
			throw nullptr;
	}
	static bool abordError;
	static bool abordWarning;
};