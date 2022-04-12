#pragma once
#include "GameObject.h"
#include <vector>
#include <GL\glew.h>
#include <glm\ext\matrix_transform.hpp>
#include "ClientENet.h"
#include "ServerENet.h"
#include "../Action.h"

typedef unsigned int GLuint;

class World
{
	friend GameObject;
public:
	~World();
	void Update(GLuint _programID, GLuint _matrixID, GLuint _textureID);
	inline GLuint GetMatrixID() { return matrixID; }
	static World* world;
	static ENet* networkLayer;
	float deltaTime;
	Action<> OnNetworkSet;
protected:
	World();
	void AddObject(GameObject* _object);
	std::vector<GameObject*> objects;
	GLuint matrixID;
};