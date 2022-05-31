#include "QuadTree.h"
#include "GameObject.h"

QuadTree::QuadTree()
{
	
}

QuadTree::~QuadTree()
{

}

void QuadTree::AddObject(Collider* _collider)
{
	glm::vec3 _position = _collider->gameObject->GetTransform()->position;
	int x = _position.x / offset + 5000;
	int y = _position.y / offset + 5000;
	int z = _position.z / offset + 5000;
	std::cout << x << " " << y << " " << z << std::endl;
	quadTree[x][y][z].contains.push_back(_collider);
}

void QuadTree::RemoveObject(Collider* _collider)
{
	glm::vec3 _position = _collider->gameObject->GetTransform()->position;
	int x = _position.x / offset + 5000;
	int y = _position.y / offset + 5000;
	int z = _position.z / offset + 5000;
	std::vector<Collider*> _gameObjects = quadTree[x][y][z].contains;
	size_t _size = _gameObjects.size();
	std::vector<Collider*>::iterator _it = _gameObjects.begin();
	std::vector<Collider*>::iterator _end = _gameObjects.end();
	for (; _it != _end; _it++)
	{
		if (*_it == _collider)
		{
			_gameObjects.erase(_it);
			return;
		}
	}
}

std::vector<Collider*> QuadTree::GetColliders(glm::vec3 _position)
{
	int x = _position.x / offset + 50;
	int y = _position.y / offset + 50;
	int z = _position.z / offset + 50;
	return quadTree[x][y][z].contains;
}