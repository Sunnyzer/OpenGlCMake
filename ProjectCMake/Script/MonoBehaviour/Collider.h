#pragma once
#include "MonoBehaviour.h"

class CollisionManager;

class Collider : public MonoBehaviour
{
	friend CollisionManager;
public:
	Collider();

protected:
	virtual void Start() override;
	virtual void UpdateCollider();
};