#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider();
	void CheckCollider();
	bool Collision(Collider* _collider);
	virtual void UpdateCollider() override;
	void SetRadius(float _radius);
	inline float GetRadius() { return *radius; };
private:
	virtual void Start() override;
	float* radius;
};