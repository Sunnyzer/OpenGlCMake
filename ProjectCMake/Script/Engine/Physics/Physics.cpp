#include "Physics.h"
#include "Collider.h"
#include "RigidBody.h"

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
	for (i = 0; i < amountCollision; i++)
		physicsCollision[i]->UpdatePhysics();
	for (i = 0; i < amountBody; i++)
		physicsBody[i]->UpdatePhysics();
}