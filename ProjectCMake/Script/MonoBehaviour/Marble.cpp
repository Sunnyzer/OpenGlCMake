#include "Mesh.h"
#include "Marble.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "SphereCollider.h"
#include <string>

using namespace std;

int Marble::marbleInstance = 0;

Marble::Marble()
{
	mesh = nullptr;
	rigidbody = nullptr;
	collider = nullptr;
	marbleInstance++;
}

void Marble::Start()
{
	mesh = gameObject->AddComponent<Mesh>();
	collider = gameObject->AddComponent<SphereCollider>();
	rigidbody = gameObject->AddComponent<RigidBody>();
	string instanceAmount = std::to_string(marbleInstance);
	string _ballNumber = "Ball";
	if (instanceAmount.size() == 1)
		_ballNumber.push_back('0');
	string _ball = _ballNumber + instanceAmount + "_UV.bmp";
	const char* _marble = _ball.c_str();
	mesh->LoadMesh("les2.obj", _marble, false);
}