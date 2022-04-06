#include "SphereCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"
#include "RigidBody.h"

SphereCollider::SphereCollider()
{
	radius = 1;
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
		float _distance = _direction.length();
		if (_distance <= radius*2)
		{
			RigidBody* _currentRb = gameObject->GetComponent<RigidBody>();
			RigidBody* _colliderRb = _collider->gameObject->GetComponent<RigidBody>();
			glm::vec3 _currentVel = _currentRb->GetVelocity();
			glm::vec3 _colliderVel;
			_direction = glm::normalize(_direction);
			glm::vec3 _deviation = _currentVel + _colliderVel;
			if (_colliderRb)
			{
				_colliderVel = _colliderRb->GetVelocity();
				_colliderRb->AddImpulse(_deviation + _direction);
			}
			_currentRb->AddImpulse(_deviation - _direction);
		}
	}
	
}

void SphereCollider::UpdateCollider()
{
	CheckCollider();
}
