#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider();
	virtual bool CheckCollision(Collider* _collider) override;
	virtual void CollisionResult(HitResult _result) override;
	glm::vec3 CalcNormal(Collider* _collider);

	inline float GetRadius() { return bounds.radius; };
	inline void SetRadius(float _radius) { bounds.radius = _radius; }
private:
	virtual void UpdatePhysics() override;
	virtual void Start() override;
};