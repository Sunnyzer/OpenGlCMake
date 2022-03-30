#pragma once
#include <vector>
#include <Script/Mesh.h>

class ObjectStorage
{
public:
	struct mesh
	{
		friend ObjectStorage;
	private:
		const char* pathName;
	public:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
	};
	struct texture
	{
		friend ObjectStorage;
	private:
		const char* pathName;
	public:
		GLuint texture;
	};
	static std::vector<mesh> meshs;
	static std::vector<texture> textures;
	static mesh LoadObject(const char* _path);
	static texture LoadTexture(const char* _texture);
};

