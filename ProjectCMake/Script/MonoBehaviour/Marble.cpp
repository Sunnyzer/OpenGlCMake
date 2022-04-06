#include "Mesh.h"
#include "Marble.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "SphereCollider.h"

Marble::Marble()
{
	mesh = nullptr;
	rigidbody = nullptr;
}

void Marble::Start()
{
	//glm::vec3 scale(0.25f);
	//gameObject->GetTransform()->AddPosition(glm::vec3(0, scale.x, 0));
	//gameObject->GetTransform()->SetScale(scale);
	mesh = gameObject->AddComponent<Mesh>();
	collider = gameObject->AddComponent<SphereCollider>();
	rigidbody = gameObject->AddComponent<RigidBody>();
	mesh->LoadMesh("les2.obj", "uvmap.DDS");
}