#include <iostream>
#include <source_location>
#include <string>

#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37
#define RESET 0
#define BOLDBRIGHT 1
#define UNDERLINE 4
#define INVERSE 7
#define BOLDBRIGHTOFF 21
#define UNDERLINEOFF 24
#define INVERSEOFF 27

class DebugException : std::exception
{
public:
	DebugException(const char* _msg, const std::source_location _location = std::source_location::current())
	{

	}
};

void SetColor(int _color = 37, int additionally = 1);

static class Debug
{
public:
	template<typename T>
	static void Log(T _object, int _color = WHITE, int additionally = BOLDBRIGHT)
	{
		SetColor(_color, additionally);
		std::cout << _object << "\033[0m" << std::endl;
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
		Log(_object, RED);
		if (abordError)
			throw std::exception("FINIE LE YOUEN");
	}
	template<typename ...params>
	static void LogError(std::string _debug, params... _params)
	{
		SetColor(RED);
		_debug = _debug + "\n";
		printf(_debug.c_str(), _params...);
		SetColor(WHITE);
		if (abordError)
			throw std::exception("FINIE LE YOUEN");
	}
	template<typename T>
	static void LogWarning(T _object)
	{
		Log(_object, YELLOW);
		if (abordWarning)
			throw DebugException("");
	}
	template<typename ...params>
	static void LogWarning(std::string _debug, params... _params)
	{
		SetColor(YELLOW);
		_debug = _debug + "\n";
		printf(_debug.c_str(), _params...);
		SetColor(WHITE);
		if (abordWarning)
			throw DebugException("");
	}
	static bool abordError;
	static bool abordWarning;
};