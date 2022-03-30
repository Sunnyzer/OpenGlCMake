#include "World.h"
#include <Script\WindowGL.h>
#include <Common\controls.hpp>

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
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		computeMatricesFromInputs();
		projectionMatrix = getProjectionMatrix();
		viewMatrix = getViewMatrix();
		glUseProgram(_programID);

		for (size_t i = 0; i < objects.size(); i++)
			objects[i]->Update();

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
