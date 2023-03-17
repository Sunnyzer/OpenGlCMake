#pragma once
#include <vector>

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
	inline static void RemoveCollider(Collider* _collider)
	{
		std::vector<Collider*>::iterator it = physicsCollision.begin();
		for (; it != physicsCollision.end(); ++it)
		{
			if (*it != _collider) continue;
			physicsCollision.erase(it);
			--amountCollision;
			return;
		}
	}
	inline static void RemoveRigidbody(RigidBody* _rigidBody)
	{
		std::vector<RigidBody*>::iterator it = physicsBody.begin();
		for (; it != physicsBody.end(); ++it)
		{
			if (*it != _rigidBody) continue;
			physicsBody.erase(it);
			--amountBody;
			return;
		}
	}
	static size_t amountCollision;
	static size_t amountBody;
	static std::vector<Collider*> physicsCollision;
	static std::vector<RigidBody*> physicsBody;
};