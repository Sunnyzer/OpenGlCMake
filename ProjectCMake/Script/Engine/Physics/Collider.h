#pragma once
#include "PhysicComponent.h"

class RigidBody;
class Physics;
struct HitResult;

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
	Collider();
	virtual ~Collider();

	virtual bool CheckCollision(Collider* _collider) = 0;
	virtual void CollisionResult(HitResult _result) = 0;
	virtual bool IntersectPoint(glm::vec3 _point) = 0;

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
