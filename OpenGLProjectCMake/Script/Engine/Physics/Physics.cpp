#include "Physics.h"
#include "Collider.h"
#include "RigidBody.h"
#include "GameObject.h"

size_t Physics::amountCollision = 0;
size_t Physics::amountBody = 0;
std::vector<Collider*> Physics::physicsCollision;
std::vector<RigidBody*> Physics::physicsBody;

Physics::~Physics()
{
	size_t i = 0;
	for (; i < amountCollision; ++i)
		delete physicsCollision[i];
	for (i = 0; i < amountBody; ++i)
		delete physicsBody[i];
}

void Physics::UpdatePhysics()
{
	size_t i = 0;
	for (i = 0; i < amountCollision; ++i)
		physicsCollision[i]->UpdatePhysics();
	for (i = 0; i < amountBody; ++i)
		physicsBody[i]->UpdatePhysics();
}

bool Physics::Raycast(glm::vec3 _position, glm::vec3 _direction, HitResult& _hitResult)
{
	for (size_t i = 0; i < amountCollision; ++i)
	{
		glm::vec3 _y = physicsCollision[i]->gameObject->GetTransform()->position;
		glm::vec3 _a = glm::normalize(_direction);
		glm::vec3 _b = _position;
		glm::vec3 _yb = _y - _b;
		//float point = glm::length(glm::vec3(_a.x != 0 ? (_yb.x / _a.x) : 0, _a.y != 0 ? (_yb.y / _a.y) : 0, _a.z != 0 ? (_yb.z / _a.z) : 0));
		float point = glm::length(_yb);
		glm::vec3 nearPoint = _a * point + _b;
		if (physicsCollision[i]->IntersectPoint(nearPoint))
		{
			_hitResult = HitResult(physicsCollision[i], glm::vec3(), glm::vec3());
			return true;
		}
	}
	return false;
}
