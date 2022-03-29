#include "World.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Script\WindowGL.h>
#include <Script\Mesh.h>
#include <Common\shader.hpp>
#include <Common\controls.hpp>

World* World::world = new World();

World::~World()
{
	
}

void World::Update()
{
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		for (size_t i = 0; i < objects.size(); i++)
			objects[i]->Update();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glfwSwapBuffers(WindowGL::window);
		glfwPollEvents();
	}
	while (!KeyPressed(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(WindowGL::window) == 0);
}

void World::AddObject(GameObject* _object)
{
	objects.push_back(_object);
}
