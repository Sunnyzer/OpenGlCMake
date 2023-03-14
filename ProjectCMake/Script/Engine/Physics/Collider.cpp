#include "Collider.h"
#include "GameObject.h"
#include "Physics.h"
#include "RigidBody.h"

Collider::Collider()
{
	rigidBody = nullptr;
	bounds;
	formCollider = FormCollider::None;
	Physics::AddCollider(this);
}
void Collider::AddRigidbody(MonoBehaviour* _rb)
{
	if (rigidBody || !_rb)
	{
		//gameObject->OnAddMonoBehaviour -= func;
		func = nullptr;
		return;
	}
	rigidBody = dynamic_cast<RigidBody*>(_rb);
	if (rigidBody)
	{
		//gameObject->OnAddMonoBehaviour -= func;
		func = nullptr;
	}
}
void Collider::Start()
{
	rigidBody = gameObject->GetComponent<RigidBody>();
	func = [this](MonoBehaviour* _t) { AddRigidbody(_t); };
	gameObject->OnAddMonoBehaviour.Add(this, &Collider::AddRigidbody);
}