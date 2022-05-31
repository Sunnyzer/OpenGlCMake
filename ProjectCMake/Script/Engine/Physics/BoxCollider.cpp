#include "BoxCollider.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include "Physics.h"

using namespace glm;
using namespace std;

BoxCollider::BoxCollider()
{
	bounds.extends = vec3(1);
	formCollider = FormCollider::Box;
}

bool BoxCollider::CheckCollision(Collider* _collider)
{
	/*vec3 center(_collider->gameObject->GetTransform()->position + _collider->GetRigidBody()->GetVelocity());
	vec3 aabb_half_extents(GetBound() * 1.05f);
	vec3 aabb_center = gameObject->GetTransform()->position;
	
	vec3 difference = center - aabb_center;
	vec3 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	
	vec3 closest = aabb_center + clamped;

	difference = closest - center;
	
	bool _valid = length(difference) < ()_collider->GetRadius();*/
	return false;
}
void BoxCollider::CollisionResult(Collider* _collider)
{
	switch (_collider->GetFormCollider())
	{
	case FormCollider::Box:
		break;
	case FormCollider::Sphere:
		SphereCollider* _sphereCollider = (SphereCollider*)_collider;
		vec3 _currentPosition = gameObject->GetTransform()->position;
		vec3 _ballPos = _collider->gameObject->GetTransform()->position;
		float _radius = _sphereCollider->GetRadius();
		float halfBoundX = bounds.extends.x / 2;
		float _maxX = _currentPosition.x + halfBoundX;
		float _minX = _currentPosition.x - halfBoundX;
		bool _posX = _ballPos.x + _radius < _maxX&& _ballPos.x + _radius > _minX;
		bool _posXN = _ballPos.x - _radius < _maxX&& _ballPos.x - _radius > _minX;
		vec3 _velo = _sphereCollider->GetRigidBody()->GetVelocity();
		if (_posX || _posXN)
		{
			vec3 _vel(_velo * vec3(1, 1, -1) * 0.98f);
			_sphereCollider->GetRigidBody()->SetVelocity(_vel);
			return;
		}
		float halfBoundZ = bounds.extends.z / 2;
		float _maxZ = _currentPosition.z + halfBoundZ;
		float _minZ = _currentPosition.z - halfBoundZ;
		bool _posZ = _ballPos.z + _radius < _maxZ&& _ballPos.z + _radius > _minZ;
		bool _posZN = _ballPos.z - _radius < _maxZ&& _ballPos.z - _radius > _minZ;
		if (_posZ || _posZN)
		{
			vec3 _vel(_velo * vec3(-1, 1, 1) * 0.98f);
			_sphereCollider->GetRigidBody()->SetVelocity(_vel);
			return;
		}
		_sphereCollider->GetRigidBody()->SetVelocity(_sphereCollider->GetRigidBody()->GetVelocity() * -0.98f);
		break;
	}
}

void BoxCollider::SetBox(glm::vec3 _box)
{
	bounds.extends = _box;
}

void BoxCollider::Start()
{
	Collider::Start();
}
void BoxCollider::UpdatePhysics()
{
	
}