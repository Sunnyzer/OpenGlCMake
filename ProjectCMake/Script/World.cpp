#include "World.h"
#include <iostream>
#include "Camera.h"
#include "MovementMarble.h"
#include <GLFW\glfw3.h>
#include "Input.h"
#include <functional>


World* World::world = new World();

World::World()
{
	viewMatrix = glm::mat4(1);
	projectionMatrix = glm::mat4(1);
	matrixID = 0;
}

World::~World()
{

}

void World::Update(GLuint _programID, GLuint _matrixID, GLuint _textureID)
{
	matrixID = _matrixID;
	int _i = 1;
	bool _pressed = false;
	Camera camera;
	MovementMarble movement;
	do {
		static double lastTime = glfwGetTime();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.ComputeMatricesFromInputs();
		projectionMatrix = camera.GetProjectionMatrix();
		viewMatrix = camera.GetViewMatrix();
		glUseProgram(_programID);

		for (size_t i = 0; i < objects.size(); ++i)
			objects[i]->Update();

		movement.InputMovement(objects[_i], (lastTime/10.0f) * Input::FlipFlop(GLFW_KEY_LEFT_SHIFT, 5.0f, 1.0f));//glfwGetKey(WindowGL::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 5 : 1)
		Input::UseKey(GLFW_KEY_SPACE, objects[0], &GameObject::Test, 5);
		if (!_pressed && KeyPressed(GLFW_KEY_SPACE))
		{  
			_pressed = true;
			++_i;
			if (_i >= objects.size())
				_i = 1;
		}
		if (!KeyPressed(GLFW_KEY_SPACE))
		{
			_pressed = false;
		}
		glUniform1i(_textureID, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(WindowGL::window);
		glfwPollEvents();
	}
	while (!KeyPressed(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(WindowGL::window) == 0);
	std::function<void(void)> lambda = [&]() { std::invoke(&GameObject::Test, objects[0], 5); };
	std::vector<std::function<void(void)>> actionKey;
	actionKey.push_back(lambda);
	glDeleteProgram(_programID);
}

void World::AddObject(GameObject* _object)
{
	objects.push_back(_object);
}
