#include "Debug.h"

bool Debug::abordError = false;
bool Debug::abordWarning = false;

void SetColor(int _color, int additionally)
{
	std::string _colorText = "\033[";
	_colorText.append(std::to_string(additionally > 27 ? additionally + 10 : additionally));
	_colorText.append(";");
	_colorText.append(std::to_string(_color));
	_colorText += "m";
	std::cout << _colorText;
}