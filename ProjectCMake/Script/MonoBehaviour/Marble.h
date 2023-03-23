#pragma once
#include "MonoBehaviour.h"

class RigidBody;
class SphereCollider;
class Mesh;

class Marble : public MonoBehaviour
{
    CLONE(Marble);
public:
	Marble();
	~Marble() override;
	void Start() override;
	inline Mesh* GetMesh() { return mesh; };
	inline RigidBody* GetRididBody() { return rigidbody; };
	inline SphereCollider* GetCollider() { return collider; };
	virtual void OnGUI() override;
private:
	Mesh* mesh;
	RigidBody* rigidbody;
	SphereCollider* collider;
	static int marbleInstance;
};
REGISTERFACTORY(MonoBehaviour,Marble)