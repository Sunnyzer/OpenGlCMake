#include "GameObject.h"
#include "World.h"
#include "Mesh.h"
#include "Transform.h"

using namespace glm;

int GameObject::amountMonoCreate = 0;

GameObject::GameObject()
{
	name = "GameObject" + World::world->gameObjectAmount;
	transform = new Transform();
	World::world->AddObject(this);
	amountMonoBehaviour = 0;
}
GameObject::~GameObject()
{
	OnDestroy();
	OnAddMonoBehaviour = nullptr;
	delete transform;
	for (size_t i = 0; i < amountMonoBehaviour; i++)
		delete monoBehaviours[i];
}

void GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < amountMonoBehaviour; i++)
	{
		MonoBehaviour* _mono = monoBehaviours[i];
		_mono->Update(deltaTime);
	}
}

void GameObject::OnDestroy()
{
}
