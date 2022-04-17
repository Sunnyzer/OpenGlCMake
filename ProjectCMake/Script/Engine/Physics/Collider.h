#pragma once
#include "PhysicComponent.h"

class RigidBody;
class Physics;

enum class FormCollider
{
	None,
	Sphere,
	Box
};

class Collider : public PhysicComponent
{
	friend Physics;
public:
	Collider();
	virtual bool CheckCollision(Collider* _collider) = 0;
	virtual void CollisionResult(Collider* _collider) = 0;

	inline RigidBody* GetRigidBody() { return rigidBody; };
	inline FormCollider GetFormCollider() { return formCollider; };
protected:
	virtual void Start() override;

	void AddRigidbody(RigidBody* _rb);
	FormCollider formCollider;
	RigidBody* rigidBody;
};