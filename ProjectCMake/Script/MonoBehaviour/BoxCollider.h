#pragma once
#include "Collider.h"
#include <glm\ext\vector_float3.hpp>

class SphereCollider;

class BoxCollider : public Collider
{
public:
	BoxCollider();
	void CheckCollider();
	virtual void UpdateCollider() override;
	void SetBox(glm::vec3 _radius);
	inline glm::vec3 GetBound() { return *box; };
	bool Collision(SphereCollider* sphereCollider);
private:
	virtual void Start() override;
	glm::vec3* box;
};