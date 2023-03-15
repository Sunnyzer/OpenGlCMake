#include "Mesh.h"
#include "World.h"
#include "ObjectStorage.h"
#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>
#include "GameObject.h"
#include "Transform.h"

using namespace glm;

Mesh::Mesh()
{
	texture = 0;
	uvbuffer = 0;
	vertexbuffer = 0;
	modelMatrix = new mat4(1);
}
Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteTextures(1, &texture);
}
void Mesh::MeshDraw()
{
	glm::mat4 MVP = Camera::currentCamera->GetProjectionMatrix() * Camera::currentCamera->GetViewMatrix() * *modelMatrix;
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
void Mesh::Update(float deltaTime)
{
	vec3 _cameraF = Camera::currentCamera->forward;
	vec3 _objectF = gameObject->GetTransform()->position - Camera::currentCamera->GetPosition();
	float _angle = dot(_cameraF, _objectF);
	//if (_angle < 0.1) return;
	MeshDraw();
}

void Mesh::SetMatrix(mat4* _modelMatrix)
{
	delete modelMatrix;
	modelMatrix = _modelMatrix;
}

void Mesh::LoadMesh(const char* _path, const char* _texturePath, bool _uvmap)
{
	ObjectStorage::MeshData _mesh = ObjectStorage::LoadObject(_path);// loadOBJ(_mesh, vertices, uvs, normals);
	ObjectStorage::TextureData _texture = ObjectStorage::LoadTexture(_texturePath, _uvmap);//loadDDS(_texture);
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
void Mesh::MoveVertex(vec3 _pos)
{
	*modelMatrix = glm::translate(*modelMatrix, _pos);
}
void Mesh::ScaleVertex(vec3 _scale)
{
	*modelMatrix = glm::scale(*modelMatrix, _scale);
}
void Mesh::SetOwner(GameObject* _gameObject)
{
	gameObject = _gameObject;
	SetMatrix(&gameObject->GetTransform()->matrix);
}