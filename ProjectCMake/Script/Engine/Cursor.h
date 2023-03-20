#include <iostream>
#include <glm/ext/vector_float2.hpp>

static class Cursor
{
public:
	static void Enable();
	static void Disable();
	static void Lock();
	static glm::vec2 GetCursorPosition();
};