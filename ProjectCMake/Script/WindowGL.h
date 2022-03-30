#pragma once

class GLFWwindow;

class WindowGL
{
public:
	WindowGL();
	bool CreateWindow(const char* _name,int _width,int _height);
	inline static int GetWidth() { return width; }
	inline static int GetHeight() { return height; }
	static GLFWwindow* window;
private:
	static int width;
	static int height;
};