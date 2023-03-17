#include "MonoBehaviour.h"
#include "Action.h"
#include "Camera.h"
#include "TimerManager.h"

int MonoBehaviour::instanceMonoBehaviour = 0;

MonoBehaviour::MonoBehaviour()
{
	++instanceMonoBehaviour;
}

MonoBehaviour::~MonoBehaviour()
{
	Destroy();
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