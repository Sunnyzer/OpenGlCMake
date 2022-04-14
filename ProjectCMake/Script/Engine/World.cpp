#include "World.h"
#include <iostream>
#include <GLFW\glfw3.h>
#include "Camera.h"
#include "Input.h"
#include "CollisionManager.h"

#define MAXFPS 60.0

World* World::world = new World();
ENet* World::networkLayer = nullptr;

World::World()
{
	matrixID = 0;
	deltaTime = 0;
}
World::~World()
{
	size_t _size = objects.size();
	for (size_t i = 0; i < _size; i++)
		delete objects[i];
}
void World::Update(GLuint _programID, GLuint _matrixID, GLuint _textureID)
{
	Input::BindInput(GLFW_KEY_1, [this]() { networkLayer = new ClientENet("192.168.10.69", 1234); OnNetworkSet.Invoke(); });
	Input::BindInput(GLFW_KEY_2, [this]() { networkLayer = new ServerENet(1234); OnNetworkSet.Invoke(); });
	matrixID = _matrixID;
	double period = 1.0 / MAXFPS;
	Camera camera;
	do {
		double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.ComputeMatricesFromInputs();
		glUseProgram(_programID);
		for (size_t i = 0; i < objects.size(); ++i)
		{
			GameObject* _object = objects[i];
			if (!_object)continue;
			_object->Update(deltaTime);
		}
		Input::UpdateInput();
		CollisionManager::collisionManager->UpdateCollision();
		if (networkLayer) networkLayer->Update();
		glUniform1i(_textureID, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(WindowGL::window);
		glfwPollEvents();
		if(period > deltaTime)
			Sleep((period - deltaTime) * 1000.0);
	}
	while (!KeyPressed(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(WindowGL::window) == 0);
	glDeleteProgram(_programID);
}
void World::AddObject(GameObject* _object)
{
	objects.push_back(_object);
}
