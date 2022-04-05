#include <vector>
#include "WindowGL.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <common/shader.hpp>
#include "Mesh.h"
#include "World.h"
#include <time.h>
#include <Script\MarbleControl.h>

using namespace glm;

void SetMarble(GameObject& _bille)
{
	Mesh* _mesh = _bille.AddComponent<Mesh>();
	_mesh->LoadMesh("les2.obj", "uvmap.DDS");
	double _x = rand() % 9 + (rand() % 100) / 100.0 - 5;
	double _y = rand() % 9 + (rand() % 100) / 100.0 - 5;
	vec3 scale(0.25f);
	_bille.GetTransform()->AddPosition(vec3(_x, scale.x, _y));
	_bille.GetTransform()->SetScale(scale);
	//_bille.GetTransform()->SetRotation(rand() % 180, vec3(0,1,0));
}

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
	
	GameObject pool;
	MarbleControl* _marbleControl = pool.AddComponent<MarbleControl>();
	Mesh* _mesh = pool.AddComponent<Mesh>();
	_mesh->LoadMesh("billard.obj", "uvmap.dds");
	for (size_t i = 0; i < 10; i++)
	{
		GameObject* _marble = new GameObject();
		SetMarble(*_marble);
		_marbleControl->AddBall(_marble);
	}
	World::world->Update(programID, MatrixID, TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
	return 0;
}