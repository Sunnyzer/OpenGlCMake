#include "GameObject.h"
#include "World.h"
#include "Mesh.h"
#include "imgui.h"

using namespace glm;

GameObject::GameObject()
{
	name = "GameObject " + std::to_string(World::world->gameObjectAmount);
	transform = new Transform();
	World::world->AddObject(this);
	amountMonoBehaviour = 0;
}

GameObject::GameObject(std::string _name)
{
	name = std::string(_name);
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
	_gameObject->OnDestroy.Invoke(_gameObject);
	delete _gameObject;
}

void GameObject::OnGUI()
{
	float p[3] = { transform->position.x, transform->position.y, transform->position.z };
	float r[3] = { transform->rotation.x, transform->rotation.y, transform->rotation.z };
	float s[3] = { transform->scale.x, transform->scale.y, transform->scale.z };
	std::string _name = name + "##1";
	ImGui::InputText(_name.c_str(), name.data(), 25);
	ImGui::Text("Position : ");
	ImGui::SameLine();
	ImGui::DragFloat3("##gameObjectPosition", p);

	ImGui::Text("Rotation : ");
	ImGui::SameLine();
	ImGui::DragFloat3("##gameObjectRotation", r);

	ImGui::Text("Scale : ");
	ImGui::SameLine();
	ImGui::DragFloat3("##gameObjectScale", s);

	transform->SetPosition(glm::vec3(p[0], p[1], p[2]));
	transform->SetRotation(glm::vec3(r[0], r[1], r[2]));
	transform->SetScale(glm::vec3(s[0], s[1], s[2]));
	for (size_t i = 0; i < amountMonoBehaviour; ++i)
	{
		MonoBehaviour* _mono = monoBehaviours[i];
		ImGui::SeparatorText(_mono->name.c_str());
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
