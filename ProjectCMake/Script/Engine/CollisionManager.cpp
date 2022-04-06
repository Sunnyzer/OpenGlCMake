#include "CollisionManager.h"
#include "Collider.h"

CollisionManager* CollisionManager::collisionManager = new CollisionManager();

CollisionManager::CollisionManager()
{
	amountCollider = 0;
}

void CollisionManager::AddCollision(Collider* _collider)
{
	colliders.push_back(_collider);
	++amountCollider;
}

void CollisionManager::UpdateCollision()
{
	for (size_t i = 0; i < amountCollider; i++)
	{
		colliders[i]->UpdateCollider();
	}
}
