#include "RigidBody.h"
#include "GameObject.h"
#include "Physics.h"

RigidBody::RigidBody()
{
	velocity = glm::vec3(0, 0, 0);
	Physics::AddRigidBody(this);
}

void RigidBody::AddImpulse(glm::vec3 _velocity)
{
	velocity += _velocity;
}

void RigidBody::AddRImpulse(glm::vec3 _velocity)
{
	rVelocity += _velocity;
}

void RigidBody::SetVelocity(glm::vec3 _velocity)
{
	velocity = _velocity;
}

void RigidBody::SetRVelocity(glm::vec3 _velocity)
{
	rVelocity = _velocity;
}

void RigidBody::UpdatePhysics()
{
	gameObject->GetTransform()->AddPosition(velocity);
	velocity *= 98.0 / 100.0;
}