#include "Mesh.h"

Mesh::Mesh(const char* _mesh, const char* _texture, glm::vec3 _position, glm::vec3 _scale)
{
	bool res = loadOBJ(_mesh, vertices, uvs, normals);
	sizeVertices = vertices.size();
	texture = new GLuint();
	vertexbuffer = new GLuint();
	uvbuffer = new GLuint();
	for (size_t i = 0; i < sizeVertices; i++)
	{
		(vertices[i] *= _scale) += _position;
	}
	*texture = loadDDS(_texture);
	glGenBuffers(1, vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeVertices * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, *uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, vertexbuffer);
	glDeleteBuffers(1, uvbuffer);
	glDeleteTextures(1, texture);
}

void Mesh::MeshDraw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, *uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, sizeVertices);
}