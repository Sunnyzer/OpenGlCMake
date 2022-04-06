#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider();
	void CheckCollider();
	virtual void UpdateCollider() override;
private:
	float radius;
};