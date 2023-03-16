#pragma once
#include <string>
#include <GL\glew.h>
#include "Input.h"
#include "Action.h"
#include "Camera.h"
#include "Transform.h"
#include "TimerManager.h"

class GameObject;

class MonoBehaviour abstract
{
	friend GameObject;
public:
	GameObject* gameObject = nullptr;
	
	std::string GetName() { return name; }
	Action<MonoBehaviour*> OnDestroy;
protected:
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void Destroy();
	std::string name = "";
	virtual ~MonoBehaviour();
	MonoBehaviour();
private:
	static int instanceMono;
	virtual void SetOwner(GameObject* _gameObject);
};