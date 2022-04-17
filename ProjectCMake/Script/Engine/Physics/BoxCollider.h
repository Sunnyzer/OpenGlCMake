#pragma once
#include "Collider.h"

class SphereCollider;

class BoxCollider : public Collider
{
public:
	BoxCollider();
	virtual bool CheckCollision(Collider* _collider) override;
	virtual void CollisionResult(Collider* _collider) override;

	void SetBox(glm::vec3 _radius);

	inline glm::vec3 GetBound() { return *box; };
private:
	virtual void Start() override;
	virtual void UpdatePhysics() override;
	glm::vec3* box;
};