#include "GameObject.h"
#include "World.h"
#include "Mesh.h"
#include "Transform.h"

using namespace glm;

GameObject::GameObject()
{
	transform = new	Transform();
	World::world->AddObject(this);
	amountMonoBehaviour = 0;
}

GameObject::~GameObject()
{
	OnDestroy();
	delete transform;
}

void GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < amountMonoBehaviour; i++)
	{
		MonoBehaviour* _mono = monoBehaviours[i];
		if (!_mono)continue;
		_mono->Update(deltaTime);
	}
}

void GameObject::OnDestroy()
{
}
