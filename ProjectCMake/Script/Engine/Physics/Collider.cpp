#include "Collider.h"
#include "GameObject.h"
#include "Physics.h"
#include "RigidBody.h"

Collider::Collider()
{
	rigidBody = nullptr;
	formCollider = FormCollider::None;
	Physics::AddCollider(this);
}
void Collider::AddRigidbody(RigidBody* _rb)
{
	if (rigidBody || !_rb)
		return;
	rigidBody = _rb;
}
void Collider::Start()
{
	rigidBody = gameObject->GetComponent<RigidBody>();
	gameObject->OnAddMonoBehaviour += [&](MonoBehaviour* _rb)
	{
		AddRigidbody(dynamic_cast<RigidBody*>(_rb));
	};
}