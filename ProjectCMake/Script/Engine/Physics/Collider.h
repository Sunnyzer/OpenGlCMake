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
struct Bounds
{
	float radius;
	glm::vec3 extends;
};

class Collider : public PhysicComponent
{
	friend Physics;
public:
	Collider();
	virtual bool CheckCollision(Collider* _collider) = 0;
	virtual void CollisionResult(Collider* _collider) = 0;

	inline RigidBody* GetRigidBody() const { return rigidBody; };
	inline FormCollider GetFormCollider() const { return formCollider; };
	inline const Bounds& GetBounds() const { return bounds; };
protected:
	virtual void Start() override;
	void AddRigidbody(RigidBody* _rb);
	FormCollider formCollider;
	RigidBody* rigidBody;
	Bounds bounds;
};