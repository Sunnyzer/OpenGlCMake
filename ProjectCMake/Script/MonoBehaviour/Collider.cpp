#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider()
{
}

void Collider::Start()
{
	CollisionManager::collisionManager->AddCollision(this);
}

void Collider::UpdateCollider()
{

}
