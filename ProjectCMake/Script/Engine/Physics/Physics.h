#pragma once
#include <vector>
#include "QuadTree.h"

class Collider;
class RigidBody;

class Physics
{
	friend RigidBody;
	friend Collider;
public:
	~Physics();
	static void UpdatePhysics();
	inline static std::vector<Collider*> GetColliders() { return physicsCollision; };
private:
	inline static void AddCollider(Collider* _collider)
	{
		physicsCollision.push_back(_collider);
		amountCollision++;
	}
	inline static void AddRigidBody(RigidBody* _rigidbody)
	{
		physicsBody.push_back(_rigidbody);
		amountBody++;
	}
	static size_t amountCollision;
	static size_t amountBody;
	static QuadTree tree;
	static std::vector<Collider*> physicsCollision;
	static std::vector<RigidBody*> physicsBody;
};