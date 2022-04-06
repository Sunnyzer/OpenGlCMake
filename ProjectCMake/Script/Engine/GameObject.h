#pragma once
#include <vector>
#include "MonoBehaviour.h"

class World;
class Mesh;
class Transform;

class GameObject
{
	friend World;
public:
	GameObject();
	virtual ~GameObject();
	inline Transform* GetTransform() { return transform; };
	template<class T>
	T* AddComponent()
	{
		T* _behaviour = new T();
		MonoBehaviour* _monoBehaviour = dynamic_cast<MonoBehaviour*>(_behaviour);
		if (!_monoBehaviour)
		{
			std::cout << "impossible de cast en monobehaviour" << std::endl;
			return nullptr;
		}
		_monoBehaviour->SetOwner(this);
		monoBehaviours.push_back(_monoBehaviour);
		++amountMonoBehaviour;
		return _behaviour;
	}
	template<class T>
	T* GetComponent()
	{
		for (size_t i = 0; i < amountMonoBehaviour; i++)
		{
			T* _component = dynamic_cast<T*>(monoBehaviours[i]);
			if (_component) return _component;
		}
		return nullptr;
	}
	template<class T>
	static T* Instanciate()
	{
		GameObject* _gameObject = new GameObject();
		T* _behaviour = _gameObject->AddComponent<T>();
		return _behaviour;
	}
private:
	virtual void Update(float deltaTime);
	virtual void OnDestroy();
	Transform* transform;
	std::vector<MonoBehaviour*> monoBehaviours;
	size_t amountMonoBehaviour;
};