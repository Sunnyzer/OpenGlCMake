#pragma once
#include <GL\glew.h>
#include <vector>
#include "GameObject.h"
#include "ServerENet.h"
#include "ClientENet.h"
#include <glm\ext\matrix_transform.hpp>
#include "../Action.h"

typedef unsigned int GLuint;

class World
{
	friend GameObject;
public:
	~World();
	void Update();
	inline GLuint GetMatrixID() { return matrixID; }
	static World* world;
	static ENet* networkLayer;
	float deltaTime;
	Action<> OnNetworkSet;
protected:
	World();
	void AddObject(GameObject* _object);
	void RemoveObject(GameObject* _object);
	std::vector<GameObject*> objects;
	GLuint matrixID;
	size_t gameObjectAmount;
};