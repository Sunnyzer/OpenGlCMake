#pragma once
#include "MonoBehaviour.h"

class World;
class Mesh;
class Transform;

class GameObject
{
	friend World;
public:
	GameObject();
	GameObject(std::string _name);
	virtual ~GameObject();
protected:
	virtual void Update(float deltaTime);
public:
	void AddComponent(MonoBehaviour* behaviour)
	{
		MonoBehaviour* _monoBehaviour = behaviour->Clone();
		_monoBehaviour->name = typeid(behaviour).name() + std::to_string(MonoBehaviour::instanceMonoBehaviour);
		_monoBehaviour->SetOwner(this);
		monoBehaviours.push_back(_monoBehaviour);
		++amountMonoBehaviour;
		OnAddMonoBehaviour.Invoke(_monoBehaviour);
	}
	template<class T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<MonoBehaviour, T>());
		T* _behaviour = new T();
		MonoBehaviour* _monoBehaviour = static_cast<MonoBehaviour*>(_behaviour);
		_monoBehaviour->name = typeid(T).name() + std::to_string(MonoBehaviour::instanceMonoBehaviour);
		_monoBehaviour->SetOwner(this);
		monoBehaviours.push_back(_monoBehaviour);
		++amountMonoBehaviour;
		OnAddMonoBehaviour.Invoke(_monoBehaviour);
		return _behaviour;
	}
	template<class T>
	T* GetComponent()
	{
		static_assert(std::is_base_of<MonoBehaviour, T>());
		T* _component = nullptr;
		for (size_t i = 0; i < amountMonoBehaviour; ++i)
		{
			/*if (typeid(*monoBehaviours[i]) != typeid(T))
				continue;*/
			_component = dynamic_cast<T*>(monoBehaviours[i]);
			if (!_component)
				continue;
			break;
		}
		return _component;
	}
	template<class T>
	static T* Instanciate()
	{
		static_assert(std::is_base_of<MonoBehaviour, T>());
		GameObject* _gameObject = new GameObject();
		T* _behaviour = _gameObject->AddComponent<T>();
		return _behaviour;
	}

	static void Destroy(GameObject* _gameObject);
	static void Destroy(MonoBehaviour* _mono)
	{
		std::vector<MonoBehaviour*> _monoBehaviours = _mono->gameObject->monoBehaviours;
		std::vector<MonoBehaviour*>::iterator it = _monoBehaviours.begin();
		for (; it != _monoBehaviours.end(); ++it)
		{
			if (*it != _mono)continue;
			_mono->gameObject->monoBehaviours.erase(it);
			return;
		}
		delete _mono;
	}

	Transform* GetTransform() const { return transform; };

	virtual void OnGUI();
	Action<MonoBehaviour*> OnAddMonoBehaviour;
	Action<GameObject*> OnDestroy;
	std::string name;
	
protected:
	Transform* transform;
	size_t amountMonoBehaviour;
	std::vector<MonoBehaviour*> monoBehaviours;
};