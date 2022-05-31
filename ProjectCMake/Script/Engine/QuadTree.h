#pragma once
#include <vector>
#include "Collider.h"

class GameObject;
class Collider;

struct Box
{
	std::vector<Collider*> contains;
};

class QuadTree
{
public:
	QuadTree();
	~QuadTree();
	void AddObject(Collider* _collider);
	void RemoveObject(Collider* _collider);
	std::vector<Collider*> GetColliders(glm::vec3 _position);
private:
	Box quadTree[100][100][100];
	float offset = 5;
};
