#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider()
{
	rigidBody = nullptr;
}

void Collider::Start()
{
	CollisionManager::collisionManager->AddCollision(this);
}

void Collider::UpdateCollider()
{

}
