#pragma once
#include "MonoBehaviour.h"

class CollisionManager;
class RigidBody;

class Collider : public MonoBehaviour
{
	friend CollisionManager;
public:
	Collider();
	inline RigidBody* GetRigidBody() { return rigidBody; };
protected:
	void AddRigidbody(RigidBody* _rb);
	virtual void Start() override;
	virtual void UpdateCollider();
	RigidBody* rigidBody;
};