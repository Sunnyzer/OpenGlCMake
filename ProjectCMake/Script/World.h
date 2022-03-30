#pragma once
#include "GameObject.h"
#include <vector>
#include <GL\glew.h>
#include <glm\ext\matrix_transform.hpp>

typedef unsigned int GLuint;

class World
{
	friend GameObject;
public:
	~World();
	void Update(GLuint _programID, GLuint _matrixID, GLuint _textureID);

	inline glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
	inline glm::mat4 GetViewMatrix() { return viewMatrix; }
	inline GLuint GetMatrixID() { return matrixID; }

	static World* world;
protected:
	World();

	void AddObject(GameObject* _object);

	std::vector<GameObject*> objects;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	GLuint matrixID;
};