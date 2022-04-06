#include "SphereCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"
#include "RigidBody.h"

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
		glm::vec3 _currentLoc = gameObject->GetTransform()->position;
		glm::vec3 _colliderLoc = _collider->gameObject->GetTransform()->position;
		glm::vec3 _direction = _colliderLoc - _currentLoc;
		float _distance = glm::length(_direction);
		if (_distance < *radius*2)
		{
			RigidBody* _currentRb = gameObject->GetComponent<RigidBody>();
			RigidBody* _colliderRb = _collider->gameObject->GetComponent<RigidBody>();
			glm::vec3 _currentVel = _currentRb->GetVelocity()/ 2.0f;
			glm::vec3 _colliderVel = _colliderRb->GetVelocity()/2.0f;
			glm::vec3 _deviation = glm::normalize(_currentVel + _colliderVel);
			_direction = glm::normalize(_direction);
			glm::vec3 _test = (_deviation + _direction) / 10.f;
			_colliderRb->AddImpulse(_test);
			glm::vec3 _test1 = (_deviation - _direction) / 10.f;
			_currentRb->AddImpulse(_test1);
		}
	}	
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
