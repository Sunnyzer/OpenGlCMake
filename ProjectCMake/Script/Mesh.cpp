#include "Mesh.h"
#include "World.h"
#include <common/texture.hpp>
#include <common/objloader.hpp>
#include "ObjectStorage.h"

//#include <GL\glew.h>
//#include <glm/glm.hpp>

using namespace glm;

Mesh::Mesh()
{
	texture = 0;
	uvbuffer = 0;
	vertexbuffer = 0;
	modelMatrix = new glm::mat4(1);
}
Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteTextures(1, &texture);
}
void Mesh::MeshDraw()
{
	glm::mat4 MVP = World::world->GetProjectionMatrix() * World::world->GetViewMatrix() * *modelMatrix;
	glUniformMatrix4fv(World::world->GetMatrixID(), 1, GL_FALSE, &MVP[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	GLsizei _count = (GLsizei)vertices.size();
	glDrawArrays(GL_TRIANGLES, 0, _count);
}
void Mesh::SetMatrix(glm::mat4* _modelMatrix)
{
	modelMatrix = _modelMatrix;
}
void Mesh::LoadMesh(const char* _path, const char* _texturePath)
{
	ObjectStorage::mesh _mesh = ObjectStorage::LoadObject(_path);// loadOBJ(_mesh, vertices, uvs, normals);
	ObjectStorage::texture _texture = ObjectStorage::LoadTexture(_texturePath);//loadDDS(_texture);
	vertices = _mesh.vertices;
	uvs = _mesh.uvs;
	normals = _mesh.normals;
	texture = _texture.texture;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}
void Mesh::MoveVertex(glm::vec3 _pos)
{
	*modelMatrix = glm::translate(*modelMatrix, _pos);
}
void Mesh::ScaleVertex(glm::vec3 _scale)
{
	*modelMatrix = glm::scale(*modelMatrix, _scale);
}