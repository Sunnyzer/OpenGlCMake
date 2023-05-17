#include "SphereCollider.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "Physics.h"
#include <iostream>

using namespace glm;

SphereCollider::SphereCollider()
{
	bounds.radius = 0.5f;
	formCollider = FormCollider::Sphere;
}

bool SphereCollider::CheckCollision(Collider* _collider)
{
	glm::vec3 _gameObjectPos = gameObject->GetTransform()->position;
	glm::vec3 _gameObjectCollidePos = _collider->gameObject->GetTransform()->position;
	switch (_collider->GetFormCollider())
	{
	case FormCollider::None:
		std::cout << "Collider form NONE !!!" << std::endl;
		return false;
	case FormCollider::Box:
		vec3 center = _gameObjectPos + rigidBody->GetVelocity();
		vec3 difference = center - _gameObjectCollidePos;
		vec3 clamped = glm::clamp(difference, -_collider->GetBounds().extends, _collider->GetBounds().extends);
		vec3 closest = _gameObjectCollidePos + clamped;
		difference = closest - center;
		return length(difference) < bounds.radius;
	case FormCollider::Sphere:
		glm::vec3 _direction = _gameObjectCollidePos - _gameObjectPos;
		float _distance = glm::length(_gameObjectCollidePos - _gameObjectPos);
		return _distance < bounds.radius + _collider->GetBounds().radius;
	}
	return false;
}
void SphereCollider::CollisionResult(HitResult _result)
{
	RigidBody* _colliderRb = nullptr;
	switch (_result.colliderHit->GetFormCollider())
	{
	case FormCollider::None:
		break;
	case FormCollider::Sphere:
		vec3 _gameObjectPos = gameObject->GetTransform()->position;
		_colliderRb = _result.colliderHit->GetRigidBody();

		vec3 _actorVel = rigidBody->GetVelocity();
		vec3 _colliderVel = vec3(0);
		if (_colliderRb) _colliderVel = _colliderRb->GetVelocity();
		vec3 _impactVel = (_actorVel + _colliderVel);

		vec3 _norm = _result.impactNormal * length(_impactVel);
		if (_colliderRb)
		{
			vec3 _newActorColliderVel = (_norm + _impactVel) / 2.0f;
			_colliderRb->SetVelocity(_newActorColliderVel * ((SphereCollider*)_result.colliderHit)->bounceRatio); 
		}
		vec3 _newActorVel = (_impactVel - _norm) / 2.0f;
		rigidBody->SetVelocity(_newActorVel * bounceRatio);
		return;
	case FormCollider::Box:
		vec3 _ratio(1);
		if (_result.impactNormal.x != 0)
			_ratio.x = -1;
		if (_result.impactNormal.z != 0)
			_ratio.z = -1;
		rigidBody->SetVelocity(rigidBody->GetVelocity() * _ratio * bounceRatio);
		return;
	}
}
bool SphereCollider::IntersectPoint(glm::vec3 _point)
{
	return glm::length(gameObject->GetTransform()->position - _point) < GetRadius();
}
glm::vec3 SphereCollider::CalcNormal(Collider* _collider)
{
	switch (_collider->GetFormCollider())
	{
		case FormCollider::None:
			break;
		case FormCollider::Sphere:
			return normalize(_collider->gameObject->GetTransform()->position - gameObject->GetTransform()->position);
		case FormCollider::Box:
			vec3 _impactNormal(0);
			BoxCollider* _box = (BoxCollider*)_collider;
			vec3 _pos = gameObject->GetTransform()->position;
			vec3 _boxPos = _collider->gameObject->GetTransform()->position;
			if (_pos.x < -_box->GetBounds().extends.x)
				_impactNormal.x = -1;
			else if (_pos.x > _box->GetBounds().extends.x)
				_impactNormal.x = 1;
			if (_pos.z < -_box->GetBounds().extends.z)
				_impactNormal.z = -1;
			else if (_pos.z  > _box->GetBounds().extends.z)
				_impactNormal.z = 1;
			std::cout << _impactNormal.x << " " << _impactNormal.z << std::endl;
			return _impactNormal;
	}
	return glm::vec3(0);
}

void SphereCollider::Start()
{
	Collider::Start();  
	OnActorBeginOverlap.Add(this, &SphereCollider::CollisionResult);
}
void SphereCollider::UpdatePhysics()
{
	if (!rigidBody || rigidBody->GetVelocity() == vec3(0, 0, 0)) return;
	std::vector<Collider*> _colliders = Physics::GetColliders();
	size_t _size = _colliders.size();
	for (size_t i = 0; i < _size; i++)
	{
		Collider* _collider = _colliders[i];
		if (_collider == this) continue;
		if (CheckCollision(_collider))
		{
			glm::vec3 _impactNormal = CalcNormal(_collider);
			glm::vec3 _impactPoint = gameObject->GetTransform()->position + _impactNormal * bounds.radius;
			OnActorBeginOverlap.Invoke(HitResult(_collider, _impactPoint, _impactNormal));
		}
	}
}