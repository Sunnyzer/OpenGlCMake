#pragma once
#include <glm\ext\vector_float3.hpp>
#include "PhysicComponent.h"

class RigidBody : public PhysicComponent
{
public:
	RigidBody();
	virtual ~RigidBody();
	inline glm::vec3 GetVelocity() { return velocity; };
	void AddImpulse(glm::vec3 _velocity);
	void AddRImpulse(glm::vec3 _velocity);
	void SetVelocity(glm::vec3 _velocity);
	void SetRVelocity(glm::vec3 _velocity);
	virtual void UpdatePhysics() override;
private:
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	glm::vec3 rVelocity = glm::vec3(0, 0, 0);
};