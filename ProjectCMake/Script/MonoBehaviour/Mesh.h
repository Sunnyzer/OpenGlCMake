#pragma once
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include "Transform.h"
#include "MonoBehaviour.h"

class Mesh : public MonoBehaviour
{
public:
	Mesh();
	~Mesh();
	void MeshDraw();
	void LoadMesh(const char* _path, const char* _texturePath);
	void MoveVertex(glm::vec3 _pos);
	void ScaleVertex(glm::vec3 _scale);
protected:
	void SetMatrix(glm::mat4* _modelMatrix);
	void Update(float deltaTime) override;
	void SetOwner(GameObject* _gameObject) override;
	GLuint texture;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	glm::mat4* modelMatrix;
};