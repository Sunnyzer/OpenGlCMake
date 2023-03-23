#pragma once
#include "MonoBehaviour.h"

class Physics;

class PhysicComponent : public MonoBehaviour
{
	friend Physics;
public:
	PhysicComponent();
	~PhysicComponent();

	virtual void OnGUI() override { }
protected:
	virtual void UpdatePhysics() = 0;
};