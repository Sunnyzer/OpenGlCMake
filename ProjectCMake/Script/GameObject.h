#pragma once

class World;
class Mesh;
class Transform;

class GameObject
{
	friend World;
public:
	GameObject();
	~GameObject();
	virtual void Update();
	inline Mesh* GetMesh() { return mesh; };
	inline Transform* GetTransform() { return transform; };
private:
	Mesh* mesh;
	Transform* transform;
};