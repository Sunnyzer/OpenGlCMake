#include "World.h"
#include <Common\shader.hpp>
#include <Windows.h>
#include "Physics.h"
#include "GameObject.h"
#include <TimerManager.h>
#include <Camera.h>
#include "OnlineNetwork.h"

World* World::world = new World();

World::World()
{
	matrixID = 0;
	deltaTime = 0;
	gameObjectAmount = 0;
}
World::~World()
{
	size_t i = 0;
	size_t _size = objects.size();
	for (; i < _size; ++i)
	{
		delete objects[i];
	}
	objects.clear();
}

void World::GameLoop()
{
	bool _exit = false;
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	matrixID = glGetUniformLocation(programID, "MVP");
	GLuint textureID = glGetUniformLocation(programID, "myTextureSampler");

	Input::BindInput(GLFW_KEY_ESCAPE, InputType::Pressed, [&]() { _exit = true; });
	Input::BindInput(GLFW_KEY_1, InputType::Pressed, OnlineNetwork::onlineNetwork, &OnlineNetwork::LoadClient);
	Input::BindInput(GLFW_KEY_2, InputType::Pressed, OnlineNetwork::onlineNetwork, &OnlineNetwork::LoadServer);

	Camera camera;
	double waitTime = 0;
	double lastTime = 0;
	double currentTime = 0;
	
	do 
	{
		lastTime = currentTime;
		currentTime = glfwGetTime();

		deltaTime = float(currentTime - lastTime);
		waitTime += deltaTime;
		bool _tick = waitTime >= PERIOD;

		TimerManager::UpdateTimer(deltaTime);
		glfwPollEvents();
		Input::UpdateInput();
		if (!_tick)continue;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.ComputeMatricesFromInputs(deltaTime);
		glUseProgram(programID);
		OnlineNetwork::onlineNetwork->Update();
		for (size_t i = 0; i < gameObjectAmount; ++i)
		{
			GameObject* _object = objects[i];
			_object->Update(deltaTime);
		}
		Physics::UpdatePhysics();
		glUniform1i(textureID, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(WindowGL::window);
		waitTime = 0;
	}
	while (!_exit && glfwWindowShouldClose(WindowGL::window) == 0);
	glDeleteProgram(programID);
}
void World::AddObject(GameObject* _object)
{
	objects.push_back(_object);
	++gameObjectAmount;
}

void World::RemoveObject(GameObject* _object)
{
	std::vector<GameObject*>::iterator it = objects.begin();
	for (; it != objects.end(); ++it)
	{
		if (*it != _object) continue;
		objects.erase(it);
		--gameObjectAmount;
		return;
	}
}
