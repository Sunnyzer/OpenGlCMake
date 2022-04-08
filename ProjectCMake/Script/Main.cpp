#include <vector>
#include "WindowGL.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <common/shader.hpp>
#include "Mesh.h"
#include "World.h"
#include <time.h>
#include "MarbleControl.h"
#include "Marble.h"

using namespace glm;

int main()
{
	srand((unsigned int)time(0));
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	WindowGL windowGL;
	windowGL.CreateWindow("Ma Game", 1920, 1080);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwSetInputMode(WindowGL::window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(WindowGL::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
	
	GameObject _pool;
	MarbleControl* _marbleControl = _pool.AddComponent<MarbleControl>();
	//Mesh* _mesh = _pool.AddComponent<Mesh>();
	//_mesh->LoadMesh("billard.obj", "Board_UV.bmp", false);
	World::world->Update(programID, MatrixID, TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
	return 0;
}