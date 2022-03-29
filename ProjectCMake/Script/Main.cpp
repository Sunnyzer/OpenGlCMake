#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <Script/Mesh.h>
#include <Script/WindowGL.h>
#include <Script/World.h>

int main()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	WindowGL windowGL;
	windowGL.CreateWindow("Ma Game", 1920, 1080);
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwSetInputMode(WindowGL::window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(WindowGL::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
	World::world->Update();
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
	return 0;
}