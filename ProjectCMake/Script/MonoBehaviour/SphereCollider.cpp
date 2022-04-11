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
	radius = new float(1);
}

void SphereCollider::CheckCollider()
{
	if (!rigidBody || rigidBody->GetVelocity() == vec3(0, 0, 0)) return;
	std::vector<Collider*> _colliders = CollisionManager::collisionManager->GetColliders();
	vec3 _currentLoc = gameObject->GetTransform()->position;
	size_t _size = _colliders.size();
	for (size_t i = 0; i < _size; i++)
	{
		Collider* _collider = _colliders[i];
		if (_collider == this) continue;
		if (Collision(_collider))
		{
			vec3 _colliderLoc = _collider->gameObject->GetTransform()->position;

			RigidBody* _colliderRb = _collider->GetRigidBody();
			
			vec3 _currentVel = rigidBody->GetVelocity();
			vec3 _colliderVel = vec3(0);

			if (_colliderRb)
				_colliderVel = _colliderRb->GetVelocity();
			vec3 _vel = (_currentVel + _colliderVel);

			vec3 norm = normalize(_colliderLoc - _currentLoc) * length(_vel);
			if (_colliderRb)
			{
				vec3 _test = (norm + _vel) / 2.0f;
				_colliderRb->SetVelocity(_test);
			}
			vec3 _test1 =(_vel - norm) / 2.0f;
			rigidBody->SetVelocity(_test1);
		}
	}	
}

bool SphereCollider::Collision(Collider* _collider)
{
	SphereCollider* _sphereCollider = dynamic_cast<SphereCollider*>(_collider);
	if (_sphereCollider)
	{
		glm::vec3 _currentLoc = gameObject->GetTransform()->position;
		glm::vec3 _colliderLoc = _collider->gameObject->GetTransform()->position;
		glm::vec3 _direction = _colliderLoc - _currentLoc;
		float _distance = glm::length(_direction);
		return _distance < *radius + *_sphereCollider->radius;
	}
	return false;
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
