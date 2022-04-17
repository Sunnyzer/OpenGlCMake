#include "SphereCollider.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "Physics.h"

using namespace glm;

SphereCollider::SphereCollider()
{
	radius = new float(1);
	formCollider = FormCollider::Sphere;
}

bool SphereCollider::CheckCollision(Collider* _collider)
{
	glm::vec3 _currentLoc = gameObject->GetTransform()->position;
	glm::vec3 _colliderLoc = _collider->gameObject->GetTransform()->position;
	switch (_collider->GetFormCollider())
	{
	case FormCollider::Box:
		vec3 center(_currentLoc + rigidBody->GetVelocity());
		vec3 aabb_half_extents(((BoxCollider*)_collider)->GetBound() * 1.05f);
		vec3 aabb_center = _colliderLoc;
		vec3 difference = center - aabb_center;
		vec3 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
		vec3 closest = aabb_center + clamped;
		difference = closest - center;
		return length(difference) < *radius;
	case FormCollider::Sphere:
		glm::vec3 _direction = _colliderLoc - _currentLoc;
		float _distance = glm::length(_colliderLoc - _currentLoc);
		return _distance < *radius + *((SphereCollider*)_collider)->radius;
	}
	return false;
}
void SphereCollider::CollisionResult(Collider* _collider)
{
	vec3 _currentLoc = gameObject->GetTransform()->position;
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
	vec3 _test1 = (_vel - norm) / 2.0f;
	rigidBody->SetVelocity(_test1);
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
			_collider->CollisionResult(this);
	}
}