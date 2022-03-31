#include "GameObject.h"
#include "World.h"
#include "Mesh.h"
#include "Transform.h"

using namespace glm;

GameObject::GameObject()
{
	mesh = new Mesh();
	transform = new	Transform();
	mesh->SetMatrix(&transform->matrix);
	World::world->AddObject(this);
}

GameObject::~GameObject()
{
	delete mesh;
	delete transform;
}

void GameObject::Update()
{
	mesh->MeshDraw();
}

void GameObject::Test(int i)
{
	std::cout << "Test " << i << std::endl;
}
