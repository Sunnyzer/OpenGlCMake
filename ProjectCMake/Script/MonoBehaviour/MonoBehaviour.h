#pragma once
#include <GL\glew.h>
#include <string>
#include <Action.h>
#include <Transform.h>
#include <Input.h>

class GameObject;

class MonoBehaviour 
{
	friend GameObject;
public:
	GameObject* gameObject = nullptr;
	
	std::string GetName() { return name; }
	Action<MonoBehaviour*> OnDestroy;
	static int instanceMonoBehaviour;
	virtual ~MonoBehaviour();
protected:
	MonoBehaviour();
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void Destroy();
	std::string name = "";
private:
	virtual void SetOwner(GameObject* _gameObject);
	virtual MonoBehaviour* Clone()
	{
		return new MonoBehaviour(*this);
	}
};