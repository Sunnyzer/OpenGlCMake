#include "ObjectStorage.h"
#include <Common\objloader.hpp>
#include <Common\texture.hpp>

std::vector<ObjectStorage::mesh> ObjectStorage::meshs;
std::vector<ObjectStorage::texture> ObjectStorage::textures;

ObjectStorage::mesh ObjectStorage::LoadObject(const char* _path)
{
	int _size = meshs.size();
	for (size_t i = 0; i < _size; i++)
		if(meshs[i].pathName == _path)
			return meshs[i];
	mesh _meshOut;
	_meshOut.pathName = _path;
	loadOBJ(_path, _meshOut.vertices, _meshOut.uvs, _meshOut.normals);
	meshs.push_back(_meshOut);
	return _meshOut;
}

ObjectStorage::texture ObjectStorage::LoadTexture(const char* _texture)
{
	int _size = textures.size();
	for (size_t i = 0; i < _size; i++)
		if (textures[i].pathName == _texture)
			return textures[i];
	ObjectStorage::texture _textureOut;
	_textureOut.pathName = _texture;
	_textureOut.texture = loadDDS(_texture);
	textures.push_back(_textureOut);
	return _textureOut;
}
