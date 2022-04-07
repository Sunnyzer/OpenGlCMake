#include "Mesh.h"
#include "MarbleControl.h"
#include "Input.h"
#include "MovementMarble.h"
#include "GameObject.h"
#include "Marble.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Camera.h"
#include "BoxCollider.h"

using namespace glm;

MarbleControl::MarbleControl()
{
	currentIndex = 0;
	whiteMarble = nullptr;
}

void MarbleControl::Start()
{
	//Input::BindInput(GLFW_KEY_V, this, &MarbleControl::ChangeBall);
	Input::BindInput(GLFW_KEY_SPACE, this, &MarbleControl::Shoot);
	glm::vec3 _scale(0.25);
	glm::vec3 _basePos(1 , _scale.y, 0);
	whiteMarble = GameObject::Instanciate<Marble>();
	whiteMarble->gameObject->GetTransform()->SetScale(_scale);
	whiteMarble->gameObject->GetTransform()->SetPosition(_basePos +  vec3(-5,0,0));
	Marble* _marble = GameObject::Instanciate<Marble>();
	_marble->gameObject->GetTransform()->SetScale(_scale);
	_marble->gameObject->GetTransform()->SetPosition(_basePos);
	AddBall(_marble);
	for (size_t i = 2; i < 6; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			Marble* _marble = GameObject::Instanciate<Marble>();
			_marble->gameObject->GetTransform()->SetScale(_scale);
			_marble->gameObject->GetTransform()->SetPosition(_basePos + vec3((i-2) * 0.5 + 0.5, 0, ((i-1) * -0.25) + 0.5 * j));
			AddBall(_marble);
		}
	}
	BoxCollider* _boxCollider = GameObject::Instanciate<BoxCollider>();
	Mesh* _mesh = _boxCollider->gameObject->AddComponent<Mesh>();
	_mesh->LoadMesh("cube.obj","uvmap.DDS");
	_boxCollider->gameObject->GetTransform()->SetScale(vec3(1, 1, 1));
	_boxCollider->gameObject->GetTransform()->SetPosition(vec3(15.0f, 0, 0));
	/*BoxCollider* _boxCollider1 = GameObject::Instanciate<BoxCollider>();
	_boxCollider1->gameObject->GetTransform()->SetScale(vec3(1,1,10));
	BoxCollider* _boxCollider2 = GameObject::Instanciate<BoxCollider>();
	_boxCollider2->gameObject->GetTransform()->SetScale(vec3(10,1,1));
	BoxCollider* _boxCollider3 = GameObject::Instanciate<BoxCollider>();
	_boxCollider3->gameObject->GetTransform()->SetScale(vec3(10,1,1));*/
}

void MarbleControl::Update(float deltaTime)
{

	/*MovementMarble movement;
	double _sprintValue = Input::FlipFlop<double>(GLFW_KEY_LEFT_SHIFT, 5.0f, 1.0f);
	if (!marbles[currentIndex])return;
	movement.InputMovement(marbles[currentIndex]->gameObject, (deltaTime/ 10.0) * _sprintValue);*/
}


void MarbleControl::ChangeBall()
{
	++currentIndex;
	if (currentIndex >= marbles.size())
		currentIndex = 0;
}

void MarbleControl::AddBall(Marble* _object)
{
	marbles.push_back(_object);
}

void MarbleControl::Shoot()
{
	vec3 _impulse = normalize(vec3(Camera::forward.x, 0, Camera::forward.z));
	whiteMarble->GetRididBody()->AddImpulse(vec3(_impulse.x, 0, _impulse.z));
}
