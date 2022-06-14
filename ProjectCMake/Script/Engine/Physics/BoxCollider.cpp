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

void BoxCollider::UpdatePhysics()
{
	
}