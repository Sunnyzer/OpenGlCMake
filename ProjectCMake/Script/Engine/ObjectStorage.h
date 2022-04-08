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
	struct MeshData
	{
		friend ObjectStorage;
	private:
		const char* pathName = "";
	public:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
	};
	struct TextureData
	{
		friend ObjectStorage;
	private:
		const char* pathName = "";
	public:
		GLuint texture = 0;
	};
	static std::vector<MeshData> meshDatas;
	static std::vector<TextureData> textureDatas;
	static MeshData LoadObject(const char* _path);
	static TextureData LoadTexture(const char* _texture, bool _uvmap);
};

