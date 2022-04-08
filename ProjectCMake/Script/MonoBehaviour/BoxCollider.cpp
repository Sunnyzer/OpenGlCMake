#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"
#include "RigidBody.h"
#include "World.h"
#include <SphereCollider.h>
#include <iostream>
#include <iostream>

using namespace glm;
using namespace std;

BoxCollider::BoxCollider()
{
	box = new vec3(0);
}

void BoxCollider::CheckCollider()
{
	int x = 0;
	vector<Collider*> _colliders = CollisionManager::collisionManager->GetColliders();
	size_t _size = _colliders.size();
	for (size_t i = 0; i < _size; i++)
	{
		Collider* _collider = _colliders[i];
		RigidBody* _rbCollider = _collider->GetRigidBody();
		if (_collider == this) continue;
		if (!_rbCollider || _rbCollider->GetVelocity() == vec3(0, 0, 0))continue;
		SphereCollider* _sphereCollider = (SphereCollider*)_collider;
		if (length(_rbCollider->GetVelocity()) > 15)
		{
			x++;
		}
		if (Collision(_sphereCollider))
		{
			vec3 _ballPos = _sphereCollider->gameObject->GetTransform()->position;
			vec3 _currentPosition = gameObject->GetTransform()->position;
			float _radius = _sphereCollider->GetRadius();
 			float _maxX = _currentPosition.x + (GetBound().x/2);
			float _minX = _currentPosition.x - (GetBound().x/2);
			bool _posX = _ballPos.x + _radius < _maxX && _ballPos.x + _radius > _minX;
			bool _posXN = _ballPos.x - _radius < _maxX && _ballPos.x - _radius > _minX;
			vec3 _velo = _rbCollider->GetVelocity();
			if (_posX|| _posXN)
			{
				vec3 _vel(_velo * vec3(1, 1, -1));
				_rbCollider->SetVelocity(_vel);
				continue;
			}
			float _maxZ = _currentPosition.z + (GetBound().z/2);
			float _minZ = _currentPosition.z - (GetBound().z/2);
			bool _posZ = _ballPos.z + _radius < _maxZ && _ballPos.z + _radius > _minZ;
			bool _posZN = _ballPos.z - _radius < _maxZ && _ballPos.z - _radius > _minZ;
			if (_posZ || _posZN)
			{
				vec3 _vel(_velo * vec3(-1, 1, 1));
				_rbCollider->SetVelocity(_vel);
				continue;
			}
			_rbCollider->SetVelocity(_rbCollider->GetVelocity() * -1.0f);
		}
	}
	if(x != 0)
		cout << "x : " << x << endl;
}

void BoxCollider::UpdateCollider()
{
	CheckCollider();
}
void BoxCollider::SetBox(glm::vec3 _box)
{
	box = new vec3(_box);
}
bool BoxCollider::Collision(SphereCollider* _sphereCollider)
{
	if (!_sphereCollider) return false;
	vec3 center(_sphereCollider->gameObject->GetTransform()->position );
	vec3 aabb_half_extents(GetBound());
	vec3 aabb_center = gameObject->GetTransform()->position;
	
	vec3 difference = center - aabb_center;
	vec3 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	
	vec3 closest = aabb_center + clamped;

	difference = closest - center;
	
	bool _valid = length(difference) < _sphereCollider->GetRadius();
	return _valid;
}
void BoxCollider::Start()
{
	Collider::Start();
	box = &gameObject->GetTransform()->scale;
}
