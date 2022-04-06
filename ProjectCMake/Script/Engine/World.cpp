#include "World.h"
#include <iostream>
#include <GLFW\glfw3.h>
#include "Camera.h"
#include "Input.h"
#include "CollisionManager.h"

World* World::world = new World();

World::World()
{
	matrixID = 0;
}
World::~World()
{

}
void World::Update(GLuint _programID, GLuint _matrixID, GLuint _textureID)
{
	matrixID = _matrixID;
	Camera camera;
	do {
		static double lastTime = glfwGetTime();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.ComputeMatricesFromInputs();
		glUseProgram(_programID);
		for (size_t i = 0; i < objects.size(); ++i)
		{
			GameObject* _object = objects[i];
			if (!_object)continue;
			_object->Update((float)lastTime);
		}
		Input::UpdateInput();
		CollisionManager::collisionManager->UpdateCollision();
		glUniform1i(_textureID, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(WindowGL::window);
		glfwPollEvents();
	}
	while (!KeyPressed(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(WindowGL::window) == 0);
	glDeleteProgram(_programID);
}
void World::AddObject(GameObject* _object)
{
	objects.push_back(_object);
}
