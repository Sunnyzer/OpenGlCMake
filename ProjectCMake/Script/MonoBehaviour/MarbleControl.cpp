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

using namespace glm;
using json::JSON;

MarbleControl::MarbleControl()
{
	currentIndex = 0;
	whiteMarble = nullptr;
	server = nullptr;
	amountMarble = 0;
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

	SetMarble();
	SetWall();

	World::world->OnNetworkSet += [this]()
	{
		World::networkLayer->OnReceive += [this](ENetPacket* _receive)
		{
			JSON myJson;
			myJson = myJson.Load((char*)_receive->data);
			size_t _size = marbles.size();
			JSON _velocity;
			switch (_receive->flags)
			{
			case 0:
				_velocity = myJson["velocity"];
				vec3 vel(_velocity["x"].ToFloat(), _velocity["y"].ToFloat(), _velocity["z"].ToFloat());
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
						float _posValue = (float)myJson[name][marbles[i]->GetName()]["position"].at((unsigned int)j).ToFloat();
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
	bool _verif = VerifAllMarbleStop(myJson);
	ServerReplicated(World::networkLayer);
	if(_verif && World::networkLayer)
		World::networkLayer->SendBroadcastPacket(false, NetType::Server,2, myJson.dump().c_str());
}

void MarbleControl::AddBall(Marble* _object)
{
	marbles.push_back(_object);
	amountMarble++;
}
void MarbleControl::Shoot()
{
	if(!shoot) return;
	shoot = false;
	vec3 _impulse = normalize(vec3(Camera::forward.x, 0, Camera::forward.z));
	_impulse = vec3(_impulse.x, 0, _impulse.z) * 2.5f;
	whiteMarble->GetRididBody()->AddImpulse(_impulse);
	BothReplicated(World::networkLayer);
	JSON myJson({ "velocity" , { "x" ,_impulse.x , "y", _impulse.y, "z",_impulse.z} });
	if(World::networkLayer)
		World::networkLayer->SendBroadcastPacket(false, NetType::Both,0, myJson.dump().c_str());
}

void MarbleControl::SetMarble()
{
	glm::vec3 _scale(0.75);
	glm::vec3 _basePos(1, _scale.y, 0);
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
}
void MarbleControl::SetWall()
{
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
}
bool MarbleControl::VerifAllMarbleStop(JSON& json)
{
	for (size_t i = 0; i < amountMarble; i++)
	{
		Marble* _marble = marbles[i];
		if (length(_marble->GetRididBody()->GetVelocity()) > 0.005f)
		{
			shoot = false;
			return false;
		}
		vec3 _pos = _marble->gameObject->GetTransform()->position;
		json[name][_marble->GetName()]["position"] = json::Array(_pos.x, _pos.y, _pos.z);
		_marble->GetRididBody()->SetVelocity(glm::vec3(0));
	}
	shoot = true;
	return true;
}