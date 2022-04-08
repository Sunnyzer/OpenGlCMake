#include "Mesh.h"
#include "Marble.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "SphereCollider.h"

Marble::Marble()
{
	mesh = nullptr;
	rigidbody = nullptr;
	collider = nullptr;
}

void Marble::Start()
{
	mesh = gameObject->AddComponent<Mesh>();
	collider = gameObject->AddComponent<SphereCollider>();
	rigidbody = gameObject->AddComponent<RigidBody>();
	mesh->LoadMesh("les2.obj", "Ball01_UV.bmp", false);
}