#pragma once
#include <vector>
#include "Collider.h"

class GameObject;
class Collider;

struct Box
{
	std::vector<Collider*> contains;
};

class OcteeTreeFils;

class QuadTree
{
public:
	QuadTree();
	~QuadTree();
	void AddObject(Collider* _collider);
	void RemoveObject(Collider* _collider);
	std::vector<Collider*> GetColliders(glm::vec3 _position);
private:
	OcteeTreeFils* quadTree;
	float offset = 5;
};

class OcteeTreeFils
{
public:
	OcteeTreeFils();
	~OcteeTreeFils();

private:
	OcteeTreeFils* fils;
	std::vector<Collider*> contains;
};

OcteeTreeFils::OcteeTreeFils()
{
}

OcteeTreeFils::~OcteeTreeFils()
{
}