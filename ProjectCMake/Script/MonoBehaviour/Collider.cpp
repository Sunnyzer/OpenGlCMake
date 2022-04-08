#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "RigidBody.h"

Collider::Collider()
{
	rigidBody = nullptr;
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
	CollisionManager::collisionManager->AddCollision(this);
}

void Collider::UpdateCollider()
{

}
