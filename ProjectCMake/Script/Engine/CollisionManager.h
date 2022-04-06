#pragma once
#include <vector>

class Collider;

class CollisionManager
{
public:
	static CollisionManager* collisionManager;
	void AddCollision(Collider* _collider);
	void UpdateCollision();
	inline std::vector<Collider*> GetColliders() { return colliders; };
private:
	CollisionManager();
	std::vector<Collider*> colliders;
	size_t amountCollider;
};