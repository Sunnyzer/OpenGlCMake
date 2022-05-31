#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider();
	virtual bool CheckCollision(Collider* _collider) override;
	virtual void CollisionResult(Collider* _collider) override;

	void SetRadius(float _radius);

	inline float GetRadius() { return bounds.radius; };
private:
	virtual void UpdatePhysics() override;
	virtual void Start() override;
};