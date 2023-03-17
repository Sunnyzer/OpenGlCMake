#pragma once
#include <GL\glew.h>
#include <string>
#include <Action.h>
#include <Transform.h>
#include <Input.h>

class GameObject;

class MonoBehaviour abstract
{
	friend GameObject;
public:
	GameObject* gameObject = nullptr;
	
	std::string GetName() { return name; }
	Action<MonoBehaviour*> OnDestroy;
	static int instanceMonoBehaviour;
protected:
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void Destroy();
	std::string name = "";
	virtual ~MonoBehaviour();
	MonoBehaviour();
private:
	virtual void SetOwner(GameObject* _gameObject);
};