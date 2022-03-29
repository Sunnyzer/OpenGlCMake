#pragma once
#include "GameObject.h"
#include <vector>

class World
{
public:
	~World();
	void Update();
	static World* world;
private:
	World()
	{

	}
	std::vector<GameObject*> objects;
};