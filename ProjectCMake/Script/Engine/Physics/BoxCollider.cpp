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
	return false;
}

void BoxCollider::CollisionResult(HitResult _result)
{

}

bool BoxCollider::IntersectPoint(glm::vec3 _point)
{
	bool _intersectX = gameObject->GetTransform()->position.x + bounds.extends.x < _point.x && gameObject->GetTransform()->position.x - bounds.extends.x > _point.x;
	bool _intersectY = gameObject->GetTransform()->position.y + bounds.extends.y < _point.y && gameObject->GetTransform()->position.y - bounds.extends.y > _point.y;
	bool _intersectZ = gameObject->GetTransform()->position.z + bounds.extends.z < _point.z && gameObject->GetTransform()->position.z - bounds.extends.z > _point.z;
	return _intersectX && _intersectY && _intersectZ;
}

void BoxCollider::UpdatePhysics()
{
	
}