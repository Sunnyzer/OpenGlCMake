#include "World.h"
#include <Common\shader.hpp>
#include "Physics.h"
#include "GameObject.h"

#define MAXFPS 60.0

World* World::world = new World();
ENet* World::networkLayer = nullptr;

World::World()
{
	matrixID = 0;
	deltaTime = 0;
	gameObjectAmount = 0;
}
World::~World()
{
	if(networkLayer)
		delete networkLayer;
	for (size_t i = 0; i < gameObjectAmount; i++)
		delete objects[i];
}

void World::Update()
{
	bool _exit = false;
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	matrixID = glGetUniformLocation(programID, "MVP");
	GLuint textureID = glGetUniformLocation(programID, "myTextureSampler");
	Input::BindInput(GLFW_KEY_1, InputType::Pressed, [this]() { networkLayer = new ClientENet("127.0.0.1", 1234); OnNetworkSet.Invoke(); });
	Input::BindInput(GLFW_KEY_2, InputType::Pressed, [this]() { networkLayer = new ServerENet(1234); OnNetworkSet.Invoke(); });
	Input::BindInput(GLFW_KEY_ESCAPE, InputType::Pressed, [&]() { _exit = true; });
	double period = 1.0 / MAXFPS;
	Camera camera;
	do {
		double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.ComputeMatricesFromInputs();
		glUseProgram(programID);
		if (networkLayer) networkLayer->Update();
		for (size_t i = 0; i < gameObjectAmount; ++i)
		{
			GameObject* _object = objects[i];
			_object->Update(deltaTime);
		}
		Input::UpdateInput();
		Physics::UpdatePhysics();
		glUniform1i(textureID, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(WindowGL::window);
		glfwPollEvents();
		if(period > deltaTime)
			Sleep(DWORD((period - deltaTime) * 1000.0));
	}
	while (!_exit && glfwWindowShouldClose(WindowGL::window) == 0);
	glDeleteProgram(programID);
}
void World::AddObject(GameObject* _object)
{
	objects.push_back(_object);
	gameObjectAmount++;
}

void World::RemoveObject(GameObject* _object)
{
}
