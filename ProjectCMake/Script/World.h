#pragma once
#include "GameObject.h"
#include <vector>

class World
{
	friend GameObject;
public:
	~World();
	void Update();
	static World* world;
protected:
	void AddObject(GameObject* _object);
	World()
	{

	}
	std::vector<GameObject*> objects;
};