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
	ImGui::Text(std::to_string(velocity.x).c_str());
	ImGui::SameLine();
	ImGui::Text(std::to_string(velocity.y).c_str());
	ImGui::SameLine();
	ImGui::Text(std::to_string(velocity.z).c_str());
}
