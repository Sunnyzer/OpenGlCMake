#pragma once
#include <vector>
#include "MonoBehaviour.h"
#include "../Action.h"

class World;
class Mesh;
class Transform;

class GameObject
{
	friend World;
public:
	GameObject();
	virtual ~GameObject();
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
		_monoBehaviour->name = "Mono" + std::to_string(amountMonoCreate);
		amountMonoCreate++;
		_monoBehaviour->SetOwner(this);
		monoBehaviours.push_back(_monoBehaviour);
		++amountMonoBehaviour;
		OnAddMonoBehaviour.Invoke(_monoBehaviour);
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
	Action<MonoBehaviour*> OnAddMonoBehaviour;
	inline Transform* GetTransform() const { return transform; };
protected:
	static int amountMonoCreate;
	virtual void Update(float deltaTime);
	virtual void OnDestroy();
private:
	std::string name;
	Transform* transform;
	std::vector<MonoBehaviour*> monoBehaviours;
	size_t amountMonoBehaviour;
};