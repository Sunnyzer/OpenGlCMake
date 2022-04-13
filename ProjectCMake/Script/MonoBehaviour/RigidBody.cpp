#include "RigidBody.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"
#include "World.h"
#include <iostream>

RigidBody::RigidBody()
{
	velocity = glm::vec3(0, 0, 0);
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

void RigidBody::Update(float deltaTime)
{
	gameObject->GetTransform()->AddPosition(velocity + gameObject->GetTransform()->rotation);
	//if(length(rVelocity) > 0.05f)
		//gameObject->GetTransform()->AddRotation(0.1f, rVelocity);
	velocity *= 98.0/100.0;
	rVelocity *= 98.0/100.0;
}
