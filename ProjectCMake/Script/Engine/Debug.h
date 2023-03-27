#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <imgui.h>

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

void SetColor(int _color = 37, int additionally = 1);

enum DebugType
{
	None,
	Warning,
	Error
};

struct DebugPrint
{
	DebugType debugType = DebugType::None;
	std::string debugMessage = "";
	ImVec4 color = ImVec4(0,0,0,1);

	DebugPrint(std::string _debugMessage, ImVec4 _color = ImVec4(0,0,0,1), DebugType _debugType = DebugType::None)
	{
		debugMessage = _debugMessage;
		debugType = _debugType;
		color = _color;
	}
};

static class Debug
{
public:
	~Debug()
	{
		size_t _count = debugMessages.size();
		for (size_t i = 0; i < _count; ++i)
		{
			delete debugMessages[i];
		}
		debugMessages.clear();
	}

	static void Log(const char* _message)
	{
		std::cout << _message << "\033[0m" << std::endl;
		debugMessages.push_back(new DebugPrint(_message));
	}
	static void Log(std::string _message)
	{
		std::cout << _message << "\033[0m" << std::endl;
		debugMessages.push_back(new DebugPrint(_message));
	}
	template<typename T>
	static void Log(T _object)
	{
		std::cout << _object << "\033[0m" << std::endl;
		debugMessages.push_back(new DebugPrint(std::format(_object)));
	}
	template<typename ...params>
	static void Log(std::string _debug, params... _params)
	{
		_debug = _debug + "\n";
		printf(_debug.c_str(), _params...);
		debugMessages.push_back(new DebugPrint(std::format(_debug, _params...)));
	}
	static void LogError(const char* _message)
	{
		SetColor(RED);
		Log(_message);
		SetColor(WHITE);
		debugMessages.push_back(new DebugPrint(_message, ImVec4(1, 0, 0, 1), Error));
		if (abordError)
			throw std::exception("ERROR");
	}
	static void LogError(std::string _message) 
	{
		SetColor(RED);
		Log(_message);
		SetColor(WHITE);
		debugMessages.push_back(new DebugPrint(_message, ImVec4(1,0,0,1), Error));
		if (abordError)
			throw std::exception("ERROR");
	}
	template<typename T>
	static void LogError(T _object)
	{
		SetColor(RED);
		Log(_object);
		debugMessages.push_back(new DebugPrint(std::format(_object), ImVec4(1, 0, 0, 1), DebugType::Error));
		SetColor(WHITE);
		if (abordError)
			throw std::exception("ERROR");
	}
	template<typename ...params>
	static void LogError(std::string _debug, params... _params)
	{
		SetColor(RED);
		debugMessages.push_back(new DebugPrint(std::format(_debug, _params...), ImVec4(1, 0, 0, 1), DebugType::Error));
		_debug = _debug + "\n";
		printf(_debug.c_str(), _params...);
		SetColor(WHITE);
		if (abordError)
			throw std::exception("ERROR");
	}
	static void LogWarning(std::string _message)
	{
		SetColor(YELLOW);
		Log(_message);
		SetColor(WHITE);
		debugMessages.push_back(new DebugPrint(_message, ImVec4(1, 1, 0, 1), DebugType::Warning));
		if (abordWarning)
			throw std::exception("WARNING");
	}
	static void LogWarning(const char* _message)
	{
		SetColor(YELLOW);
		Log(_message);
		SetColor(WHITE);
		debugMessages.push_back(new DebugPrint(_message, ImVec4(1, 1, 0, 1), DebugType::Warning));
		if (abordWarning)
			throw std::exception("WARNING");
	}
	template<typename T>
	static void LogWarning(T _object)
	{
		SetColor(YELLOW);
		debugMessages.push_back(new DebugPrint(std::format(_object), ImVec4(1, 1, 0, 1), DebugType::Warning));
		Log(_object, false);
		SetColor(WHITE);
		if (abordWarning)
			throw std::exception("WARNING");
	}
	template<typename ...params>
	static void LogWarning(std::string _debug, params... _params)
	{
		SetColor(YELLOW);
		debugMessages.push_back(new DebugPrint(std::format(_debug, _params...), ImVec4(1, 1, 0, 1), DebugType::Warning));
		_debug = _debug + "\n";
		printf(_debug.c_str(), _params...);
		SetColor(WHITE);
		if (abordWarning)
			throw std::exception("WARNING");
	}
	static void OnGui()
	{
		ImGui::Begin("Console");
		int _count = debugMessages.size();
		for (size_t i = 0; i < _count; ++i)
		{
			DebugPrint* _debugPrint = debugMessages[i];
			//ImGui::TextColored(_debugPrint->color, _debugPrint->debugMessage.c_str());
		}
		ImGui::End();
	}
	inline static bool abordError = false;
	inline static bool abordWarning = false;
	inline static std::vector<DebugPrint*> debugMessages;
};