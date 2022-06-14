#pragma once
#include "Collider.h"

class SphereCollider;

class BoxCollider : public Collider
{ 
public:
	BoxCollider();
	virtual bool CheckCollision(Collider* _collider) override;
	virtual void CollisionResult(HitResult _result) override;

	void SetBox(glm::vec3 _box) { bounds.extends = _box; }
private:
	virtual void UpdatePhysics() override;
};