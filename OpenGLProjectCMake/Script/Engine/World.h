#pragma once
#include <vector>
#include <string>

typedef unsigned int GLuint;
class GameObject;

#define MAXFPS 120.0
#define PERIOD 1.0 / MAXFPS

class World
{
	friend GameObject;
public:
	~World();
	void GameLoop();
	void DetailsWindow();
	void SceneWindow();
	inline GLuint GetMatrixID() { return matrixID; }
	static World* world;
	float GetDeltaTime() const { return deltaTime; }
	void ResetObjectSelect(GameObject* _object);
	void SelectObject(GameObject* _object);
protected:
	World();
	void AddObject(GameObject* _object);
	void RemoveObject(GameObject* _object);
	void Render();
	float deltaTime;
	int currentSelected = 0;
	GLuint matrixID;
	size_t gameObjectAmount;
	std::vector<GameObject*> objects;
	GameObject* gameObjectSelect = nullptr;
	std::string gameObjectName;
};