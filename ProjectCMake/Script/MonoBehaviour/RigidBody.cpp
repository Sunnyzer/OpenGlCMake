#include "RigidBody.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"

RigidBody::RigidBody()
{
	velocity = glm::vec3(0, 0, 0);
}

void RigidBody::AddImpulse(glm::vec3 _velocity)
{
	//(1,0,0) + (0,1,0) = (0.5,0.5,0)
	//(1,0,0) + (0,1,0) = (1,0.5,0)
	//(1,0,0) + (0,1,0) = (1,0.5,0)
	velocity += _velocity;
}

void RigidBody::SetVelocity(glm::vec3 _velocity)
{
	velocity = _velocity;
}

void RigidBody::Update(float deltaTime)
{
	gameObject->GetTransform()->AddPosition(velocity * deltaTime);
	velocity *= 0.93;
}
