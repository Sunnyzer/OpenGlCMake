#include "Mesh.h"
#include "MarbleControl.h"
#include "Input.h"
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
	server = nullptr;
}

void MarbleControl::Start()
{
	Input::BindInput(GLFW_KEY_SPACE, this, &MarbleControl::Shoot);
	glm::vec3 _scale(0.75);
	glm::vec3 _basePos(1, _scale.y, 0);
	whiteMarble = GameObject::Instanciate<Marble>();
	whiteMarble->gameObject->GetTransform()->SetScale(_scale);
	whiteMarble->gameObject->GetTransform()->SetPosition(_basePos + vec3(-10, 0, 0));
	AddBall(whiteMarble);
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
	server = dynamic_cast<ServerENet*>(World::networkLayer);
	World::world->OnNetworkSet += [this]()
	{
		server = dynamic_cast<ServerENet*>(World::networkLayer);
		World::networkLayer->OnReceive += [this](ENetPacket* _receive)
		{
			JSON myJson;
			myJson = myJson.Load((char*)_receive->data);
			size_t _size = marbles.size();
			switch (_receive->flags)
			{
			case 0:
				tvec3<double> vel(myJson["velocity"]["x"].ToFloat(), myJson["velocity"]["y"].ToFloat(), myJson["velocity"]["z"].ToFloat());
				whiteMarble->GetRididBody()->AddImpulse(vel);
				shoot = false;
				break;
			case 2:
				for (size_t i = 0; i < _size; i++)
				{
					glm::vec3 _pos;
					size_t _size = 3;
					for (size_t j = 0; j < _size; j++)
					{
						float _posValue = (float)myJson["position" + std::to_string(i)].at((unsigned int)j).ToFloat();
						_pos[(length_t)j] = _posValue;
					}
					marbles[i]->gameObject->GetTransform()->SetPosition(_pos);
				}
				break;
			default:
				break;
			}
		};
	};
}

void MarbleControl::Update(float deltaTime)
{
	if (shoot) return;
	JSON myJson;
	size_t _size = marbles.size();
	for (size_t i = 0; i < _size; i++)
	{
		Marble* _marble = marbles[i];
		if (length(_marble->GetRididBody()->GetVelocity()) > 0.005f)
		{
			shoot = false;
			return;
		}
		if(server)
			myJson["position" + std::to_string(i)] = json::Array(_marble->gameObject->GetTransform()->position.x , _marble->gameObject->GetTransform()->position.y, _marble->gameObject->GetTransform()->position.z);
		_marble->GetRididBody()->SetVelocity(glm::vec3(0));
	}
	shoot = true;
	if (server)
		server->BroadcastPacket(false, 2, myJson.dump().c_str());
}

void MarbleControl::AddBall(Marble* _object)
{
	marbles.push_back(_object);
}

void MarbleControl::Shoot()
{
	if(!shoot) return;
	shoot = false;
	vec3 _impulse = normalize(vec3(Camera::forward.x, 0, Camera::forward.z));
	_impulse = vec3(_impulse.x, 0, _impulse.z) * 2.5f;
	whiteMarble->GetRididBody()->AddImpulse(_impulse);
	if (!World::networkLayer) return;
	JSON myJson({ "velocity" , { "x" ,_impulse.x , "y", _impulse.y, "z",_impulse.z} });
	World::networkLayer->SendBroadcastPacket(false, 0, myJson.dump().c_str());
}
