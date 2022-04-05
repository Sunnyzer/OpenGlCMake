#pragma once

class GameObject;

class MonoBehaviour 
{
	friend GameObject;
public:
	GameObject* gameObject = nullptr;
protected:
	virtual void SetOwner(GameObject* _gameObject);
	virtual void Start(){}
	virtual void Update(float deltaTime){}
	virtual void Destroy(){}
};