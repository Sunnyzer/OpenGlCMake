#pragma once
#include <GL\glew.h>
#include <vector>
#include <iostream>
#include "glm/glm.hpp"
#include <common/texture.hpp>
#include <common/objloader.hpp>

class Mesh
{
public:
	Mesh(const char* _mesh, const char* _texture, glm::vec3 _position = glm::vec3(0, 0, 0), glm::vec3 _scale = glm::vec3(1, 1, 1));
	~Mesh();
	void MeshDraw();
private:
	GLuint* texture;
	GLuint* vertexbuffer;
	GLuint* uvbuffer;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	int sizeVertices = 0;
};