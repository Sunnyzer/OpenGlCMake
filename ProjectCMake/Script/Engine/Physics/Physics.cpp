#include "Physics.h"
#include "Collider.h"
#include "RigidBody.h"

size_t Physics::amountCollision = 0;
size_t Physics::amountBody = 0;
std::vector<Collider*> Physics::physicsCollision;
std::vector<RigidBody*> Physics::physicsBody;
QuadTree Physics::tree;
Physics::~Physics()
{
	size_t i = 0;
	for (; i < amountCollision; i++)
		delete physicsCollision[i];
	for (i = 0; i < amountBody; i++)
		delete physicsBody[i];
}

void Physics::UpdatePhysics()
{
	size_t i = 0;
	//for (; i < amountCollision; i++)
		//tree.AddObject(physicsCollision[i]);
	for (i = 0; i < amountCollision; i++)
		physicsCollision[i]->UpdatePhysics();
	//for (i = 0; i < amountCollision; i++)
		//tree.RemoveObject(physicsCollision[i]);
	for (i = 0; i < amountBody; i++)
		physicsBody[i]->UpdatePhysics();
}

//inline void Physics::AddCollider(Collider* _collider)
//{
//	physicsCollision.push_back(_collider);
//	amountCollision++;
//}
//
//inline void Physics::AddRigidBody(RigidBody* _rigidbody)
//{
//	physicsBody.push_back(_rigidbody);
//	amountBody++;
//}