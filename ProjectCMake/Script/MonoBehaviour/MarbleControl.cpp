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
#include "World.h"
#include "json.hpp"

using namespace glm;
using json::JSON;

MarbleControl::MarbleControl()
{
	currentIndex = 0;
	whiteMarble = nullptr;
}

void MarbleControl::Start()
{
	Input::BindInput(GLFW_KEY_SPACE, this, &MarbleControl::Shoot);
	glm::vec3 _scale(0.75);
	glm::vec3 _basePos(1, _scale.y, 0);
	whiteMarble = GameObject::Instanciate<Marble>();
	whiteMarble->gameObject->GetTransform()->SetScale(_scale);
	whiteMarble->gameObject->GetTransform()->SetPosition(_basePos + vec3(-10, 0, 0));
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
			_marble->gameObject->GetTransform()->SetPosition(_basePos + vec3((i - 2) * _scale.y * 2 + _scale.y * 2, 0, ((i - 1) * -_scale.y) + _scale.y * 2 * j));
			AddBall(_marble);
		}
	}
	BoxCollider* _boxCollider = GameObject::Instanciate<BoxCollider>();
	_boxCollider->gameObject->GetTransform()->SetScale(vec3(5, 1, 100));
	_boxCollider->gameObject->GetTransform()->SetPosition(vec3(33, 0, 0));

	_boxCollider = GameObject::Instanciate<BoxCollider>();
	_boxCollider->gameObject->GetTransform()->SetScale(vec3(5, 1, 100));
	_boxCollider->gameObject->GetTransform()->SetPosition(vec3(-33, 0, 0));

	_boxCollider = GameObject::Instanciate<BoxCollider>();
	_boxCollider->gameObject->GetTransform()->SetScale(vec3(100, 1, 5));
	_boxCollider->gameObject->GetTransform()->SetPosition(vec3(0, 0, 21));

	_boxCollider = GameObject::Instanciate<BoxCollider>();
	_boxCollider->gameObject->GetTransform()->SetScale(vec3(100, 1, 5));
	_boxCollider->gameObject->GetTransform()->SetPosition(vec3(0, 0, -21));
	World::world->OnNetworkSet += [this]()
	{
		World::networkLayer->OnReceive += [this](const char* _receive)
		{
			JSON myJson;
			myJson = myJson.Load(_receive);
			tvec3<double> vel(myJson["velocity"]["x"].ToFloat(), myJson["velocity"]["y"].ToFloat(), myJson["velocity"]["z"].ToFloat());
			whiteMarble->GetRididBody()->AddImpulse(vel);
		};
	};
}

void MarbleControl::Update(float deltaTime)
{
	
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
	_impulse = vec3(_impulse.x, 0, _impulse.z) * 2.5f;
	whiteMarble->GetRididBody()->AddImpulse(_impulse);
	JSON myJson({ "velocity" , { "x" ,_impulse.x , "y", _impulse.y, "z",_impulse.z} });
	std::cout << myJson.dump().c_str() << std::endl;
	if (!World::networkLayer)return;
	ClientENet* _client = dynamic_cast<ClientENet*>(World::networkLayer);
	if (_client)
		_client->SendPacket(false, myJson.dump().c_str());
	else
		((ServerENet*)World::networkLayer)->BroadcastPacket(false, myJson.dump().c_str());
}
