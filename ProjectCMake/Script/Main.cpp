#include "WindowGL.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Mesh.h"
#include "World.h"
#include "MarbleControl.h"
#include "ENet.h"
#include <time.h>
#include "GameObject.h"
#include "Transform.h"

using namespace glm;

int main()
{
	srand((unsigned int)time(0));
	
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		char _r = getchar();
		return -1;
	}
	WindowGL windowGL;
	windowGL.CreateMyWindow("Ma Game", 1080, 720);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		char _r = getchar();
		glfwTerminate();
		return -1;
	}

	ENet::Initialize();

	glfwSetInputMode(WindowGL::window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(WindowGL::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GameObject _pool;
	_pool.GetTransform()->SetPosition(vec3(0, -0.5f, 0));
	MarbleControl* _marbleControl = _pool.AddComponent<MarbleControl>();
	Mesh* _mesh = _pool.AddComponent<Mesh>();
	_mesh->LoadMesh("billard.obj", "Board_UV.bmp", false);
	World::world->Update();
	
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
	return 0;
}