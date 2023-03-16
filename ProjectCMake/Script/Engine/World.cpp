#include "World.h"
#include <Common\shader.hpp>
#include "Physics.h"
#include "GameObject.h"
#include "OnlineNetwork.h"
#include <Windows.h>
#include <iostream>


#define NK_ZERO_COMMAND_MEMORY
#define NK_IMPLEMENTATION
#include <external/glfw-3.3.2/deps/nuklear.h>
#include <external/glfw-3.3.2/deps/nuklear_glfw_gl2.h>

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
		GameObject* _gameObject = objects[i];
		objects[i] = nullptr;
		delete _gameObject;
	}
	objects.clear();
}

void World::Update()
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

		if (_tick)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			camera.ComputeMatricesFromInputs(deltaTime);
			glUseProgram(programID);
			OnlineNetwork::onlineNetwork->Update();
			for (size_t i = 0; i < gameObjectAmount; ++i)
			{
				GameObject* _object = objects[i];
				_object->Update(deltaTime);
			}
		}
		TimerManager::UpdateTimer(deltaTime);
		glfwPollEvents();
		Input::UpdateInput();

		if (_tick)
		{
			Physics::UpdatePhysics();
			glUniform1i(textureID, 0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glfwSwapBuffers(WindowGL::window);
			waitTime = 0;
		}
		//lastTime = glfwGetTime();
		//if(period > deltaTime)
		//	Sleep(DWORD((period - deltaTime) * 1000.0));
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
	std::vector<GameObject*>::iterator it = objects.begin();
	for (; it != objects.end(); ++it)
	{
		if (*it != _object) continue;
		objects.erase(it);
		--gameObjectAmount;
		return;
	}
}
