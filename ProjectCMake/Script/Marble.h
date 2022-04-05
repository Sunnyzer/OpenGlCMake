#pragma once
#include "MonoBehaviour.h"

class Marble : public MonoBehaviour
{
public:
	Marble();
	void Start() override;
	inline Mesh* GetMesh() { return mesh; };
private:
	Mesh* mesh;
};