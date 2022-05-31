#pragma once
#include <string>
#include <GL\glew.h>
#include "Input.h"
#include "Action.h"
#include "Camera.h"
#include "Transform.h"
#include "TimerManager.h"

class GameObject;

class MonoBehaviour
{
	friend GameObject;
public:
	GameObject* gameObject = nullptr;
	std::string inline GetName() { return name; }
protected:
	virtual void Start(){}
	virtual void Update(float deltaTime){}
	virtual void Destroy(){}
	std::string name = "";
private:
	static int instanceMono;
	/*void* operator new(size_t _count)
	{
		if (_count == 0)
			_count++;

		if (void* ptr = std::malloc(_count))
			return ptr;

		throw std::bad_alloc{};
	}*/
	virtual void SetOwner(GameObject* _gameObject);
};