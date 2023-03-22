#pragma once
#include "MonoBehaviour.h"
#include "Factory.h"

class RigidBody;
class SphereCollider;
class Mesh;

class Marble : public MonoBehaviour
{
public:
	Marble();
	~Marble() override;
	void Start() override;
	inline Mesh* GetMesh() { return mesh; };
	inline RigidBody* GetRididBody() { return rigidbody; };
	inline SphereCollider* GetCollider() { return collider; };
private:
	Mesh* mesh;
	RigidBody* rigidbody;
	SphereCollider* collider;
	static int marbleInstance;
	virtual MonoBehaviour* Clone() override
	{
		return new Marble(*this);
	}
};

REGISTERFACTORY(MonoBehaviour, Marble);