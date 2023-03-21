#include "MarbleControl.h"
#include "Mesh.h"
#include "Marble.h"
#include "RigidBody.h"
#include "World.h"
#include "GameObject.h"
#include <OnlineNetwork.h>
#include "ENet.h"
#include <Camera.h>
#include <SphereCollider.h>
#include <BoxCollider.h>


using namespace glm;
using json::JSON;

MarbleControl::MarbleControl()
{
	currentIndex = 0;
	whiteMarble = nullptr;
	amountMarble = 0;
}
MarbleControl::~MarbleControl()
{
	Destroy();
}

void MarbleControl::Start()
{
	Mesh* _mesh = gameObject->AddComponent<Mesh>();
	//Load Mesh
	_mesh->LoadMesh("billard.obj", "Board_UV.bmp", false);
	Input::BindInput(GLFW_KEY_SPACE, InputType::Pressed, this, &MarbleControl::Shoot);
	glm::vec3 _scale(0.75);
	glm::vec3 _basePos(1, _scale.y, 0);
	whiteMarble = GameObject::Instanciate<Marble>();
	whiteMarble->gameObject->GetTransform()->SetPosition(_basePos + vec3(-10, 0, 0));
	whiteMarble->GetCollider()->OnActorBeginOverlap.Add(this, &MarbleControl::DestroyMarble);
	AddBall(whiteMarble);

	SetMarble();
	SetWall();
	OnlineNetwork::onlineNetwork->OnNetworkSet.Add(this, &MarbleControl::AddReceiveInfoToOnReceive);
	//Marble* _oui = new Marble();
}
void MarbleControl::Update(float deltaTime)
{
	if (shoot) return;
	JSON myJson;
	bool _verif = VerifAllMarbleStop(myJson);
	ServerReplicated(OnlineNetwork::onlineNetwork->GetNetwork());
	if (!_verif)return;
	OnlineNetwork::onlineNetwork->SendPacket(NetType::Server, 2, myJson.dump());
}

void MarbleControl::Destroy()
{
	size_t _size = marbles.size();
	for (int i = 0; i < _size; ++i)
	{
		marbles[i]->OnDestroy.Remove(this, &MarbleControl::RemoveMarbleMono);
	}
}

void MarbleControl::DestroyMarble(Collider::HitResult _hitResult)
{
	if (!_hitResult.colliderHit->gameObject->GetComponent<Marble>())return;
	GameObject::Destroy(_hitResult.colliderHit->gameObject);
}

void MarbleControl::RemoveMarbleMono(MonoBehaviour* _mono)
{
	RemoveMarble(static_cast<Marble*>(_mono));
}

void MarbleControl::AddBall(Marble* _object)
{
	marbles.push_back(_object);
	++amountMarble;
}
void MarbleControl::RemoveMarble(Marble* _object)
{
	std::vector<Marble*>::iterator it = marbles.begin();
	for (; it != marbles.end(); ++it)
	{
		if(*it != _object)continue;
		marbles.erase(it);
		--amountMarble;
		return;
	}
}
void MarbleControl::Shoot()
{
	if(!shoot) return;
	shoot = false;
	vec3 _impulse = normalize(vec3(Camera::currentCamera->GetForward().x, 0, Camera::currentCamera->GetForward().z));
	_impulse = vec3(_impulse.x, 0, _impulse.z) * float(75.0f * PERIOD);
	whiteMarble->GetRididBody()->AddImpulse(_impulse);
	BothReplicated(OnlineNetwork::onlineNetwork->GetNetwork());
	JSON myJson({ "velocity" , { "x" ,_impulse.x , "y", _impulse.y, "z",_impulse.z} });
	OnlineNetwork::onlineNetwork->SendPacket(NetType::Both, 0, myJson.dump());
}

void MarbleControl::SetMarble()
{
	glm::vec3 _scale(0.75);
	glm::vec3 _basePos(1, _scale.y, 0);
	Marble* _marble = GameObject::Instanciate<Marble>();
	_marble->gameObject->GetTransform()->SetPosition(_basePos);
	_marble->OnDestroy.Add(this, &MarbleControl::RemoveMarbleMono);
	AddBall(_marble);
	for (size_t i = 2; i < 6; ++i)
	{
		for (size_t j = 0; j < i; ++j)
		{
			_marble = GameObject::Instanciate<Marble>();
			_marble->gameObject->GetTransform()->SetPosition(_basePos + vec3((i - 2) * _scale.y * 2 + _scale.y * 2, 0, ((i - 1) * -_scale.y) + _scale.y * 2 * j));
			_marble->OnDestroy.Add(this, &MarbleControl::RemoveMarbleMono);
			AddBall(_marble);
		}
	}
}

void MarbleControl::AddReceiveInfoToOnReceive()
{
	OnlineNetwork::onlineNetwork->GetNetwork()->OnReceive.Add(this, &MarbleControl::ReceiveInfo);
}

void MarbleControl::SetWall()
{
	BoxCollider* _boxCollider = GameObject::Instanciate<BoxCollider>();
	_boxCollider->gameObject->GetTransform()->SetScale(vec3(5, 1, 100));
	_boxCollider->SetBox(vec3(5, 1, 100));
	_boxCollider->gameObject->GetTransform()->SetPosition(vec3(33, 0, 0));

	_boxCollider = GameObject::Instanciate<BoxCollider>();
	_boxCollider->gameObject->GetTransform()->SetScale(vec3(5, 1, 100));
	_boxCollider->SetBox(vec3(5, 1, 100));
	_boxCollider->gameObject->GetTransform()->SetPosition(vec3(-33, 0, 0));

	_boxCollider = GameObject::Instanciate<BoxCollider>();
	_boxCollider->gameObject->GetTransform()->SetScale(vec3(100, 1, 5));
	_boxCollider->SetBox(vec3(100, 1, 5));
	_boxCollider->gameObject->GetTransform()->SetPosition(vec3(0, 0, 21));

	_boxCollider = GameObject::Instanciate<BoxCollider>();
	_boxCollider->gameObject->GetTransform()->SetScale(vec3(100, 1, 5));
	_boxCollider->SetBox(vec3(100, 1, 5));
	_boxCollider->gameObject->GetTransform()->SetPosition(vec3(0, 0, -21));
}

void MarbleControl::ReceiveInfo(ENetPacket* _receive)
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
}

bool MarbleControl::VerifAllMarbleStop(JSON& json)
{
	for (size_t i = 0; i < amountMarble; ++i)
	{
		Marble* _marble = marbles[i];
		if (!_marble) continue;
		//TODO
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

