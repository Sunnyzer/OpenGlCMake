#include "GameObject.h"
#include "World.h"
#include "Mesh.h"

using namespace glm;

int GameObject::amountMonoCreate = 0;

GameObject::GameObject()
{
	name = "GameObject " + World::world->gameObjectAmount;
	transform = new Transform();
	World::world->AddObject(this);
	amountMonoBehaviour = 0;
}
GameObject::~GameObject()
{
	OnDestroy();
	OnAddMonoBehaviour.Clear();
	delete transform;
	for (size_t i = 0; i < amountMonoBehaviour; ++i)
		delete monoBehaviours[i];
	monoBehaviours.clear();
}

void GameObject::Destroy(GameObject* _gameObject)
{
	if (!_gameObject) return;
	World::world->RemoveObject(_gameObject);
	delete _gameObject;
}

void GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < amountMonoBehaviour; ++i)
	{
		MonoBehaviour* _mono = monoBehaviours[i];
		_mono->Update(deltaTime);
	}
}

void GameObject::OnDestroy()
{
}
