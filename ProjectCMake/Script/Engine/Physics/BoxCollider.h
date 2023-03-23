#pragma once
#include "Collider.h"

class SphereCollider;

class BoxCollider : public Collider
{ 
public:
	BoxCollider();
	virtual bool CheckCollision(Collider* _collider) override;
	virtual void CollisionResult(HitResult _result) override;
	virtual bool IntersectPoint(glm::vec3 _point) override;
	void SetBox(glm::vec3 _box) { bounds.extends = _box; }
protected:
private:
	virtual void UpdatePhysics() override;
};