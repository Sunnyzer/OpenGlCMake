#include "MonoBehaviour.h"

MonoBehaviour::MonoBehaviour()
{
}

MonoBehaviour::~MonoBehaviour()
{
	Destroy();
	OnDestroy;
	//OnDestroy.Clear();
}

void MonoBehaviour::SetOwner(GameObject* _gameObject)
{
	gameObject = _gameObject;
	Start();
}

void MonoBehaviour::Destroy()
{
	OnDestroy.Invoke(this);
}