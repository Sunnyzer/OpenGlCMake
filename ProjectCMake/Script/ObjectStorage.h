#pragma once
#include <GL\glew.h>
#include <vector>
#include <glm\ext\vector_float3.hpp>
#include <glm\ext\vector_float2.hpp>

bool LoadOBJ(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals);
GLuint LoadBMP_custom(const char* imagepath);
GLuint LoadDDS(const char* imagepath);

class ObjectStorage
{
public:
	struct mesh
	{
		friend ObjectStorage;
	private:
		const char* pathName = "";
	public:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
	};
	struct texture
	{
		friend ObjectStorage;
	private:
		const char* pathName = "";
	public:
		GLuint texture;
	};
	static std::vector<mesh> meshs;
	static std::vector<texture> textures;
	static mesh LoadObject(const char* _path);
	static texture LoadTexture(const char* _texture);
};
