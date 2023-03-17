#include "QuadTree.h"
#include <iostream>
#include "GameObject.h"

QuadTree::QuadTree()
{
	quadTree = nullptr;
}

QuadTree::~QuadTree()
{

}

void QuadTree::AddObject(Collider* _collider)
{
	glm::vec3 _position = _collider->gameObject->GetTransform()->position;
	int x = (int)_position.x / (int)offset + 50;
	int y = (int)_position.y / (int)offset + 50;
	int z = (int)_position.z / (int)offset + 50;
	std::cout << x << " " << y << " " << z << std::endl;
	//quadTree[x][y][z].contains.push_back(_collider);
}

void QuadTree::RemoveObject(Collider* _collider)
{
	glm::vec3 _position = _collider->gameObject->GetTransform()->position;
	int x = (int)_position.x / (int)offset + 50;
	int y = (int)_position.y / (int)offset + 50;
	int z = (int)_position.z / (int)offset + 50;
	std::vector<Collider*> _gameObjects = quadTree[x][y][z].contains;
	/*size_t _size = _gameObjects.size();
	std::vector<Collider*>::iterator _it = _gameObjects.begin();
	std::vector<Collider*>::iterator _end = _gameObjects.end();
	for (; _it != _end; _it++)
	{
		if (*_it == _collider)
		{
			_gameObjects.erase(_it);
			return;
		}
	}*/
}

std::vector<Collider*> QuadTree::GetColliders(glm::vec3 _position)
{
	int x = (int)_position.x / (int)offset + 50;
	int y = (int)_position.y / (int)offset + 50;
	int z = (int)_position.z / (int)offset + 50;
	return quadTree[x][y][z].contains;
}