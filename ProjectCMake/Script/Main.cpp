#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <common/shader.hpp>

#include "Mesh.h"
#include "WindowGL.h"
#include "World.h"
#include <time.h>

using namespace glm;

void SetBille(GameObject& _bille)
{
	_bille.GetMesh()->LoadMesh("les2.obj", "uvmap.DDS");
	float _x = rand() % 10 + (rand() % 100) / 100.0 - 5;
	float _y = rand() % 10 + (rand() % 100) / 100.0 - 5;
	vec3 scale(0.25f);
	_bille.GetTransform()->SetPosition(vec3(_x, scale.x, _y));
	_bille.GetTransform()->SetScale(scale);
	_bille.GetTransform()->SetRotation(rand() % 180, vec3(0,1,0));
}

int main()
{
	srand(time(0));
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
	
	GameObject billard;
	/*GameObject bille;
	GameObject bille1;
	GameObject bille2;
	GameObject bille3;*/

	billard.GetMesh()->LoadMesh("billard.obj", "Oui.DDS");
	for (size_t i = 0; i < 10; i++)
	{
		GameObject* bille = new	GameObject();
		SetBille(*bille);
	}
	/*}
	SetBille(bille1);
	SetBille(bille2);
	SetBille(bille3);*/
	
	World::world->Update(programID, MatrixID, TextureID);
	
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
	return 0;
}