#include "Mesh.h"
#include "Marble.h"
#include "GameObject.h"

Marble::Marble()
{
	mesh = nullptr;
}

void Marble::Start()
{
	glm::vec3 scale(0.25f);
	gameObject->GetTransform()->AddPosition(glm::vec3(0, scale.x, 0));
	gameObject->GetTransform()->SetScale(scale);
	mesh = gameObject->AddComponent<Mesh>();
	mesh->LoadMesh("les2.obj", "uvmap.DDS");
}