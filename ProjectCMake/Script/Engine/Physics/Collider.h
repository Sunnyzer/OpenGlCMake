#pragma once
#include "PhysicComponent.h"

class RigidBody;
class Physics;

enum class FormCollider
{
	None,
	Sphere,
	Box
}; 

struct Bounds
{
	float radius;
	glm::vec3 extends;
};


class Collider : public PhysicComponent
{
	friend Physics;
public:
	struct HitResult
	{
		glm::vec3 impactPoint;
		glm::vec3 impactNormal;
		Collider* colliderHit;
		HitResult()
		{

		}
		HitResult(Collider* _collider, glm::vec3 _impactPoint, glm::vec3 _impactNormal)
		{
			colliderHit = _collider;
			impactPoint = _impactPoint;
			impactNormal = _impactNormal;
		}
	};
	Collider();
	virtual ~Collider();

	virtual bool CheckCollision(Collider* _collider) = 0;
	virtual void CollisionResult(HitResult _result) = 0;

	inline RigidBody* GetRigidBody() const { return rigidBody; };
	inline FormCollider GetFormCollider() const { return formCollider; };
	inline const Bounds& GetBounds() const { return bounds; };
	Action<HitResult> OnActorBeginOverlap;
	Action<HitResult> OnActorEndOverlap;
protected:
	virtual void Start() override;
	void AddRigidbody(MonoBehaviour* _rb);
	FormCollider formCollider;
	RigidBody* rigidBody;
	Bounds bounds;
	float bounceRatio = 1; 
private:
	std::function<void(MonoBehaviour*)> func;
};
