#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider();
	void CheckCollider();
	virtual void UpdateCollider() override;
	void SetRadius(float _radius);
private:
	virtual void Start() override;
	float* radius;
};