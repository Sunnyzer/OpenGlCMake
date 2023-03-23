#include "GameObject.h"
#include "World.h"
#include "Mesh.h"
#include "imgui.h"

using namespace glm;

GameObject::GameObject()
{
	std::string _test = "GameObject " + std::to_string(World::world->gameObjectAmount);
	name = _test;
	transform = new Transform();
	World::world->AddObject(this);
	amountMonoBehaviour = 0;
}
GameObject::~GameObject()
{
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

void GameObject::OnGUI()
{
	ImGui::InputText(name.c_str(), name.data(), 25);
	for (size_t i = 0; i < amountMonoBehaviour; ++i)
	{
		MonoBehaviour* _mono = monoBehaviours[i];
		_mono->OnGUI();
	}
}

void GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < amountMonoBehaviour; ++i)
	{
		MonoBehaviour* _mono = monoBehaviours[i];
		_mono->Update(deltaTime);
	}
}
