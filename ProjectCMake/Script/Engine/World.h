#pragma once
#include <vector>

typedef unsigned int GLuint;
class GameObject;

#define MAXFPS 60.0
#define PERIOD 1.0 / MAXFPS

class World
{
	friend GameObject;
public:
	~World();
	void GameLoop();
	inline GLuint GetMatrixID() { return matrixID; }
	static World* world;
	float GetDeltaTime() const { return deltaTime; }
protected:
	World();
	void AddObject(GameObject* _object);
	void RemoveObject(GameObject* _object);

	float deltaTime;
	GLuint matrixID;
	size_t gameObjectAmount;
	std::vector<GameObject*> objects;
};