#include "Marble.h"
#include "Mesh.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "SphereCollider.h"

using namespace std;

int Marble::marbleInstance = 0;

Marble::Marble()
{
	mesh = nullptr;
	rigidbody = nullptr;
	collider = nullptr;
	marbleInstance++;
}

Marble::~Marble()
{

}

void Marble::Start()
{
	mesh = gameObject->AddComponent<Mesh>();
	collider = gameObject->AddComponent<SphereCollider>();
	rigidbody = gameObject->AddComponent<RigidBody>();
	string _ball = "Ball15_UV.bmp";
	if (marbleInstance <= 16)
	{
		string instanceAmount = std::to_string(marbleInstance - 1);
		string _ballNumber = "Ball";
		if (instanceAmount.size() == 1)
			_ballNumber.push_back('0');
		_ball = _ballNumber + instanceAmount + "_UV.bmp";
	}
	mesh->LoadMesh("les2.obj", _ball.c_str(), false);
	collider->SetRadius(0.75);
	gameObject->GetTransform()->SetScale(glm::vec3(0.75f));
}

void Marble::OnGUI()
{
	// mesh->OnGUI();
	rigidbody->OnGUI();
	//collider->OnGUI();
}
