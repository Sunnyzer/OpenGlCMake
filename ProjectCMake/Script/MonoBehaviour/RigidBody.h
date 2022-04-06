#pragma once
#include <glm/glm.hpp>
#include "MonoBehaviour.h"

class RigidBody : public MonoBehaviour
{
public:
	RigidBody();
	inline glm::vec3 GetVelocity() { return velocity; };
	void AddImpulse(glm::vec3 _velocity);
	void Update(float deltaTime) override;
private:
	glm::vec3 velocity = glm::vec3(0, 0, 0);
};