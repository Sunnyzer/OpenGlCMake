#include "SphereCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"
#include "RigidBody.h"
#include "World.h"
#include <BoxCollider.h>

using namespace glm;

SphereCollider::SphereCollider()
{
	radius = new float(10000000);
}

void SphereCollider::CheckCollider()
{
	std::vector<Collider*> _colliders = CollisionManager::collisionManager->GetColliders();
	size_t _size = _colliders.size();
	for (size_t i = 0; i < _size; i++)
	{
		Collider* _collider = _colliders[i];
		if (_collider == this) continue;
		if (Collision(_collider))
		{
			vec3 _currentLoc = gameObject->GetTransform()->position;
			vec3 _colliderLoc = _collider->gameObject->GetTransform()->position;
			RigidBody* _currentRb = gameObject->GetComponent<RigidBody>();
			RigidBody* _colliderRb = _collider->gameObject->GetComponent<RigidBody>();
			vec3 _currentVel = _currentRb->GetVelocity();
			vec3 _colliderVel = vec3(0);
			if (!_colliderRb) continue;
			_colliderVel = _colliderRb->GetVelocity();
			vec3 _deviation = glm::normalize(_currentVel + _colliderVel);
			vec3 _direction = normalize(_colliderLoc - _currentLoc);
			vec3 _test = (_deviation + _direction)/2.0f;
			_colliderRb->AddImpulse(_test);
			vec3 _test1 = (_deviation - _direction)/2.0f;
			_currentRb->AddImpulse(_test1);
		}
	}	
}

bool SphereCollider::Collision(Collider* _collider)
{
	SphereCollider* _sphereCollider = (SphereCollider*)_collider;
	if (_sphereCollider)
	{
		glm::vec3 _currentLoc = gameObject->GetTransform()->position;
		glm::vec3 _colliderLoc = _collider->gameObject->GetTransform()->position;
		glm::vec3 _direction = _colliderLoc - _currentLoc;
		float _distance = glm::length(_direction);
		return _distance < *radius + *_sphereCollider->radius;
	}
	BoxCollider* _boxCollider = (BoxCollider*)_collider;
	return !_collider;
}

void SphereCollider::UpdateCollider()
{
	CheckCollider();
}
void SphereCollider::SetRadius(float _radius)
{
	delete radius;
	radius = new float(_radius);
}
void SphereCollider::Start()
{
	Collider::Start();
	radius = &gameObject->GetTransform()->scale.y;
}
