#include "RigidBody.h"
#include "GameObject.h"
#include "Physics.h"
#include "imgui.h"

RigidBody::RigidBody()
{
	velocity = glm::vec3(0, 0, 0);
	Physics::AddRigidBody(this);
}
RigidBody::~RigidBody()
{
	Physics::RemoveRigidbody(this);
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

void RigidBody::OnGUI()
{
	float v[3] = { velocity.x, velocity.y, velocity.z };
	ImGui::Text("Velocity : ");
	ImGui::SameLine();
	ImGui::InputFloat3("##velocity", v);
}
