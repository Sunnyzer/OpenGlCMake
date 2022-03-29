#include "GameObject.h"
#include "World.h"
#include "Mesh.h"

using namespace glm;

GameObject::GameObject()
{
	if(World::world)
		World::world->AddObject(this);
	mesh = new Mesh();
	transform = new	Transform();
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	mesh->MeshDraw();
}
