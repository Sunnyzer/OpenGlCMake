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
	inline GLuint GetMatrixID() { return matrixID; }
	static World* world;
	float deltaTime;
protected:
	World();
	void AddObject(GameObject* _object);
	std::vector<GameObject*> objects;
	GLuint matrixID;
};